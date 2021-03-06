require recipes-kernel/linux/linux-yocto.inc

KERNEL_IMAGETYPE = "uImage"

COMPATIBLE_MACHINE = "overo"

# for identification
LINUX_VERSION_EXTENSION = "-RT-MaG"

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stable_3.5.7:"

S = "${WORKDIR}/git"

# v3.5.7 = f2b152564afdf9c9917c17d1c41c1082c82067bd
SRCREV = "f2b152564afdf9c9917c17d1c41c1082c82067bd"
SRC_URI = " \
    git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git;branch=linux-3.5.y \ 
    file://0001-Revert-omap2_mcspi-Flush-posted-writes.patch \
    file://0002-mtd-nand-Eliminate-noisey-uncorrectable-error-messag.patch \
    file://0003-OMAP-DSS2-add-bootarg-for-selecting-svideo-or-compos.patch \
    file://0004-video-add-timings-for-hd720.patch \
    file://0005-drivers-net-smsc911x-return-ENODEV-if-device-is-not-.patch \
    file://0006-drivers-input-touchscreen-ads7846-return-ENODEV-if-d.patch \
    file://0007-rtc-twl-add-support-for-backup-battery-recharge.patch \
    file://0008-soc-codecs-Enable-audio-capture-by-default-for-twl40.patch \
    file://0009-soc-codecs-twl4030-Turn-on-mic-bias-by-default.patch \
    file://0010-Add-power-off-support-for-the-TWL4030-companion.patch \
    file://0011-Enabling-Hwmon-driver-for-twl4030-madc.patch \
    file://0012-omap-overo-Add-twl4030-madc-support.patch \
    file://0013-omap-overo-Add-support-for-spidev.patch \
    file://0014-omap-overo-Add-opp-init.patch \
    file://0015-omap3-Add-basic-support-for-720MHz-part.patch \
    file://0016-omap-overo-Add-support-for-Caspa-camera-module.patch \
    file://0017-mfd-twl4030-madc-Enable-ADC-channels-3-6.patch \
    file://0018-omap-overo-Restructure-code-to-allow-customization-v.patch \
    file://0019-omap-beagle-Don-t-register-madc-twice.patch \
    file://0020-omap-overo-don-t-overwrite-sdrc-setup-from-u-boot-sp.patch \
    file://0021-mmc-omap-add-sdio-interrupt-support.patch \
    file://0022-v4l2-ctrls-Add-v4l2_ctrl_-gs-_ctrl_int64.patch \
    file://0023-mt9v032-Provide-pixel-rate-control.patch \
    file://0024-mt9v032-Provide-link-frequency-control.patch \
    file://0025-mt9v032-Export-horizontal-and-vertical-blanking-as-V.patch \
    file://0026-board-overo-Add-Caspa-camera-link-frequencies.patch \
    file://0027-ARM-OMAP-USB-Fixup-ehci_hcd_omap_probe-error-path.patch \
    file://0028-ARM-OMAP-USB-Fix-omap3xxx-EHCI-regression-caused-by-.patch \
    file://0030-Fix-sprz319-erratum-2.1.patch \
    file://0031-OMAP3-overo-increase-linux-partition-to-8-MiB.patch \
    file://0032-Backport-patch-required-to-allow-mt9v032-module-to-b.patch \
    file://0033-ARM-7668-1-fix-memset-related-crashes-caused-by-rece.patch \
    file://0034-ARM-7670-1-fix-the-memset-fix.patch \
    file://0035-OMAP2-3-clock-fix-sprz319-erratum-2.1.patch \ 
    file://defconfig \
"

