import serial
import time

def sendData(posX, posY):
	posX = int((0-(posX/15 - 10))*10)
	posY = int((0-(posY/15 - 1))*10)
	print(posX)
	print(posY)
	ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
	x_str = str(posX).zfill(3)+"\n"
	y_str = str(posY).zfill(3)+"\n"
	
	
	print(x_str.encode('utf-8'))
	print(y_str.encode('utf-8'))
	
	ser.write(b"000\n")
	time.sleep(1)
	ser.write(str(x_str.zfill(3)).encode('utf-8'))
	ser.write(str(y_str.zfill(3)).encode('utf-8'))
	ser.write(b"-300\n")

