let upSeconds="$(/usr/bin/cut -d. -f1 /proc/uptime)"
let secs=$((${upSeconds}%60))
let mins=$((${upSeconds}/60%60))
let hours=$((${upSeconds}/3600%24))
let days=$((${upSeconds}/86400))
UPTIME=`printf "%02dh%02dm" "$hours" "$mins" `

echo "
Uptime.............: ${UPTIME}
Free Disk Space....: `df -Ph . | awk 'NR==2 {print $4}'`
" 
