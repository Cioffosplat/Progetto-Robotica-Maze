import serial
import time

from Settings import const_distaces

# L_frontUp = 0
# L_frontDown = 1
# L_right = 2
# L_left = 3
# L_back = 4

L_front_L = 0
L_front_R = 1
L_right_L = 2
L_right_R = 3
L_back_R = 4
L_back_L = 5
L_left_L = 6
L_left_R = 7



def isWall(millisL, millisR):
    if (millisR + millisL) < (const_distaces.WALL_MAX * 2):
        return True
    else:
        return False


def robotSinastra():
    ser.write("13\n".encode('utf-8'))
    if isWall(lasers[L_right_L], lasers[L_right_R]):
        ser.write("15\n".encode('utf-8'))


def robotDestra():
    ser.write("12\n".encode('utf-8'))
    if isWall(lasers[L_left_L], lasers[L_left_R]):
        ser.write("15\n".encode('utf-8'))


def getLasers():
    ser.write("3\n".encode('utf-8'))
    print("get lasers")
    lasers = []
    for i in range(8):
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
    condition = False
    while not condition:
        try:
            ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)
            ser.reset_input_buffer()
            condition = True
        except:
            print("Serial waiting")
    while condition:
        lasers = getLasers()
        if not isWall(lasers[L_right_L], lasers[L_right_R]):
            print("DESTRA")
            robotDestra()
            robotAvanti()
        elif not isWall(lasers[L_front_L], lasers[L_front_R]):
            print("AVANTI")
            robotAvanti()
        elif not isWall(lasers[L_left_L], lasers[L_left_R]):
            print("SINISTRA")
            robotSinastra()
            robotAvanti()
        elif not isWall(lasers[L_back_L], lasers[L_back_R]):
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
