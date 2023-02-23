import serial
import time

from camera import Camera
from analysis import read_all

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
    lasers = []
    while condition:
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = (ser.readline().decode('utf-8').rstrip())
        print(line)
        if line == "READY":
            condition = False
    condition = True
    while condition:
        ser.write("3\n".encode('utf-8'))
        print(3)
        lasers = []
        for i in range(5):
            while ser.in_waiting == 0:
                time.sleep(0.001)
            line = (ser.readline().decode('utf-8').rstrip())
            print("laser " + i + " = " + line)
            lasers.append(line)
        if isNotWall(lasers[L_right]):
            print("DESTRA")
            ser.write("12\n".encode('utf-8'))
            if not isNotWall(lasers[L_left]):
                ser.write("15\n".encode('utf-8'))
            ser.write("10\n".encode('utf-8'))
        elif isNotWall(lasers[L_frontDown]):
            print("AVANTI")
            ser.write("10\n".encode('utf-8'))
        elif isNotWall(lasers[L_left]):
            print("SINISTRA")
            ser.write("13\n".encode('utf-8'))
            if not isNotWall(lasers[L_right]):
                ser.write("15\n".encode('utf-8'))
            ser.write("10\n".encode('utf-8'))
        elif isNotWall(lasers[L_back]):
            print("INDIETRO")
            ser.write("12\n".encode('utf-8'))
            ser.write("15\n".encode('utf-8'))
            ser.write("12\n".encode('utf-8'))
            ser.write("15\n".encode('utf-8'))
            ser.write("10\n".encode('utf-8'))
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = (ser.readline().decode('utf-8').rstrip())
        print(line)
        if line == "0":
            ser.write("12\n".encode('utf-8'))
            ser.write("15\n".encode('utf-8'))
            ser.write("12\n".encode('utf-8'))
            ser.write("15\n".encode('utf-8'))
            ser.write("10\n".encode('utf-8'))
        if line == "11":
            time.sleep(5)

