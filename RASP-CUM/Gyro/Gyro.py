from mpu6050 import mpu6050
import math
import time

# Initialize MPU6050 sensor
sensor = mpu6050(0x68)

# Define constants
RAD_TO_DEG = 57.295779513082320876798154814105

# Define a function to calculate pitch angle
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

# Main loop
while True:
    pitch = get_pitch()
    print("Pitch: {:.2f}".format(pitch))
    time.sleep(0.1)