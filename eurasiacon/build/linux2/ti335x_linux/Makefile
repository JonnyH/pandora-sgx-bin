#
# Copyright (C) Imagination Technologies Ltd. All rights reserved.
# 
# This program is free software; you can redistribute it and/or modify it
# under the terms and conditions of the GNU General Public License,
# version 2, as published by the Free Software Foundation.
# 
# This program is distributed in the hope it will be useful but, except 
# as otherwise stated in writing, without any warranty; without even the 
# implied warranty of merchantability or fitness for a particular purpose. 
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
# 
# The full GNU General Public License is included in this distribution in
# the file called "COPYING".
#
# Contact Information:
# Imagination Technologies Ltd. <gpl-support@imgtec.com>
# Home Park Estate, Kings Langley, Herts, WD4 8LZ, UK 
# 
#

PVR_SYSTEM		:= ti335x

KERNEL_COMPONENTS := srvkm bufferclass_example

include ../kernel_version.mk

OMAP_KERNEL_AT_LEAST_2_6_35 := $(shell test $(KERNEL_VERSION) -ge 2 -a \
			$(KERNEL_PATCHLEVEL) -ge 6 -a \
			$(KERNEL_SUBLEVEL) -ge 35 && echo 1 || echo 0)

# Only enable active power management if passive power management is
# enabled, as indicated by LDM_PLATFORM being set to 1.  On OMAP,
# the system can suspend in the case where active power management is
# enabled in the SGX driver, but passive power management isn't. As
# passive power management isn't enabled, the driver won't see the
# system suspend/resume events, and so won't take appropriate action.
LDM_PLATFORM ?= 1

SUPPORT_LINUX_USING_WORKQUEUES := 1
DISPLAY_CONTROLLER_COMPONENT += dc_omapfb3_linux
DISPLAY_CONTROLLER := omaplfb

OPTIM := -Os

SYS_CFLAGS := -march=armv7-a
TRANSFER_QUEUE                          ?= 1
SUPPORT_SGX_EVENT_OBJECT                ?= 1
SUPPORT_SECURE_HANDLES                  = 1
SUPPORT_SRVINIT                         = 1
SUPPORT_PERCONTEXT_PB                   = 1
DISABLE_SGX_PB_GROW_SHRINK             ?= 1
SUPPORT_LINUX_X86_PAT                   ?=1
SUPPORT_LINUX_X86_WRITECOMBINE          ?=1
SUPPORT_SGX_LOW_LATENCY_SCHEDULING      ?=1


SUPPORT_OMAP4430_NEON ?= 1
PVR_LDM_PLATFORM_PRE_REGISTERED := 0

ifeq ($(SUPPORT_OMAP4430_NEON),1)
SYS_CFLAGS += -ftree-vectorize -mfpu=neon -mfloat-abi=softfp
endif

PVR_NO_FULL_CACHE_OPS := 1

LIBGCC := $(shell $(CROSS_COMPILE)gcc -print-libgcc-file-name)

SGXCORE := 530
SGX_CORE_REV := 125

SGX_DYNAMIC_TIMING_INFO := 1
SYS_CUSTOM_POWERLOCK_WRAP := 1

ifeq ($(OMAP_NON_FLIP_DISPLAY),1)
OPK_DEFAULT := libpvrPVR2D_BLITWSEGL.so
else
OPK_DEFAULT := libpvrPVR2D_FLIPWSEGL.so
endif

ifeq ($(OMAP_KERNEL_AT_LEAST_2_6_35),1)
ifeq ($(LDM_PLATFORM),1)
PVR_LDM_PLATFORM_PRE_REGISTERED := 0
endif
endif

include ../common/xorg_test.mk
ifeq ($(want_xorg),1)

SUPPORT_DRI_DRM := 1

ifeq ($(OMAP_KERNEL_AT_LEAST_2_6_35),1)
PVR_DRI_DRM_PLATFORM_DEV := 1
PVR_DRI_DRM_STATIC_BUS_ID := 1
else
PVR_DRI_DRM_NOT_PCI := 1
endif

XORG_TOOLCHAIN := tarballs-omap4-ubuntu-10.10-cross
XORG_PVR_CONF := omap4
XORG_PVR_VIDEO := omap4

OPK_FALLBACK := libpvrPVR2D_DRIWSEGL.so

ifneq ($(OMAP_NON_FLIP_DISPLAY),1)
XORG_PVR_VIDEO ?= $(PVR_SYSTEM)
PVR_DISPLAY_CONTROLLER_DRM_IOCTL := 1
endif

else  # xorg isn't excluded

OPK_FALLBACK := libpvrPVR2D_BLITWSEGL.so

endif # xorg isn't excluded

ifeq ($(SUPPORT_DRI_DRM),1)
ifeq ($(PVR_DRI_DRM_NOT_PCI),1)
KERNEL_COMPONENTS += linux_drm
EXTRA_KBUILD_SOURCE := $(KERNELDIR)
endif
EXTRA_PVRSRVKM_COMPONENTS += $(DISPLAY_CONTROLLER_COMPONENT)
else
KERNEL_COMPONENTS += $(DISPLAY_CONTROLLER_COMPONENT)
endif

include ../config/core.mk
include ../common/xorg.mk
include ../common/dridrm.mk
include ../common/opencl.mk
include ../common/omap4.mk

# We only need this for pvr_video's includes, which should
# really be done differently, as DISPLAY_CONTROLLER_DIR is
# now obsolete..
#
$(eval $(call UserConfigMake,DISPLAY_CONTROLLER_DIR,3rdparty/$(DISPLAY_CONTROLLER_COMPONENT)))
