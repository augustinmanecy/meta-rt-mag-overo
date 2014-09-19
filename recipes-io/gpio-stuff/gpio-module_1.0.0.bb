DESCRIPTION = "Linux Driver for manipulating GPIO pins"
LICENSE = "GPLv1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PR = "r1"

inherit module update-rc.d

INITSCRIPT_NAME = "gpio"
INITSCRIPT_PARAMS = "defaults 40"

SRC_URI = "file://gpio/module/user-gpio-drv.h \
			file://gpio/module/gpio.init \
			file://gpio/module/Makefile \
			file://gpio/module/user-gpio-drv.mod.c \
			file://gpio/module/user-gpio-drv.c \
			file://gpio/module/yocto-env.sh \
		"

S = "${WORKDIR}/gpio/module"

d_compile() {
	make
}

do_install() {	
	 install -m 0644 ${S}/user-gpio-drv.h ${STAGING_INCDIR}/
    install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -m 0644 ${S}/user-gpio-drv.ko ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -d ${D}${sysconfdir}/init.d/
    install -m 0755 ${S}/gpio.init ${D}${sysconfdir}/init.d/gpio
}

PACKAGES = "${PN}"

FILES_${PN} = "${base_libdir}/modules/"
FILES_${PN} += "${sysconfdir}/"

