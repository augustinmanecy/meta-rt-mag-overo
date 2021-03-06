SUMMARY = "Initial directories for the RT-MaG ToolBox"
DESCRIPTION = "This package creates the directories with the needed files to run the RT-MaG ToolBox."
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6"

PR = "r0"

SRC_URI = "\
		file://etc/profile.d/systemstat.sh \
		file://etc/profile.d/GoToRT-MaG_Folder.sh \
		file://RT_MaG_ToolBox/LoadProfile \
		file://RT_MaG_ToolBox/RT_MaG_profile.conf \
		file://RT_MaG_ToolBox/RT_MaG_Program/PutFTP \
		file://RT_MaG_ToolBox/RT_MaG_Program/PullFTP \
	   file://RT_MaG_ToolBox/RT_MaG_Program/RunModel \
	   file://RT_MaG_ToolBox/RT_MaG_Program/UpToDateModel \
	   file://RT_MaG_ToolBox/RT_MaG_Program/CompileTestModels \
	   file://RT_MaG_ToolBox/RT_MaG_Program/SendTimeLogger \
	   file://RT_MaG_ToolBox/RT_MaG_Program/TimeLogger/README \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/defines.h \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.c \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.h \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/DemoI2C.c \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.c \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.h \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/UpToDate \
	   file://RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/Makefile \
	   file://RT_MaG_ToolBox/ipk/Install_Inetutils \
	  "

S = "${WORKDIR}"

do_install () {
	# Welcome screen
	install -d ${D}${sysconfdir}/profile.d/
	install -m 0744 etc/profile.d/systemstat.sh 			${D}${sysconfdir}/profile.d/systemstat.sh
	install -m 0744 etc/profile.d/GoToRT-MaG_Folder.sh ${D}${sysconfdir}/profile.d/GoToRT-MaG_Folder.sh
	# RT_MaG_ToolBox folder
	install -d ${D}/home/root/RT_MaG_ToolBox/
	install -m 0744 RT_MaG_ToolBox/LoadProfile 			${D}/home/root/RT_MaG_ToolBox/LoadProfile
	install -m 0644 RT_MaG_ToolBox/RT_MaG_profile.conf	${D}/home/root/RT_MaG_ToolBox/RT_MaG_profile.conf
	# provide inetutils ipk files to install FTP
	install -d ${D}/home/root/RT_MaG_ToolBox/ipk/
	install -m 0744 RT_MaG_ToolBox/ipk/Install_Inetutils 						${D}/home/root/RT_MaG_ToolBox/ipk/Install_Inetutils
	# RT-MaG_Program folder
	install -d ${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/PutFTP 					${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/PutFTP
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/PullFTP 				${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/PullFTP
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/RunModel 				${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/RunModel
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/UpToDateModel 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/UpToDateModel
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/CompileTestModels 	${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/CompileTestModels
	# add FTP tools the /usr/bin to make them available from everywhere
	install -d ${D}${bindir}
	install -m 0755 RT_MaG_ToolBox/RT_MaG_Program/PutFTP ${D}${bindir}
	install -m 0755 RT_MaG_ToolBox/RT_MaG_Program/PullFTP ${D}${bindir}
	# TimeLogger tools
	install -d ${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/TimeLogger
	install -m 0744 RT_MaG_ToolBox/RT_MaG_Program/SendTimeLogger 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/SendTimeLogger
	install -m 0644 RT_MaG_ToolBox/RT_MaG_Program/TimeLogger/README 	${D}/home/root/RT_MaG_ToolBox/RT_MaG_Program/TimeLogger/README
	# RT_MaG_TestDev folder
	install -d ${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/
	# Test_I2C folder
	install -d ${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/defines.h 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/defines.h
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.c ${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.c
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.h ${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/library_I2C.h
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/DemoI2C.c 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/DemoI2C.c 
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.c 	${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.c
	install -m 0644 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.h 	${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/time_tools.h
	install -m 0744 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/UpToDate 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/UpToDate
	install -m 0744 RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/Makefile 		${D}/home/root/RT_MaG_ToolBox/RT_MaG_TestDev/Test_I2C/Makefile
	# Test_SPI folder
}

FILES_${PN} += " \
            /home/root/* \
            ${sysconfidir}/motd \
            ${sysconfidir}/profile.d/systemstat.sh \
            ${sysconfidir}/profile.d/term-prompt.sh \
            ${sysconfidir}/profile.d/GoToRT-MaG_Folder.sh \
            ${bindir}/* \
         "
         
