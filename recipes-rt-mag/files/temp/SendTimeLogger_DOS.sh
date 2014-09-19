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

################# SendTimeLogger_DOS.sh #################
#
# This shell script allows to put an archive conitaining
# all the data about the Time Logger activated during a 
# RT-MaG model's execution:
#    + TimeLogger.zip
#    |--- TimeLogger_Task0.csv : ';' delimited file with Task0' data
#    |--- ... 
#    |--- TimeLogger_TaskN.csv : ';' delimited file with Task0' data
#    |--- top-output.txt       : text file with the CPU history of each PID (results of top command)
#    |--- README.txt           : text file with instructions to plot these data in MATLAB
#
# USAGE (for the first downloading):
#
# 1) On your Gumstix, type: 
#    wget ftp://overo:gumstix@192.168.137.1/SendTimeLogger_DOS.sh
#              ^      ^          ^
#              |      |          |
#            login  password  server's IP
# 
# 2) Then convert your DOS file to a UNIX file:
#    sed 's/.$//' SendTimeLogger_DOS.sh > SendTimeLogger
#    rm SendTimeLogger_DOS.sh
#
# 3) Make your script exectable:
#    chmod +x SendTimeLogger
#
###############################################

#!/bin/sh

HOST='192.168.137.3'
USER='overo'
PASSWD='gumstix'

#tar -zcvf TimeLogger.tar.gz TempTimeLoggerDir
zip -r TimeLogger.zip TimeLogger

ftp -n -v $HOST << EOT
user $USER $PASSWD
prompt
binary
put TimeLogger.zip
bye
EOT

#rm TimeLogger.tar.gz
rm TimeLogger.zip
