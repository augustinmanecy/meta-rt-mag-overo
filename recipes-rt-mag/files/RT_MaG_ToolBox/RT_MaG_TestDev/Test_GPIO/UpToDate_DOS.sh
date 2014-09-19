################# UpToDate.sh #################
#
# This shell script allows to download/uptodate 
# and compile automatically the Test program:
#       Test_CustomBaudRate
#
# USAGE (for the first downloading, then just call: "./UpToDate.sh"):
#
# 1) On your Gumstix, type: 
#    wget ftp://overo:gumstix@192.168.137.1/TestProgram/Test_GPIO/UpToDate_DOS.sh
#              ^      ^          ^
#              |      |          |
#            login  password  server's IP
# 
# 2) Then convert your DOS file to a UNIX file:
#    sed 's/.$//' UpToDate_DOS.sh > UpToDate
#    rm UpToDate_DOS.sh
#
# 3) Make your script exectable:
#    chmod +x UpToDate
#
###############################################


#!/bin/sh

# load RT-MaG profile data
source ~/RT_MaG_ToolBox/LoadProfile
	
APPNAME=DemoGPIO
	
# remove files
	rm $APPNAME.c
	rm $APPNAME
	
# update files
	eval wget ftp://"$USER":"$PASSWD"@"$HOST"/TestProgram/Test_GPIO/Test_GPIO.c
	
# compile the program
	echo "compiling $APPNAME..."
	eval `gcc $APPNAME.c -o "$APPNAME"`
	# test if compilation has succeed 
	eval res=`ls |grep "$APPNAME"`
	if test $res=$APPNAME
	then
		echo "$APPNAME SUCCESSFULLY COMPILED!"	
	else
		echo "COMPILATION FAILED!"
	fi
	echo ""

	
