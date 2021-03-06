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

DEPENDS_${PN} = " 	libusb \
		 libconfuse \ 
"

SRC_URI = "http://www.intra2net.com/en/developer/libftdi/download/libftdi1-1.1.tar.bz2 \
"
SRC_URI[md5sum] = "b79a6356978aa8e69f8eecc3a720ff79"
SRC_URI[sha256sum] = "c0b1af1a13e2c6682a1d8041e5b164a1e0d90267cd378bb51e059bd62f821e21"

S = "${WORKDIR}/libftdi1-1.1"

PACKAGECONFIG ??= ""
# PACKAGECONFIG[cpp-wrapper] = "--enable-libftdipp,--disable-libftdipp,boost"

inherit autotools binconfig pkgconfig cmake

BBCLASSEXTEND = "native"

FILES_${PN} += " \
            ${includedir}/* \
            ${libdir}/* \
            ${bindir}/* \
         "
