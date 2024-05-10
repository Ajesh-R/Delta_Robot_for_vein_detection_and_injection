import serial
import time 
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
x_str = str(-190).zfill(3)+"\n"
y_str = str(-100).zfill(3)+"\n"

print(x_str.encode('utf-8'))
print(y_str.encode('utf-8'))

ser.write(b"000\n")
time.sleep(1)

ser.write(x_str.encode('utf-8'))
ser.write(y_str.encode('utf-8'))
ser.write("-230".encode('utf-8'))

#ser.write(str(x_str.zfill(3)).encode('utf-8'))
#ser.write(str(y_str.zfill(3)).encode('utf-8'))
#ser.write(b"-300\n")



#ser.write(b"000\n")
#time.sleep(1)
#ser.write(b"000\n")
#ser.write(b"000\n")
#ser.write(b"-300\n")
