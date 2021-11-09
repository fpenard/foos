import cv2
from threading import Thread
import time
from datetime import datetime
from enum import Enum, auto
import logging

logger = logging.getLogger(__name__)

class WebcamState(Enum):
    WEBCAM_INIT = auto()
    WEBCAM_READY = auto()
    WEBCAM_START = auto()
    WEBCAM_RECORD = auto()
    WEBCAM_STOP = auto()
    WEBCAM_ERROR = auto()

class Webcam:
    def __init__(self, devStr = '/dev/video0'):
        self.state = WebcamState.WEBCAM_INIT
        self.webcamCap = cv2.VideoCapture(devStr)
        Thread(target=self.recordLoop, daemon=True).start()
        if not self.webcamCap.isOpened():
            self.state = WebcamState.WEBCAM_ERROR
            logger.warning("Cannot open {0} webcam device".format(devStr))
        else:
            self.state = WebcamState.WEBCAM_READY

    # Run camera
    def recordLoop(self):
        while(True):
            while(self.state == WebcamState.WEBCAM_RECORD) and self.webcamCap.isOpened():
                ret, frame = self.webcamCap.read()
                if ret == True:
                    frame = cv2.flip(frame,1)
                    self.output.write(frame)
                else:
                    break
            time.sleep(0.250)

    # Run camera
    def startRecord(self, filename='output.avi', fps=5.0):
        if self.state == WebcamState.WEBCAM_READY:
            self.state = WebcamState.WEBCAM_START

            fourcc = cv2.VideoWriter_fourcc(*'XVID')
            self.output = cv2.VideoWriter(filename,fourcc, fps, (640,480))
            if not self.output.isOpened():
                logger.warning("Cannot open {0} video record output file".format(filename))
                return

            self.state = WebcamState.WEBCAM_RECORD

    def stopRecord(self):
        if self.state == WebcamState.WEBCAM_RECORD:
            self.state = WebcamState.WEBCAM_STOP
            self.output.release()
            self.state = WebcamState.WEBCAM_READY

    # Run camera
    def runReplay(self, filename, fpsFactor, replayDurMs):
        # Open file
        cap = cv2.VideoCapture(filename)
        if not cap.isOpened():
            logger.warning("Cannot open {0} input video replay file".format(filename))
            return

        # Find OpenCV version
        (major_ver, minor_ver, subminor_ver) = (cv2.__version__).split('.')

        # Get FPS
        if int(major_ver) < 3:
            fps = cap.get(cv2.cv.CV_CAP_PROP_FPS)
        else :
            fps = cap.get(cv2.CAP_PROP_FPS)

        # Get total number of frames
        if int(major_ver) < 3:
            nbFrame = cap.get(cv2.cv.CV_CAP_PROP_FRAME_COUNT)
        else :
            nbFrame = cap.get(cv2.CAP_PROP_FRAME_COUNT)

        # Compute total video duration
        durationMs = (nbFrame / fps) * 1000

        # Set OpenCV frame position depending on replay duration
        if durationMs > replayDurMs:
            if int(major_ver) < 3:
                nbFrame = cap.set(cv2.cv.CV_CAP_PROP_POS_MSEC, durationMs-replayDurMs)
            else :
                nbFrame = cap.set(cv2.CAP_PROP_POS_MSEC, durationMs-replayDurMs)

        # Compute step time duration
        timeStep = 1.0 / (float(fps) * fpsFactor)

        # Play video
        while(cap.isOpened()):
            ret, frame = cap.read()
            if ret:
                cv2.imshow("frame", frame)
                cv2.waitKey(int(timeStep*1000))
            else:
                break
        cap.release()
        cv2.destroyAllWindows()

    def __del__(self):
        self.webcamCap.release()
        self.output.release()
        cv2.destroyAllWindows()


if __name__ == '__main__':
    filename='outputTest.avi'
    webcamDev = Webcam(devStr = '/dev/video0')
    webcamDev.startRecord(filename=filename, fps=20.0)
    time.sleep(10)
    webcamDev.stopRecord()
    startTime = datetime.now()
    webcamDev.runReplay(filename, 0.5, 2000)
    print(datetime.now() - startTime)
