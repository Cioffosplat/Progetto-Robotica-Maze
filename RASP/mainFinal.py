import serial
import time
import math

from camera import Camera
from analysis import read_all

from RPi import GPIO
from Settings import const_distaces

#tipo di riferimento, numerazione della cpu
GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN)

#Lasers
L_front_R = 0
L_front_L = 1
#L_left_R = 2 removed for now cause of hardware problems
L_left_L = 2
L_back_L = 3
L_back_R = 4
L_right_R = 5

laserName = ["L_front_R", "L_front_L", "L_left_L", "L_back_L", "L_back_R", "L_right_R"]

#cameras
busses = Camera.list_cameras()
r_camera = Camera('/dev/video0')

# /dev/ttyACM0 is STM32F103C8
# /dev/ttyUSB0 is Arduino Nano

def isLack():
    if not GPIO.input(23):
        return True
    else:
        return False

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

def isRamp(dist):
    if (dist > const_distaces.WALL_MIN and dist < const_distaces.WALL_MAX):
        return True
    else:
        return False

def rampRide():
    print("RIDING RAMP")
    lasers = getLasers()
    serSTM.write("14\n".encode('utf-8'))
    while True:
        lasers = getLasers()
        if not isWall(lasers[L_left_L], lasers[L_right_R]):
            serSTM.write("7\n".encode('utf-8'))
            break
        lasers = getLasers()
    return "101"  


def read_wallR():
    print("lettura cum")
    time.sleep(1.5)
    out = 0
    letter, color = read_all(r_camera)
    print(f'R: letter({letter}) color({color})')
    out += {'': 0, 'g': 1, 'y': 2, 'r': 2}[color]
    if out == 0:
        out += {'': 0, 'u': 1, 's': 3, 'h': 4}[letter]
    print("numero mattoni")
    print(out)
    cagaMattoni(out)


def robotSinistra():
    print("GIRAMENTO A SINISTRA")
    angle = getNano()
    finish = angle - 90
    if finish >= 180:
        finish = -180 + (finish - 180)
    serSTM.write("13\n".encode('utf-8'))
    while not (angle > (finish -1) and angle < (finish +1)):
        angle = getNano()
        print(angle)
    serSTM.write("1\n".encode('utf-8'))
    lasers = getLasers()
    if isWall(lasers[L_back_R], lasers[L_back_L]):
        print("Back adjust")
        serSTM.write("15\n".encode('utf-8'))
    elif isWall(lasers[L_front_R], lasers[L_front_L]):
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
        print(angle)
    serSTM.write("1\n".encode('utf-8'))
    lasers = getLasers()
    if isWall(lasers[L_back_R], lasers[L_back_L]):
        print("Back adjust")
        serSTM.write("15\n".encode('utf-8'))
        print("inviato seriale")
    elif isWall(lasers[L_front_R], lasers[L_front_L]):
        print("Front adjust")
        serSTM.write(("16\n".encode('utf-8')))

def getLasers():
    serSTM.write("3\n".encode('utf-8'))
    print("get lasers")
    lasers = []
    for i in range(6):
        while serSTM.in_waiting == 0:
            time.sleep(0.002)
        line = float((serSTM.readline().decode('utf-8').rstrip()))
        print(laserName[i] + str(line))
        lasers.append(line)
    return lasers

def ctrlCam():
    ls = getLasers()
    rotation = 0
    if isWall(ls[L_right_R],ls[L_right_R]):
        read_wallR()
        rotation = -1
    if isWall(ls[L_front_R], ls[L_front_L]):
        rotation += 2
        robotSinistra()
        read_wallR()
    if rotation == 1:
        if isWall(ls[L_left_L], ls[L_left_L]):
            robotSinistra()
            read_wallR()
    elif rotation == -1:
        if isWall(ls[L_left_L], ls[L_left_L]):
            robotSinistra()
            robotSinistra()
            read_wallR()
            robotDestra()
            robotDestra()
    elif rotation == 2:
        if isWall(ls[L_left_L], ls[L_left_L]):
            robotSinistra()
            read_wallR()
            robotDestra()
            robotDestra()
        else:
            robotDestra()
    elif rotation == 0:
        if isWall(ls[L_left_L], ls[L_left_L]):
            robotSinistra()
            robotSinistra()
            read_wallR()
            robotDestra()
            robotDestra()

def blinkVictim():
    serSTM.write("0\n".encode('utf-8'))

def cagaMattoni(n):
    print("N mattoni + 1 :")
    print(n)
    if n > 0:
        blinkVictim()
    for i in range(n-1):
        serSTM.write("2\n".encode('utf-8'))

def robotBack():
    robotDestra()
    robotDestra()

def robotForward():
    serSTM.write("10\n".encode('utf-8'))


if __name__ == '__main__':
    reset = False
    isBreaked = False
    print("Serial STM")
    serSTM = serial.Serial('/dev/ttyACM0', 115200, timeout=2)  # ACM0 == STM32F103C8
    serSTM.reset_input_buffer()
    print("Serial Nano")
    serNano = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)  # USB0 == Arduino Nano
    serNano.reset_input_buffer()
    while True:
        while not isLack():
            print("\n-----CAM MOVEMENTS-----")
            ctrlCam()
            print("\n-----RUN MOVEMENTS-----")
            lasers = getLasers()
            if not isWall(lasers[L_right_R], lasers[L_right_R]):
                print("DESTRA")
                robotDestra()
                robotForward()
            elif not isWall(lasers[L_front_L], lasers[L_front_R]):
                print("AVANTI")
                robotForward()
            elif not isWall(lasers[L_left_L], lasers[L_left_L]):
                print("SINISTRA")
                robotSinistra()
                robotForward()
            elif not isWall(lasers[L_back_L], lasers[L_back_R]):
                print("INDIETRO")
                robotBack()
                robotForward()
            
            while serSTM.in_waiting == 0:
                if isLack():
                    isBreaked = True
                    break
            if not isBreaked:
                line = (serSTM.readline().decode('utf-8').rstrip())
                print("result of movement :")
                print(line)
                print("\n")
                if line == "0":
                    print("go back because of black")
                    robotBack()
                if line == "11":
                    print("stop because of blue")
                    time.sleep(5)
            else:
                break
        if isLack():
            print("-----LACK OF PROGRESS-----")
            print("Resetting STM")
            print("\n")
            serSTM.setDTR(False)
            time.sleep(0.5)
            serSTM.setDTR(True)
            serSTM.setRTS(False)
            serSTM.setRTS(True)
            print("Resetting Nano")
            print("\n")
            serNano.setDTR(False)
            time.sleep(0.5)
            serNano.setDTR(True)
            serNano.setRTS(False)
            serNano.setRTS(True)
            while isLack():
                print("Waiting for Lack Button")
                time.sleep(0.5)
