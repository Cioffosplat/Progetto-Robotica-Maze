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

# Main loop example to implement in the code
#while True:
    #pitch = get_pitch()
    #print("Pitch: {:.2f}".format(pitch))
    #time.sleep(0.1)

def isWall(millis):
    if  millis < const_distaces.WALL_MAX:
        return True
    else:
        return False

#def read_wallsL():
#    time.sleep(1.5)
#    out = 0
#    letter, color = read_all(l_camera)
#    print(f'L: letter({letter}) color({color})')
#    out += {'': 0, 'g': 1, 'y': 2, 'r': 2}[color]
#    if out == 0:
#        out += {'': 0, 'u': 0, 's': 0, 'h': 0}[letter]
#    if out > 0:
#        return out << 4


def read_wallsR():
    time.sleep(1.5)
    out = 0
    letter, color = read_all(r_camera)
    print(f'R: letter({letter}) color({color})')
    out += {'': 0, 'g': 1, 'y': 2, 'r': 2}[color]
    if out == 0:
        out += {'': 0, 'u': 0, 's': 0, 'h': 0}[letter]
    if out > 0:
        return out << 4


def robotSinistra():
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


def ctrlCam():
    print('zio pera')


def robotIndietro():
    ser.write("12\n".encode('utf-8'))
    ser.write("15\n".encode('utf-8'))
    ser.write("12\n".encode('utf-8'))
    ser.write("15\n".encode('utf-8'))


def forwardCase():
    ls = getLasers()
    up = ls[L_frontUp]
    down = ls[L_frontDown]
    if()

if __name__ == '__main__':
    time.sleep(5)
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)
    ser.reset_input_buffer()
    condition = True
    while condition:
        ctrlCam()
        lasers = getLasers()
        if not isWall(lasers[L_right]):
            print("DESTRA")
            robotDestra()
            forwardCase()
        elif not isWall(lasers[L_frontUp]):
            print("AVANTI")
            forwardCase()
        elif not isWall(lasers[L_left]):
            print("SINISTRA")
            robotSinistra()
            forwardCase()
        elif not isWall(lasers[L_back]):
            print("INDIETRO")
            robotIndietro()
            forwardCase()
        while ser.in_waiting == 0:
            time.sleep(0.001)
        line = (ser.readline().decode('utf-8').rstrip())
        print(line)
        if line == "0":
            robotIndietro()
        if line == "11":
            time.sleep(5)

