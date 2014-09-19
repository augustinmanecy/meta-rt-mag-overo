#############################################################################
#
#	Makefile for building the gpio kernel module
#
#############################################################################

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= user-gpio-drv.o

else

PWD       	= $(shell pwd)

OVEROTOP	?= /home/gus/yocto/overo/build
CROSS_COMPILE	?= $(OVEROTOP)/tmp/sysroots/`uname -m`-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-

KERNEL_PATH     ?= $(OVEROTOP)/tmp/sysroots/overo/usr/src/kernel/
ARCH		?= arm

export ARCH CROSS_COMPILE

KBUILD_FLAGS 	= -C $(KERNEL_PATH) M=$(PWD)

default: modules

modules:
	echo $(MAKE) $(KBUILD_FLAGS) modules
	$(MAKE) $(KBUILD_FLAGS) modules

clean:
	rm -rf *.o *~ *.ko *.mod.c .*.cmd .tmp* modules.order Module.symvers
endif

