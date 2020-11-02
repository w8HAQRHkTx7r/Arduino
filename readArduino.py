import os
from adafruitKey import ADAFRUITKEY, ADAFRUITUSERNAME
import datetime

try:
	modem = input()
except:
	print("Abort. No modem found.")
	exit(1)

print(modem)

ADAFRUITFEED = "https://io.adafruit.com/api/v2/macewmi/feeds/hfurnace/data"

import serial

#arduino = serial.Serial('/dev/tty.usbmodem14301',9600)
arduino = serial.Serial(modem, 9600)

while True:
	timestamp = datetime.datetime.now().strftime("%Y/%m/%d %H:%M:%S")
	reading = arduino.readline()
	dataLen = len(reading)
	decoded_values = str(reading[0:dataLen].decode("utf-8")).strip()
#	print(timestamp, decoded_values)
	command = f"curl -F 'value={decoded_values}' -H 'X-AIO-Key: {ADAFRUITKEY}' {ADAFRUITFEED} > /dev/null 2>&1"
	result = os.system(command)
	if result != 0:
		print(result)
		exit(2)
		
arduino.close()
