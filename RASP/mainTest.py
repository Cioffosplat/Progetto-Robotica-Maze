import serial
import time

from RPi import GPIO
from Settings import const_distaces

#tipo di riferimento, numerazione della cpu
#GPIO.setmode(GPIO.BCM)
#GPIO.setup(23, GPIO.IN)
#GPIO.setup(25, GPIO.OUT)
#GPIO.output(25, GPIO.HIGH)
# L_frontUp = 0
# L_frontDown = 1
# L_right = 2
# L_left = 3
# L_back = 4

#L_front_L = 0
L_front_R = 0
L_right_R = 1
L_back_R= 2
L_back_L = 3
L_left_R = 4

laserName =  ["L_front_R", "L_right_R", "L_back_R", "L_back_L", "L_left_R"]

# /dev/ttyACM0 is STM32F103C8
# /dev/ttyUSB0 is Arduino Nano

#def isLack():
#    if not GPIO.input(23):
#        return True
#    else:
#        return False

def isWall(millisL, millisR):
    if millisR < const_distaces.WALL_MAX and millisL < const_distaces.WALL_MAX:
        return True
    else:
        return False


def getNano():
    serNano.write("0\n".encode('utf-8'))
    while serNano.in_waiting == 0:
        time.sleep(0.001)
    line = float((serNano.readline().decode('utf-8').rstrip()))
    return line


def robotSinistra():
    print("GIRAMENTO A SINISTRA")
    angle = getNano()
    finish = angle + 90
    if finish >= 180:
        finish = -180 + (finish - 180)
    serSTM.write("13\n".encode('utf-8'))
    while not (angle > (finish -1) and angle < (finish +1)):
        angle = getNano()
        # print(angle)
    serSTM.write("1\n".encode('utf-8'))
    lasers = getLasers()
    if isWall(lasers[L_back_R], lasers[L_back_L]):
        print("Back adjust")
        serSTM.write("15\n".encode('utf-8'))
    elif isWall(lasers[L_front_R], lasers[L_front_R]):
        print("Front adjust")
        serSTM.write(("16\n".encode('utf-8')))


def robotDestra():
    print("GIRAMENTO A DESTRA")
    angle = getNano()
    finish = angle - 90
    if finish <= - 180:
        finish = 180 + (finish + 180)
    serSTM.write("12\n".encode('utf-8'))
    while not (angle > (finish -1) and angle < (finish +1)):
        angle = getNano()
        # print(angle)
    serSTM.write("1\n".encode('utf-8'))
    lasers = getLasers()
    if isWall(lasers[L_back_R], lasers[L_back_L]):
        print("Back adjust")
        serSTM.write("15\n".encode('utf-8'))
        print("inviato seriale")
    elif isWall(lasers[L_front_R], lasers[L_front_R]):
        print("Front adjust")
        serSTM.write(("16\n".encode('utf-8')))


def getLasers():
    serSTM.write("3\n".encode('utf-8'))
    print("get lasers")
    lasers = []
    for i in range(5):
        while serSTM.in_waiting == 0:
            time.sleep(0.002)
        line = float((serSTM.readline().decode('utf-8').rstrip()))
        print(laserName[i] + ": " + str(line))
        lasers.append(line)
    return lasers


def robotAvanti():
    serSTM.write("10\n".encode('utf-8'))


def robotIndietro():
    print("primo seriale")
    robotDestra()
    print("secondo seriale")
    robotDestra()
    print("finito il metodo indietro")


if __name__ == '__main__':
    condition = False
    while not condition:
        try:
            print("Serial STM")
            serSTM = serial.Serial('/dev/ttyACM0', 115200, timeout=2)  # ACM0 == STM32F103C8
            serSTM.reset_input_buffer()
            print("Serial Nano")
            serNano = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)  # USB0 == Arduino Nano
            time.sleep(5)
            serNano.reset_input_buffer()
            condition = True
        except:
            print("Serial waiting")
    while condition:
            print("inizio loop")
            lasers = getLasers()

            if not isWall(lasers[L_right_R], lasers[L_right_R]):
                print("DESTRA")
                robotDestra()
                robotAvanti()
            elif not isWall(lasers[L_front_R], lasers[L_front_R]):
                print("AVANTI")
                robotAvanti()
            elif not isWall(lasers[L_left_R], lasers[L_left_R]):
                print("SINISTRA")
                robotSinistra()
                robotAvanti()
            elif not isWall(lasers[L_back_L], lasers[L_back_R]):
                print("INDIETRO")
                robotIndietro()
                robotAvanti()

            while serSTM.in_waiting == 0:
                #if isLack():
                #    isBreaked = True
                #    break
                time.sleep(0.005)

            line = (serSTM.readline().decode('utf-8').rstrip())
            print("result of movement :")
            print(line)
            print("\n")
            if line == "0":
                print("go back because of black")
                robotIndietro()
            if line == "11":
                print("stop because of blue")
                time.sleep(5)
