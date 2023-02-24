import serial
import time

from Settings import const_distaces

L_frontUp = 0
L_frontDown = 1
L_right = 2
L_left = 3
L_back = 4

def isWall(millis):
    if  millis < const_distaces.WALL_MAX:
        return True
    else:
        return False


def robotSinastra():
    ser.write("13\n".encode('utf-8'))
    if isWall(lasers[L_right]):
        ser.write("15\n".encode('utf-8'))


def robotDestra():
    ser.write("12\n".encode('utf-8'))
    if isWall(lasers[L_left]):
        ser.write("15\n".encode('utf-8'))


def getLasers():
    ser.write("3\n".encode('utf-8'))
    print("get lasers")
    lasers = []
    for i in range(5):
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = float((ser.readline().decode('utf-8').rstrip()))
        print("laser = " + str(line))
        lasers.append(line)
    return lasers


def robotAvanti():
    ser.write("10\n".encode('utf-8'))


def robotIndietro():
    ser.write("12\n".encode('utf-8'))
    ser.write("15\n".encode('utf-8'))
    ser.write("12\n".encode('utf-8'))
    ser.write("15\n".encode('utf-8'))
    ser.write("10\n".encode('utf-8'))


if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)
    ser.reset_input_buffer()
    condition = True
    while condition:
        lasers = getLasers()
        if not isWall(lasers[L_right]):
            print("DESTRA")
            robotDestra()
            robotAvanti()
        elif not isWall(lasers[L_frontUp]):
            print("AVANTI")
            robotAvanti()
        elif not isWall(lasers[L_left]):
            print("SINISTRA")
            ser.write("13\n".encode('utf-8'))
            if isWall(lasers[L_right]):
                ser.write("15\n".encode('utf-8'))
            ser.write("10\n".encode('utf-8'))
        elif not isWall(lasers[L_back]):
            print("INDIETRO")
            robotIndietro()
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = (ser.readline().decode('utf-8').rstrip())
        print(line)
        if line == "0":
            robotIndietro()
        if line == "11":
            time.sleep(5)


