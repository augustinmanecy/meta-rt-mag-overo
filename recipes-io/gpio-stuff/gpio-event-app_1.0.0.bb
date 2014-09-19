DESCRIPTION = "User App for Detecting GPIO events"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "GPLv1"
DEPENDS = "gpio-event-module"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PV="svn${SRCDATE}"
PR = "r2"

SRC_URI = "file://gpio-event/app/gpio-event \
		"

S = "${WORKDIR}/gpio-event/app"

TARGET_CC_ARCH += "${LDFLAGS}"

do_install() {	
    install -d ${D}${bindir}/
    install -m 0755 ${S}/gpio-event ${D}${bindir}/
}

PACKAGES = "${PN}"

FILES_${PN} = "${bindir}/gpio-event"

