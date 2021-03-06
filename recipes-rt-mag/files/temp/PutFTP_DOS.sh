################## RunModel.sh #################
#
# This shell script allows to put a file (given in argument)
# 
#
# USAGE (for the first downloading):
#
# 1) On your Gumstix, type: 
#    wget ftp://overo:gumstix@192.168.137.1/PutFTP_DOS.sh
#              ^      ^          ^
#              |      |          |
#            login  password  server's IP
# 
# 2) Then convert your DOS file to a UNIX file:
#    sed 's/.$//' PutFTP_DOS.sh > PutFTP
#    rm PutFTP_DOS.sh
#
# 3) Make your script exectable:
#    chmod +x PutFTP
#
###############################################

#!/bin/sh

HOST='192.168.137.1'
USER='overo'
PASSWD='gumstix'

if test $# -lt 1
	then
		echo "SYNTAX ERROR: $0 <file name 1> <file name 2>"
fi

ftp -n -v $HOST << EOT
user $USER $PASSWD
prompt
ascii
put $1
bye
EOT
