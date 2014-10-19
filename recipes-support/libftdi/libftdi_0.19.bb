DESCRIPTION = "libftdi is a library to talk to FTDI chips.\
FT232BM/245BM, FT2232C/D and FT232/245R using libusb,\
including the popular bitbang mode."
HOMEPAGE = "http://www.intra2net.com/en/developer/libftdi/"
SECTION = "libs"

PR = "r1"

LICENSE = "LGPLv2.1 GPLv2"
LIC_FILES_CHKSUM= "file://COPYING.GPL;md5=751419260aa954499f7abaabaa882bbe \
                   file://COPYING.LIB;md5=db979804f025cf55aabec7129cb671ed \
"

DEPENDS = "virtual/libusb0"
DEPENDS_virtclass-native = "virtual/libusb0-native"

SRC_URI = "file://* \
"

S = "${WORKDIR}"

PACKAGECONFIG ??= ""
PACKAGECONFIG[cpp-wrapper] = "--enable-libftdipp,--disable-libftdipp,boost"

inherit autotools binconfig pkgconfig

FILES_${PN} += " \
            ${includedir}/* \
            ${libdir}/* \
            ${bindir}/* \
         "

BBCLASSEXTEND = "native"

