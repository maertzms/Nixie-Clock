#from time import localtime, strftime, sleep
import time

for i in range(1, 100):
    my_time = time.localtime()
    print("Local time =", time.strftime("H:%M:%S", time.localtime()))
    hour, minute, second = my_time[3], my_time[4], my_time[5]
#    hour, minute, second = time.localtime()[3], time.localtime()[4], time.localtime()[5]
    th, uh = hour//10, hour%10
    tm, um = minute//10, minute%10
    ts, us = second//10, second%10
    print(str(th), str(uh), ":", str(tm), str(um), ":", str(ts), str(us))
    print('{0:04b}'.format(th), '{0:04b}'.format(uh))

    time.sleep(0.5)
