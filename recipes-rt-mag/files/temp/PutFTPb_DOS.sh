###########################################################################
#
# Author: Augustin Manecy
#
# Copyright (C) 2011-2014 Augustin Manecy
#
# augustin.manecy@gmail.com
#
###########################################################################
#
# This file is part of RT-MaG Toolbox.
#
#   RT-MaG Toolbox is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   RT-MaG Toolbox is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with RT-MaG Toolbox.  If not, see <http://www.gnu.org/licenses/>.
#
###########################################################################
#
# This version of GPL is at https://www.gnu.org/licenses/gpl-3.0.txt
#
###########################################################################

################# PutFTPb_DOS.sh #################
#
# This shell script allows to put a file (given in argument) 
# in binary mode to the remote FTP server 
# 
#
# USAGE (for the first downloading):
#
# 1) On your Gumstix, type: 
#    wget ftp://overo:gumstix@192.168.137.1/PutFTPb_DOS.sh
#              ^      ^          ^
#              |      |          |
#            login  password  server's IP
# 
# 2) Then convert your DOS file to a UNIX file:
#    sed 's/.$//' PutFTPb_DOS.sh > PutFTPb
#    rm PutFTPb_DOS.sh
#
# 3) Make your script exectable:
#    chmod +x PutFTPb
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
binary
put $1
bye
EOT
