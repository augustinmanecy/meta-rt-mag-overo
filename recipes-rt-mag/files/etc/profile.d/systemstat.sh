#!/bin/bash

let upSeconds="$(/usr/bin/cut -d. -f1 /proc/uptime)"
let secs=$((${upSeconds}%60))
let mins=$((${upSeconds}/60%60))
let hours=$((${upSeconds}/3600%24))
let days=$((${upSeconds}/86400))
UPTIME=`printf "%02dh%02dm" "$hours" "$mins" `

function getip { /sbin/ifconfig $1 | grep "inet addr" | awk -F ":" '{print $2}' | awk '{print $1}';}
chmod 777 /etc/wpa_supplicant.conf
function getssid { cat /etc/wpa_supplicant.conf | grep "ssid" | awk -F "\"" '{print $2}' | awk '{print $1}';}
chmod 644 /etc/wpa_supplicant.conf

WifiIP=$(getip wlan0)
SSID=$(getssid)

#load profile info
N=1
while test "$N" -le "4"
do
	N=$(($N+1))
	IFS=: read HOST USER PASSWD
done < ~/RT_MaG_ToolBox/RT_MaG_profile.conf

echo "Uptime....................: ${UPTIME}
Free Disk Space...........: `df -Ph . | awk 'NR==2 {print $4}'`
Wifi IP address (wlan0)...: $WifiIP
Wifi SSID (wlan0).........: $SSID
RT-MaG FTP profile:
    RT-MaG FTP server.....: $HOST
    RT-MaG FTP username...: $USER
" 
