import serial
import time
from RPi import GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(23, GPIO.IN)

serSTM = serial.Serial('/dev/ttyACM0', 115200, timeout=2)  # ACM0 == STM32F103C8
serSTM.reset_input_buffer()
serNano = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)  # USB0 == Arduino Nano
serNano.reset_input_buffer()

def isLack():
    if not GPIO.input(23):
        return True
    else:
        return False
    

def resetNano():
    serNano.setDTR(False)
    time.sleep(0.5)
    serNano.setDTR(True)
    serNano.setRTS(False)
    serNano.setRTS(True)

def resetStm():
    serSTM.setDTR(False)
    time.sleep(0.5)
    serSTM.setDTR(True)
    serSTM.setRTS(False)
    serSTM.setRTS(True)

if __name__ == '__main__':
    while True:
        if isLack():
            print("ocio che xe lack")
            resetNano()
            print("Nano resettato")
            resetStm()
            print("STM resettato")
        else:
            print("tutto regolare boss")
        time.sleep(0.1)
