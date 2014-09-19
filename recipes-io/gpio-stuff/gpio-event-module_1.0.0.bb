DESCRIPTION = "Linux Driver for Detecting GPIO events"
SECTION = "base"
PRIORITY = "optional"
LICENSE = "GPLv1"
DEPENDS = "virtual/kernel"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-1.0;md5=e9e36a9de734199567a4d769498f743d"

PR = "r3"

inherit module update-rc.d

INITSCRIPT_NAME = "gpio-event"
INITSCRIPT_PARAMS = "defaults 40"

SRC_URI = "file://gpio-event/module/gpio-event-drv.h \
			file://gpio-event/module/gpio-event-drv.mod.c \
			file://gpio-event/module/gpio-event-drv.c \
			file://gpio-event/module/gpio-event.init \
			file://gpio-event/module/Makefile \
			file://gpio-event/module/yocto-env.sh \
		"

S = "${WORKDIR}/gpio-event/module"

do_compile() {
  make
}

do_install() {	
	 install -m 0644 ${S}/gpio-event-drv.h ${STAGING_INCDIR}/
    install -d ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -m 0644 ${S}/gpio-event-drv.ko ${D}${base_libdir}/modules/${KERNEL_VERSION}/extra/
    install -d ${D}${sysconfdir}/init.d/
    install -m 0755 ${S}/gpio-event.init ${D}${sysconfdir}/init.d/gpio-event
}

PACKAGES = "${PN}"

FILES_${PN} = "${base_libdir}/modules/"
FILES_${PN} += "${sysconfdir}/"

