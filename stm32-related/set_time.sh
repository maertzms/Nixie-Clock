#!/usr/bin/env bash
prog=1
#read -p "Enter uart device for setting time\nShould be similar to /dev/ttyUSB0: " uart_dev
uart_dev="/dev/ttyACM0"
#echo $uart_dev
stty 9600 -F $uart_dev
current_time=$(date "+%H %M %S")
echo $current_time
curr_hour=$(date +%H)
curr_min=$(date +%M)
#echo $curr_hour
#echo $curr_min
#echo $curr_sec
delay=0.2

if [ $prog -eq 1 ]
then
	echo "Set Time" > $uart_dev
    sleep $delay
	echo $curr_hour > $uart_dev
    sleep $delay
	echo $curr_min > $uart_dev
    sleep $delay
	curr_sec=$(date +%S)
    sleep $delay
	echo $curr_sec > $uart_dev
else
    curr_hour=$(date +%H)
    echo ${#curr_hour}
    curr_min=$(date +%M)
    echo ${#curr_min}
    curr_sec=$(date +%S)
	echo ${#curr_sec}
	echo "nothing programmed"
fi
