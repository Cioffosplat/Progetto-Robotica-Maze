import serial
import time


if __name__ == '__main__':
    stm32 = serial.Serial('/dev/ttyACM0', 115200, timeout=2)  # ACM0 == STM32F103C8
    stm32.reset_input_buffer()
    arduino = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)  # USB0 == Arduino Nano
    arduino.reset_input_buffer()
    print("first reset")
    arduino.setDTR(False)
    time.sleep(0.1)
    arduino.setDTR(True)
    arduino.setRTS(False)
    arduino.setRTS(True)
    stm32.setDTR(False)
    time.sleep(0.1)
    stm32.setDTR(True)
    stm32.setRTS(False)
    stm32.setRTS(True)

    stm32.write("3\n".encode('utf-8'))
    lasers = []
    for i in range(8):
        while stm32.in_waiting == 0:
            time.sleep(0.001)
        line = float((stm32.readline().decode('utf-8').rstrip()))
        print("laser = " + str(line))

    arduino.write("3\n".encode('utf-8'))
    while arduino.in_waiting == 0:
        time.sleep(0.001)
    line = (arduino.readline().decode('utf-8').rstrip())
    print(line)
