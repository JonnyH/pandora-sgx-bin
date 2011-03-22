/*
 * Copyright (c) 2010-2011 Imre Deak <imre.deak@nokia.com>
 * Copyright (c) 2010-2011 Luc Verhaegen <libv@codethink.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/*
 *
 * Debugfs interface living in pvr/ subdirectory.
 *
 */
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/vmalloc.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>

#include "img_types.h"
#include "servicesext.h"
#include "services.h"
#include "sgxinfokm.h"
#include "syscommon.h"
#include "pvr_bridge_km.h"
#include "sgxutils.h"
#include "pvr_debugfs.h"

static struct dentry *debugfs_dir;
static u32 pvr_reset;

/*
 *
 */
static struct PVRSRV_DEVICE_NODE *get_sgx_node(void)
{
	struct SYS_DATA *sysdata;
	struct PVRSRV_DEVICE_NODE *node;

	if (SysAcquireData(&sysdata) != PVRSRV_OK)
		return NULL;

	for (node = sysdata->psDeviceNodeList; node; node = node->psNext)
		if (node->sDevId.eDeviceType == PVRSRV_DEVICE_TYPE_SGX)
			break;

	return node;
}

static int pvr_debugfs_reset(void *data, u64 val)
{
	struct PVRSRV_DEVICE_NODE *node;
	enum PVRSRV_ERROR err;
	int r = 0;

	if (val != 1)
		return 0;

	pvr_lock();

	if (pvr_is_disabled()) {
		r = -ENODEV;
		goto exit;
	}

	node = get_sgx_node();
	if (!node) {
		r =  -ENODEV;
		goto exit;
	}

	err = PVRSRVSetDevicePowerStateKM(node->sDevId.ui32DeviceIndex,
					  PVRSRV_POWER_STATE_D0);
	if (err != PVRSRV_OK) {
		r = -EIO;
		goto exit;
	}

	HWRecoveryResetSGX(node);

	SGXTestActivePowerEvent(node);
exit:
	pvr_unlock();

	return r;
}

static int pvr_debugfs_set(void *data, u64 val)
{
	u32 *var = data;

	if (var == &pvr_reset)
		return pvr_debugfs_reset(data, val);

	BUG();
}

DEFINE_SIMPLE_ATTRIBUTE(pvr_debugfs_fops, NULL, pvr_debugfs_set, "%llu\n");

/*
 *
 */
struct edm_buf_info {
	size_t len;
	char data[1];
};

static int pvr_debugfs_edm_open(struct inode *inode, struct file *file)
{
	struct PVRSRV_DEVICE_NODE *node;
	struct PVRSRV_SGXDEV_INFO *sgx_info;
	struct edm_buf_info *bi;
	size_t size;

	/* Take a snapshot of the EDM trace buffer */
	size = SGXMK_TRACE_BUFFER_SIZE * SGXMK_TRACE_BUF_STR_LEN;
	bi = vmalloc(sizeof(*bi) + size);
	if (!bi)
		return -ENOMEM;

	node = get_sgx_node();
	sgx_info = node->pvDevice;
	bi->len = snprint_edm_trace(sgx_info, bi->data, size);
	file->private_data = bi;

	return 0;
}

static int pvr_debugfs_edm_release(struct inode *inode, struct file *file)
{
	vfree(file->private_data);

	return 0;
}

static ssize_t pvr_debugfs_edm_read(struct file *file, char __user *buffer,
				size_t count, loff_t *ppos)
{
	struct edm_buf_info *bi = file->private_data;

	return simple_read_from_buffer(buffer, count, ppos, bi->data, bi->len);
}

static const struct file_operations pvr_debugfs_edm_fops = {
	.owner		= THIS_MODULE,
	.open		= pvr_debugfs_edm_open,
	.read		= pvr_debugfs_edm_read,
	.release	= pvr_debugfs_edm_release,
};


/*
 *
 * HW Recovery dumping support.
 *
 */
static struct mutex hwrec_mutex[1];
static struct timeval hwrec_time;
static int hwrec_open_count;
static DECLARE_WAIT_QUEUE_HEAD(hwrec_wait_queue);
static int hwrec_event;

/* add extra locking to keep us from overwriting things during dumping. */
static int hwrec_event_open_count;
static int hwrec_event_file_lock;

void
pvr_hwrec_dump(void)
{
	mutex_lock(hwrec_mutex);

	if (hwrec_open_count || hwrec_event_file_lock) {
		pr_err("%s: previous hwrec dump is still locked!\n", __func__);
		mutex_unlock(hwrec_mutex);
		return;
	}

	do_gettimeofday(&hwrec_time);
	pr_info("HW Recovery dump generated at %010ld%06ld\n",
		hwrec_time.tv_sec, hwrec_time.tv_usec);

	hwrec_event = 1;

	mutex_unlock(hwrec_mutex);

	wake_up_interruptible(&hwrec_wait_queue);
}

/*
 * helpers.
 */
static int
hwrec_file_open(struct inode *inode, struct file *filp)
{
	mutex_lock(hwrec_mutex);

	hwrec_open_count++;

	mutex_unlock(hwrec_mutex);
	return 0;
}

static int
hwrec_file_release(struct inode *inode, struct file *filp)
{
	mutex_lock(hwrec_mutex);

	hwrec_open_count--;

	mutex_unlock(hwrec_mutex);
	return 0;
}

/*
 * Provides a hwrec timestamp for unique dumping.
 */
static ssize_t
hwrec_time_read(struct file *filp, char __user *buf, size_t size,
		loff_t *f_pos)
{
	char tmp[20];

	mutex_lock(hwrec_mutex);
	snprintf(tmp, sizeof(tmp), "%010ld%06ld",
		 hwrec_time.tv_sec, hwrec_time.tv_usec);
	mutex_unlock(hwrec_mutex);

	return simple_read_from_buffer(buf, size, f_pos, tmp, strlen(tmp));
}

static const struct file_operations hwrec_time_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.read = hwrec_time_read,
	.open = hwrec_file_open,
	.release = hwrec_file_release,
};

/*
 * Blocks the reader until a HWRec happens.
 */
static int
hwrec_event_open(struct inode *inode, struct file *filp)
{
	int ret;

	mutex_lock(hwrec_mutex);

	if (hwrec_event_open_count)
		ret = -EUSERS;
	else {
		hwrec_event_open_count++;
		ret = 0;
	}

	mutex_unlock(hwrec_mutex);

	return ret;
}

static int
hwrec_event_release(struct inode *inode, struct file *filp)
{
	mutex_lock(hwrec_mutex);

	hwrec_event_open_count--;

	mutex_unlock(hwrec_mutex);

	return 0;
}


static ssize_t
hwrec_event_read(struct file *filp, char __user *buf, size_t size,
		 loff_t *f_pos)
{
	int ret = 0;

	mutex_lock(hwrec_mutex);

	hwrec_event_file_lock = 0;

	mutex_unlock(hwrec_mutex);

	ret = wait_event_interruptible(hwrec_wait_queue, hwrec_event);
	if (!ret) {
		mutex_lock(hwrec_mutex);

		hwrec_event = 0;
		hwrec_event_file_lock = 1;

		mutex_unlock(hwrec_mutex);
	}

	return ret;
}

static const struct file_operations hwrec_event_fops = {
	.owner = THIS_MODULE,
	.llseek = no_llseek,
	.read = hwrec_event_read,
	.open = hwrec_event_open,
	.release = hwrec_event_release,
};

/*
 *
 */
int pvr_debugfs_init(void)
{
	mutex_init(hwrec_mutex);

	debugfs_dir = debugfs_create_dir("pvr", NULL);
	if (!debugfs_dir)
		return -ENODEV;

	if (!debugfs_create_file("reset_sgx", S_IWUSR, debugfs_dir, &pvr_reset,
				 &pvr_debugfs_fops)) {
		debugfs_remove(debugfs_dir);
		return -ENODEV;
	}

	if (!debugfs_create_file("edm_trace", S_IRUGO, debugfs_dir, NULL,
				 &pvr_debugfs_edm_fops)) {
		debugfs_remove_recursive(debugfs_dir);
		return -ENODEV;
	}

	if (!debugfs_create_file("hwrec_event", S_IRUSR, debugfs_dir, NULL,
				 &hwrec_event_fops)) {
		debugfs_remove_recursive(debugfs_dir);
		return -ENODEV;
	}

	if (!debugfs_create_file("hwrec_time", S_IRUSR, debugfs_dir, NULL,
				 &hwrec_time_fops)) {
		debugfs_remove_recursive(debugfs_dir);
		return -ENODEV;
	}

	return 0;
}

void pvr_debugfs_cleanup(void)
{
	debugfs_remove_recursive(debugfs_dir);
}
