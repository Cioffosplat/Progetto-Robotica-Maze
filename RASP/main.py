import serial
import time

from Settings import const_distaces

L_frontUp = 0
L_frontDown = 1
L_right = 2
L_left = 3
L_back = 4

def isNotWall(millis):
    if  millis < const_distaces.WALL_MAX:
        return False
    else:
        return True


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)
    ser.reset_input_buffer()
    condition = True
    while condition:
        ser.write("3\n".encode('utf-8'))
        if ser.in_waiting > 0:
            line = (ser.readline().decode('utf-8').rstrip())
            lasers = line.split(";")
            if isNotWall(lasers[L_right]):
                ser.write("12\n".encode('utf-8'))
            elif isNotWall(lasers[L_frontDown]):
                ser.write("10\n".encode('utf-8'))
            elif isNotWall(lasers[L_left]):
                ser.write("13\n".encode('utf-8'))
            else:
                ser.write("11\n".encode('utf-8'))
            while ser.in_waiting == 0:
                time.sleep(0.5)
            line = (ser.readline().decode('utf-8').rstrip())
            if line == "11":
                time.sleep(5)

