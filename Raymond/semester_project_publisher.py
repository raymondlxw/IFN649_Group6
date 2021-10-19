import serial
import time
import sys
import string
import paho.mqtt.publish as publish
from sense_hat import SenseHat

# read and write data from and to arduino serially
# input the correct rf channel into the parameter, rfcomm0 is normally the defult for the first connection
# input the IP address of the aws broker

ser = serial.Serial("/dev/rfcomm0", 9600)

# using sense hat led as indicator
sense = SenseHat()
# setting colors
red = (255, 0, 0)
green = (0, 255, 0)
yellow = (255, 255, 0)


while True:
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        rawstring = rawserial.decode('utf8').strip('\r\n')

        # Split the whole string in to a list and take out the information needed

        x = rawstring.strip().split()

        # input the index of each information

        # wind = x[] #Insert wind speed index here

        humid = x[1].split("%")
        temp = x[3].split("C")
        light = x[17]
        print(" ")

        # ----------------------Final form of the required data ---------------------------

        # wd = () # Insert wind speed information here

        th = ("humidity: " + str(humid[0]) + " Temperature: " + str(temp[0]))
        li = ("Light intensity: " + light)
        print(th + li)

        # ----------------------Set Threshold Control---------------------------------------
        # Set threshold control
        H = float(humid[0])
        T = float(temp[0])
        L = float(light)

        if (H < 70 and T > 20 and L > 140):
            nmsg = "The weather right now is suitable for drying laundry!!!"
            sense.show_letter("Y", green)
        elif (H < 70 and T > 30 and L > 550):
            nmsg = "Go do your laundry now!!! The weather is great!!!"
            sense.show_letter("G", yellow)
        else:
            nmsg = "Ops, the weather is not too good right now, you might want to do laundry at another time."
            sense.show_letter("N", red)

        print(nmsg)

        # ----------------------Publish the Information-------------------------------------
        publish.single("group6Data", th+li, hostname="3.25.68.204")
        print("Done")
        publish.single("group6Notification", nmsg, hostname="3.25.68.204")
        print("Done")

        # ---------------------Sleep 3 seconds and clean the sense hat ---------------------
        # ---------------------KeyboardInterrupt to quit the program -----------------------
        try:
            # if there is time control in the teensy code, this line can be removed
            time.sleep(3)

        except KeyboardInterrupt:
            sense.clear()
            sys.exit()
