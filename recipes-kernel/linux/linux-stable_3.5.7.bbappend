FILESEXTRAPATHS_prepend := "${THISDIR}/linux-stable-3.5.7:"

SRC_URI += " \
    file://0036-add-RT-priority-to-spi-worker-thread.patch \
    file://0037-add-to-spidev-asynchronous-capabilities.patch \    
"

