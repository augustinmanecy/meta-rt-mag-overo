#############################################################################
#
#	Makefile for building the gpio-event kernel module
#
#############################################################################

ifneq ($(KERNELRELEASE),)
# call from kernel build system

obj-m	:= gpio-event-drv.o

else

PWD       	= $(shell pwd)

OVEROTOP	?= /home/gus/yocto/poky-dylan/build
CROSS_COMPILE	?= $(OVEROTOP)/tmp/sysroots/x86_64-linux/usr/bin/armv7a-vfp-neon-poky-linux-gnueabi/arm-poky-linux-gnueabi-

KERNEL_PATH     ?= /home/gus/yocto/poky-dylan/build/tmp/sysroots/overo/usr/src/kernel/

ARCH		?= arm

export ARCH CROSS_COMPILE

KBUILD_FLAGS 	= -C $(KERNEL_PATH) M=$(PWD)

default: modules

modules:
	$(MAKE) $(KBUILD_FLAGS) modules

clean:
	rm -rf *.o *~ *.ko *.mod.c .*.cmd .tmp* modules.order Module.symvers
endif

