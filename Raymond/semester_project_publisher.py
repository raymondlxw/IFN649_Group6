import serial
import time
import string
import paho.mqtt.publish as publish

# read and write data from and to arduino serially
# input the correct rf channel into the parameter, rfcomm0 is normally the defult for the first connection
# input the IP address of the aws broker

ser = serial.Serial("/dev/rfcomm0", 9600)
ipaddr = ""

while True:
    if ser.in_waiting > 0:
        rawserial = ser.readline()
        rawstring = rawserial.decode('utf8').strip('\r\n')

        # Split the whole string in to a list and take out the information needed

        x = rawstring.strip().split()

        # input the index of each information

        wind = x[]  # Insert wind speed index here

        humid = x[1].split("%")
        temp = x[3].split("C")
        light = x[17]
        print(" ")

        # ----------------------Final form of the required data ---------------------------

        wd = ()  # Insert wind speed information here

        th = ("humidity: " + str(humid[0]) + " Temperature: " + str(temp[0]))
        li = ("Light intensity: " + light)
        print(th + li)

        # ----------------------Set Threshold Control---------------------------------------
        # Set threshold control
        nmsg = "threshold has not been set yet!!!"

        # ----------------------Publish the Information-------------------------------------
        publish.single("group6Data", th+li, hostname="3.25.68.204")
        print("Done")
        publish.single("group6Notification", nmsg, hostname="3.25.68.204")
        print("Done")
