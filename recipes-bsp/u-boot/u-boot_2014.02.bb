require u-boot.inc

PV = "2014.02"

COMPATIBLE_MACHINE = "overo"

# for identification
UBOOT_LOCALVERSION = "-gus"

# v2014.01
SRCREV = "b44bd2c73c4cfb6e3b9e7f8cf987e8e39aa74a0b"
SRC_URI = "git://git.denx.de/u-boot.git;branch=master;protocol=git \
           file://0001-omap-overo-allow-the-use-of-a-plain-text-env-file-in.patch \
           file://0002-OMAP3-overo-add-command-support-for-mtd-and-ubi.patch \
"

SRC_URI_append = "file://fw_env.config"

SPL_BINARY = "MLO"
