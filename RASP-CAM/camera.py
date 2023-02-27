import pickle
import subprocess
import os

import cv2
from cv2 import VideoCapture


class Camera:

    def __init__(self, bus, right=False, rotate=False, path='/calib.p'):
        with open(os.path.dirname(__file__) + path, 'rb') as f:
            self.distort = pickle.load(f)

        self.right = right
        self.rotate = rotate
        self.camera = VideoCapture(bus)
        self.camera.set(cv2.CAP_PROP_BUFFERSIZE, 1)

    def frame(self):
        ret, frame = self.camera.read()
        if not ret:
            return ret, None, None
        if self.rotate:
            frame = cv2.rotate(frame, cv2.ROTATE_180)
        frame = self._undistort(frame)

        frame = frame[30:355, :]

        # cv2.imshow('frame!', frame)

        binary_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

        return ret, frame, binary_frame

    def __del__(self):
        self.camera.release()

    def _undistort(self, img):
        dst = cv2.undistort(img, self.distort['mtx'], self.distort['dist'], None, self.distort['cmatrix'])
        x, y, w, h = self.distort['roi']
        dst = dst[y:y + h, x:x + w]
        return cv2.resize(dst, (640, 480), interpolation=cv2.INTER_CUBIC)

    @staticmethod
    def scan(device=1):
        index = 0
        while True:
            cap = VideoCapture(index)
            if cap.read()[0]:
                if device <= 1:
                    return index
                else:
                    device -= 1
            cap.release()
            index += 1

    @staticmethod
    def list_cameras():
        try:
            out = subprocess.check_output(["v4l2-ctl", "--list-devices"]).decode()
        except subprocess.CalledProcessError as e:
            out = e.output
        out = out.replace('\n\n', '\n').split('\n')
        devices = {}
        last_d = None
        for line in out:
            if not line.startswith('\t'):
                last_d = line
            else:
                devices[last_d] = devices.get(last_d, []) + [line[1:]]
        return devices

    def __delete__(self, instance):
        self.camera.release()
