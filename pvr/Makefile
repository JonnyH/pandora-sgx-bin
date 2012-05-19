CONFIG_PVR = m

CONFIG_PVR_RELEASE = y
CONFIG_PVR_DEBUG = n
CONFIG_PVR_TIMING = n

CONFIG_PVR_DEBUG_EXTRA = n
CONFIG_PVR_DEBUG_PDUMP = n
CONFIG_PVR_PDUMP_MODE_STANDARD = n
CONFIG_PVR_PDUMP_MODE_FULL = n
CONFIG_PVR_EDM_DEBUG = n
CONFIG_NO_HARDWARE = n
CONFIG_PVR_FORCE_CLOCKS_ON = n
CONFIG_PVR_EXAMPLES = n
CONFIG_PVR_TRACE_CMD = n

ccflags-$(CONFIG_PVR_DEBUG) += -DCONFIG_PVR_DEBUG
ccflags-$(CONFIG_PVR_DEBUG_EXTRA) += -DCONFIG_PVR_DEBUG_EXTRA
ccflags-$(CONFIG_PVR_DEBUG_PDUMP) += -DCONFIG_PVR_DEBUG_PDUMP \
	-DCONFIG_PVR_PDUMP_INITIAL_MAX_FRAME_COUNT=4
ccflags-$(CONFIG_PVR_PDUMP_MODE_STANDARD) += -DCONFIG_PVR_PDUMP_MODE_STANDARD
ccflags-$(CONFIG_PVR_PDUMP_MODE_FULL) += -DCONFIG_PVR_PDUMP_MODE_FULL
ccflags-$(CONFIG_PVR_EDM_DEBUG) += -DCONFIG_PVR_EDM_DEBUG
ccflags-$(CONFIG_PVR_EXAMPLES) += -DCONFIG_PVR_EXAMPLES
ccflags-$(CONFIG_PVR_FORCE_CLOCKS_ON) += -DCONFIG_PVR_FORCE_CLOCKS_ON
ccflags-$(CONFIG_PVR_NO_HARDWARE) += -DCONFIG_PVR_NO_HARDWARE
ccflags-$(CONFIG_PVR_RELEASE) += -DCONFIG_PVR_RELEASE
ccflags-$(CONFIG_PVR_TIMING) += -DCONFIG_PVR_TIMING
ccflags-$(CONFIG_PVR_TOOLS) += -DCONFIG_PVR_TOOLS
ccflags-$(CONFIG_PVR_TRACE_CMD) += -DCONFIG_PVR_TRACE_CMD \
	-DCONFIG_PVR_TRACE_CMD_BUF_SHIFT=3

ccflags-y += -I$(src)/../include

ifeq ($(KERNELRELEASE),)
all:
	$(MAKE) -C $(KERNELDIR) M=`pwd` $*

clean:
	$(MAKE) -C $(KERNELDIR) M=`pwd` clean
endif

###

obj-$(CONFIG_PVR)	+= omaplfb.o pvrsrvkm.o

omaplfb-objs		:= omaplfb_displayclass.o omaplfb_linux.o

pvrsrvkm-objs		:= osfunc.o mmap.o module.o proc.o	   \
			   pvr_bridge_k.o mm.o event.o	   \
			   buffer_manager.o devicemem.o deviceclass.o	   \
			   handle.o hash.o pvrsrv.o queue.o ra.o	   \
			   resman.o power.o mem.o bridged_pvr_bridge.o	   \
			   sgxinit.o sgxreset.o sgxutils.o sgxkick.o	   \
			   sgxtransfer.o mmu.o pb.o perproc.o sysconfig.o  \
			   sysutils.o osperproc.o bridged_support.o	   \
			   bridged_sgx_bridge.o	sgxpower.o pvr_events.o    \
			   pvr_debugfs.o

pvrsrvkm-objs-$(CONFIG_PVR_DEBUG) += pvr_debug.o
pvrsrvkm-objs-$(CONFIG_PVR_TIMING) += pvr_debug.o
pvrsrvkm-objs-$(CONFIG_PVR_DEBUG_PDUMP) += pvr_pdump.o pvr_pdumpfs.o
pvrsrvkm-objs-$(CONFIG_PVR_TRACE_CMD) += pvr_trace_cmd.o

pvrsrvkm-objs		+= $(pvrsrvkm-objs-y) $(pvrsrvkm-objs-m)

obj-$(CONFIG_PVR_EXAMPLES) += bc_example.o

bc_example-objs		:= bufferclass_example.o bufferclass_example_linux.o \
			   bufferclass_example_private.o


DATE			:= $(shell date "+%a %B %d %Z %Y" )
CBUILD			:= -O2						\
			   -DPVR_BUILD_DIR="\"$(PVR_BUILD_DIR)\""	\
			   -DPVR_BUILD_DATE="\"$(DATE)\""

ccflags-y		+= $(CBUILD) -include $(src)/pvrconfig.h
ccflags-y		+= $(ccflags-m)


