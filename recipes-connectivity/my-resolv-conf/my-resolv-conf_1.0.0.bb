SUMMARY = "Custom configuration for network in ISM Marseille"
DESCRIPTION = "This package modifies the files used to configure the network: /etc/network/interfaces, /etc/resolv.conf, /etc/wpa_supplicant.conf"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM =  "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

PR = "r0"

SRC_URI = "file://resolv.conf \          
	  "

do_install () {
	install -d ${D}${sysconfdir}
	install -m 0644 ${WORKDIR}/resolv.conf ${D}${sysconfdir}/resolv.conf
}

