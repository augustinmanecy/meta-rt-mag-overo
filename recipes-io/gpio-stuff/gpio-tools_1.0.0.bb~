DESCRIPTION = "User App, Lib and  kernel modules for manipulating GPIO pins"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "GPLv1"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PR = "r0"

SRC_URI = "file://gpio/app/gpio \
			file://gpio/module/gpio.init \
			file://gpio/module/user-gpio-drv.ko \
			file://gpio/module/user-gpio-drv.h \
			file://gpio/lib/user-gpio.h \
			file://gpio/lib/libgpio.a \
			file://gpio/lib/libgpio.so \
		"

S_APP = "${WORKDIR}/gpio/app"
S_LIB = "${WORKDIR}/gpio/lib"
S_MOD = "${WORKDIR}/gpio/module"

do_install() {	
    install -d ${D}${bindir}/
    install -m 0755 ${S_APP}/gpio ${D}${bindir}/ 
    install -m 0644 ${S_LIB}/user-gpio.h ${STAGING_INCDIR}/
    install -d ${D}${libdir}/
    install -m 0755 ${S_LIB}/libgpio.so ${D}${libdir}/
    install -m 0644 ${S_MOD}/user-gpio-drv.h ${STAGING_INCDIR}/
    install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -m 0644 ${S_MOD}/user-gpio-drv.ko ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -d ${D}${sysconfdir}/init.d/
    install -m 0755 ${S_MOD}/gpio.init ${D}${sysconfdir}/init.d/gpio
}

PACKAGES = "${PN}"

FILES_${PN} = "\
			${bindir}/gpio \
			${libdir}/* \ 
			${base_libdir}/modules/ \
			${sysconfdir}/ \
 "


