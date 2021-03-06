DESCRIPTION = "User App for manipulating GPIO pins"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "GPLv1"
DEPENDS = "gpio-lib"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PR = "r0"

SRC_URI = "file://gpio/app/Makefile \
			file://gpio/app/gpio.c \
			file://gpio/app/yocto-env.sh \
		"

S = "${WORKDIR}/gpio/app"

TARGET_CC_ARCH += "${LDFLAGS}"

do_compile() {
	make
}

do_install() {	
    install -d ${D}${bindir}/
    install -m 0755 ${S}/gpio ${D}${bindir}/
}

PACKAGES = "${PN}"

FILES_${PN} = "${bindir}/gpio "


