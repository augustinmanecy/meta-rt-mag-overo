# A console development image with some C/C++ dev tools

require console-image.bb


#GPIO_TOOLS = " \
#    gpio-app gpio-lib gpio-module \
#    gpio-event-app gpio-event-module \
# "

GPIO_TOOLS = " \
    gpio-tools\
 "

DEV_TOOLS = " \
	bash \
	mtd-utils mtd-utils-ubifs \
 "

CPU_TOOLS = " \
	cpufrequtils \
 "
 
CUSTOMIZATIONS_RT_MaG = " \
	 inetutils-ftp \ 
	 openssl openssl-conf ca-certificates curl \
    opkg opkg-config-base opkg-collateral \
    rt-mag-toolbox-conf \
 "
# inetutils \ doesn't seem to work except if installed with opkg

MISC_EXTRA = ""

MISC_EXTRA_overo = " \
    polladc \
 "

IMAGE_INSTALL += " \
	${DEV_TOOLS} \
	${CPU_TOOLS} \
   ${CUSTOMIZATIONS_RT_MaG} \
 "   

ROOTFS_POSTPROCESS_COMMAND += "set_local_timezone ; "


export IMAGE_BASENAME = "rt-mag-image"


