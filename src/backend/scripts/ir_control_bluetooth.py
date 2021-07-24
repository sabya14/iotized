import serial
import time
port = serial.Serial("/dev/rfcomm0",baudrate=9600)
while True:
    port.write(b'Hello World!!!\n')
    print('sent')
    time.sleep(1)