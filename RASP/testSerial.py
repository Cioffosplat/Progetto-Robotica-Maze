import serial
import time


if __name__ == '__main__':

    arduino = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)  # USB0 == Arduino Nano
    arduino.reset_input_buffer()

    arduino.write("0".encode('utf-8'))
    print("sent")
    while arduino.in_waiting == 0:
        time.sleep(0.001)
    line = (arduino.readline().decode('utf-8').rstrip())
    print(line)

    print("first reset")
    arduino.setDTR(False)
    time.sleep(0.5)
    arduino.setDTR(True)
    arduino.setRTS(False)
    arduino.setRTS(True)


    arduino.write("3\n".encode('utf-8'))
    while arduino.in_waiting == 0:
        time.sleep(0.001)
    line = (arduino.readline().decode('utf-8').rstrip())
    print(line)
