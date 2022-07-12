import RPi.GPIO as gpio
from time import sleep
import sys, signal

#Tens Hours
# D:37 C:35 B:33 A:31
#Ones Hours
# D:40 C:36 B:32 A:38

#Tens Mins
# D:29 C:24 B:21 A:26
#Ones Mins
# D:22 C:23 B:18 A:19

#Tens Secs
# D:15 C:11 B:13 A:16
#Ones Secs
# D:8 C:10 B:12 A:7

terminate = False
def signalHandler(signum, frame):
    global terminate
    terminate = True

signal.signal(signal.SIGINT, signalHandler)

class Digit:
    # LSB -> MSB  A->D
    def __init__(self, bits, locA=3, locB=3, locC=3, locD=3):
        self.A = bits[0]
        self.B = bits[1]
        self.C = bits[2]
        self.D = bits[3]
        self.locA = locA
        self.locB = locB
        self.locC = locC
        self.locD = locD

    def setBits(self, bits):
        self.A = bits[0]
        self.B = bits[1]
        self.C = bits[2]
        self.D = bits[3]

    def assignBits(self):
        gpio.output(self.locA, self.A)
        gpio.output(self.locB, self.B)
        gpio.output(self.locC, self.C)
        gpio.output(self.locD, self.D)

    def getBits(self):
        return [self.A, self.B, self.C, self.D]

def intToBits(num):
    if num == 0:
        return [0, 0, 0, 0]
    if num == 1:
        return [0, 0, 0, 1]
    if num == 2:
        return [0, 0, 1, 0]
    if num == 3:
        return [0, 0, 1, 1]
    if num == 4:
        return [0, 1, 0, 0]
    if num == 5:
        return [0, 1, 0, 1]
    if num == 6:
        return [0, 1, 1, 0]
    if num == 7:
        return [0, 1, 1, 1]
    if num == 8:
        return [1, 0, 0, 0]
    if num == 9:
        return [1, 0, 0, 1]

bits = [0, 0, 0, 0]

TH = Digit(bits, 31, 33, 35, 37)
OH = Digit(bits, 38, 32, 36, 40)

TM = Digit(bits, 26, 21, 24, 29)
OM = Digit(bits, 19, 18, 23, 22)

TS = Digit(bits, 16, 13, 11, 15)
OS = Digit(bits, 7,  12, 10, 8)

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
    if terminate:
        print("\tI'll see myself out")
        break
    """
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
    """
    n = x % 10
#    tstbits = intToBits(n)
    TH.setBits(intToBits(n))
    TH.assignBits()
    print(n, "\t", TH.getBits(), "\t") #, end='\r')
    sleep(0.25)

print("end")


#ending cleanup
gpio.cleanup()
