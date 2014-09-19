SUMMARY = "Custom configuration for opkg for overo airSTORM"
DESCRIPTION = "This package configures repositories for updates."
LICENSE = "GPLv2"
LIC_FILES_CHKSUM =  "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

PR = "r0"

SRC_URI = "file://base-feed.conf \
	   file://debug-feed.conf \
	   file://gstreamer-feed.conf \
	   file://noarch-feed.conf \
	   file://overo-feed.conf \
	   file://perl-feed.conf \
	   file://python-feed.conf \
	  "

do_install () {
	install -d ${D}${sysconfdir}/opkg
	install -d ${D}/var/lib/opkg/tmp
	install -m 0644 ${WORKDIR}/base-feed.conf ${D}${sysconfdir}/opkg/base-feed.conf
	install -m 0644 ${WORKDIR}/debug-feed.conf ${D}${sysconfdir}/opkg/debug-feed.conf
	install -m 0644 ${WORKDIR}/gstreamer-feed.conf ${D}${sysconfdir}/opkg/gstreamer-feed.conf
	install -m 0644 ${WORKDIR}/noarch-feed.conf ${D}${sysconfdir}/opkg/noarch-feed.conf
	install -m 0644 ${WORKDIR}/overo-feed.conf ${D}${sysconfdir}/opkg/overo-feed.conf
	install -m 0644 ${WORKDIR}/perl-feed.conf ${D}${sysconfdir}/opkg/perl-feed.conf
	install -m 0644 ${WORKDIR}/python-feed.conf ${D}${sysconfdir}/opkg/python-feed.conf
}

