import serial
import time

yaapt = serial.Serial('/dev/ttyACM0', 115200)

while (True):
    num_bytes = yaapt.in_waiting
    if num_bytes:
        data = yaapt.read(num_bytes)
        print(data, num_bytes)
    else:
        time.sleep(0.2)
