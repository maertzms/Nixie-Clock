import RPi.GPIO as gpio
from time import sleep

#setup
print("init")
gpio.setmode(gpio.BOARD)
gpio.setwarnings(True)
chan_list = [3, 5, 7, 8, 10, 11, 12, 13, 15, 16, 18, 19,\
 21, 22, 23, 24, 26, 29, 31, 32, 33, 35, 36, 37, \
 38, 40]
gpio.setup(chan_list, gpio.OUT)


print("start")
gpio.output(chan_list, gpio.LOW)

#main loop
for x in range(100):
    print("on")
    gpio.output(chan_list, gpio.HIGH)
    sleep(0.5)
    print("off")
    gpio.output(chan_list, 0)
    sleep(0.5)
    print("on")
    gpio.output(chan_list, True)
    sleep(0.5)
    print("off")
    gpio.output(chan_list, False)
    sleep(0.5)

print("end")


#ending cleanup
gpio.cleanup()
