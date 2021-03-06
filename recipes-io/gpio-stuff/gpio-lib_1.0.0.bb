DESCRIPTION = "User Lib for manipulating GPIO pins"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "GPLv1"
DEPENDS = "gpio-module"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PR = "r0"

SRC_URI = "file://gpio/lib/user-gpio.h \
			file://gpio/module/user-gpio-drv.h \
			file://gpio/lib/user-gpio.c \
			file://gpio/lib/Makefile \
			file://gpio/lib/yocto-env.sh \
		"

S = "${WORKDIR}/gpio/lib"

do_compile() {
	make
}

do_install() {	
	 oe_libinstall -so -a libgpio ${STAGING_LIBDIR}
    install -m 0644 ${S}/user-gpio.h ${STAGING_INCDIR}/
    install -d ${D}${libdir}/
    install -m 0755 ${S}/libgpio.so ${D}${libdir}/
}

PACKAGES = "${PN}"

FILES_${PN} = "${libdir}/libgpio.so \
					${STAGING_INCDIR}/ "

