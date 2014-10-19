SUMMARY = "Simple hello geek!"
SECTION = "examples"
LICENSE = "GPLv2"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

SRC_URI = "file://hellogeek.c"

S = "${WORKDIR}"

do_compile() {
	${CC} hellogeek.c -o hellogeek
}

do_install() {
	install -d ${D}${bindir}
	install -m 0755 hellogeek ${D}${bindir}
}

