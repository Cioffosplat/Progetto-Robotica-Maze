import serial
import time
import math

from mpu6050 import mpu6050
from camera import Camera
from analysis import read_all

from Settings import const_distaces

# Initialize MPU6050 sensor
sensor = mpu6050(0x68)
# Define constant for MPU6050
RAD_TO_DEG = 57.295779513082320876798154814105

L_frontUp = 0
L_frontDown = 1
L_right = 2
L_left = 3
L_back = 4

busses = Camera.list_cameras()
r_camera = Camera('/dev/video0')
#r_camera = Camera('/dev/video2')

def get_pitch():
    accel_data = sensor.get_accel_data()
    x = accel_data['x']
    y = accel_data['y']
    z = accel_data['z']
    pitch = math.atan2(-x, math.sqrt(y*y + z*z))
    pitch_deg = pitch * RAD_TO_DEG
    if pitch_deg > 180:
        pitch_deg = pitch_deg - 360
    return pitch_deg

def isWall(millis):
    if  millis < const_distaces.WALL_MAX:
        return True
    else:
        return False


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
    
def robotSx():
    print("GIRAMENTO A SINISTRA")
    lasers = getLasers()
    ser.write("13\n".encode('utf-8'))
    if isWall(lasers[L_right]):
        print('Back adjust')
        ser.write("15\n".encode('utf-8'))
    elif isWall(lasers[L_left]):        
        print('Front adjust')
        ser.write("16\n".encode('utf-8'))

def robotDx():
    print("GIRAMENTO A DESTRA")
    lasers = getLasers()
    ser.write("12\n".encode('utf-8'))
    if isWall(lasers[L_left]):
        print('Back adjust')
        ser.write("15\n".encode('utf-8'))
    elif isWall(lasers[L_right]):
        print('Front adjust')
        ser.write("16\n".encode('utf-8'))

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

def ctrlCam():
    ls = getLasers()
    rotation = 0
    if isWall(ls[L_right]):
        read_wallR()
        rotation = -1
    if isWall(ls[L_frontDown]):
        rotation += 2
        robotSx()
        read_wallR()
    if rotation == 1:
        if isWall(ls[L_left]):
            robotSx()
            read_wallR()
    elif rotation == -1:
        if isWall(ls[L_left]):
            robotSx()
            robotSx()
            read_wallR()
            robotDx()
            robotDx()
    elif rotation == 2:
        if isWall(ls[L_left]):
            robotSx()
            read_wallR()
            robotDx()
            robotDx()
        else: 
            robotDx()
    elif rotation == 0:
        if isWall(ls[L_left]):
            robotSx()
            robotSx()
            read_wallR()
            robotDx()
            robotDx()

def blinkVictim():
    ser.write("0\n".encode('utf-8'))

def cagaMattoni(n):
    print("N mattoni + 1 :")
    print(n)
    if n > 0:
        blinkVictim()
    for i in range(n-1):
        ser.write("2\n".encode('utf-8'))

def robotBack():
    robotDx()
    robotDx()

def robotForward():
    ser.write("10\n".encode('utf-8'))

def forwardCase():
    robotForward()

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)
    ser.reset_input_buffer()
    condition = True
    while condition:
        print("\n-----CAM MOVEMENTS-----")
        ctrlCam()
        print("\n-----RUN MOVEMENTS-----")
        lasers = getLasers()
        if not isWall(lasers[L_right]):
            print("DESTRA")
            robotDx()
            forwardCase()
        elif not isWall(lasers[L_frontDown]):
            print("AVANTI")
            forwardCase()
        elif not isWall(lasers[L_left]):
            print("SINISTRA")
            robotSx()
            forwardCase()
        elif not isWall(lasers[L_back]):
            print("INDIETRO")
            robotBack()
            forwardCase()
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = (ser.readline().decode('utf-8').rstrip())
        print("result of movement :")
        print(line)
        print("\n")
        if line == "0":
            robotBack()
        if line == "11":
            time.sleep(5)
