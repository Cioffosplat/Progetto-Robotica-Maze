import RTIMU
import time
import math
import ctypes

# Load the RTIMULib library
rtimulib = ctypes.cdll.LoadLibrary('/usr/local/lib/libRTIMULib.so')
# Create a RTIMUSettings object
settings = rtimulib.RTIMUSettings("RTIMULib")
# Create a RTIMU object
imu = rtimulib.RTIMU_createIMU(settings)

if not imu.IMUInit():
    print("IMU initialization failed")
    exit(1)

# Set up the sensor fusion algorithm
imu.setSlerpPower(0.02)
imu.setGyroEnable(True)
imu.setAccelEnable(True)
imu.setCompassEnable(True)

# Set up the poll interval
poll_interval = imu.IMUGetPollInterval()

while True:
    if imu.IMURead():
        # Get the processed orientation data
        data = imu.getFusionData()
        roll = math.degrees(data["roll"])
        pitch = math.degrees(data["pitch"])
        yaw = math.degrees(data["yaw"])
        
        # Print the data
        print("Roll: %.2f, Pitch: %.2f, Yaw: %.2f" % (roll, pitch, yaw))

    # Wait for the next poll interval
    time.sleep(poll_interval/1000.0)