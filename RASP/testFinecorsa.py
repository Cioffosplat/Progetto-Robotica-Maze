import time
from RPi import GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN)

def isLack():
    if GPIO.input(23):
        return True
    else:
        return False
    
if __name__ == '__main__':
    if isLack():
        print("ocio che xe lack")
    else:
        print("tutto regolare boss")
