import serial
import time 
import string 
import paho.mqtt.publish as publish 

#read and write data from and to arduino serially 
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
		wind = x[]
		humid = x[].split("%")
		temp = x[].split("C")
		light = x[]
		print(" ")

		#Set threshold control 

		
