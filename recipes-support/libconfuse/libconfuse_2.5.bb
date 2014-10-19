DESCRIPTION = "Library for parsing configuration files. Needed by ftdi_eeprom.\
"
HOMEPAGE = "http://www.intra2net.com/en/developer/libftdi/"
SECTION = "libs"

PR = "r0"

LICENSE = "LGPLv2.1"
LIC_FILES_CHKSUM= "file://COPYING;md5=bbb461211a33b134d42ed5ee802b37ff \
"

SRC_URI = " file://* \
"
# http://www.intra2net.com/en/developer/libftdi/download/confuse-2.5.tar.gz \
# file://patchTest.patch 
# file://patchTest2.patch 

SRC_URI[md5sum] = "4bc9b73d77ebd571ac834619ce0b3582"
SRC_URI[sha256sum] = "65451d8d6f5d4ca1dbd0700f3ef2ef257b52b542b3bab4bbeddd539f1c23f859"

S = "${WORKDIR}"

PACKAGECONFIG = "--enable-shared"

inherit autotools binconfig pkgconfig gettext

BBCLASSEXTEND = "native"

