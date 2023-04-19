import serial
import time

L_front_R = 0
L_front_L = 1
L_left_L = 2
L_back_L = 3
L_back_R = 4
L_right_R = 5

laserName = ["L_front_R", "L_front_L", "L_left_L", "L_back_L", "L_back_R", "L_right_R"]

print("Serial STM")
serSTM = serial.Serial('/dev/ttyACM0', 115200, timeout=2)  # ACM0 == STM32F103C8
serSTM.reset_input_buffer()

def getLasers():
    serSTM.write("3\n".encode('utf-8'))
    print("get lasers")
    lasers = []
    for i in range(6):
        while serSTM.in_waiting == 0:
            time.sleep(0.002)
        line = float((serSTM.readline().decode('utf-8').rstrip()))
        lasers.append(line)
        print(laserName[i] + ": " + str(lasers[i]))
    return lasers

if __name__ == '__main__':
    while True:
        l = getLasers()
        print(l[:])
        time.sleep(0.5)