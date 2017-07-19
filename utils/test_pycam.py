# testing cameras

from picamera.array import PiRGBArray
from picamera import PiCamera
from glob import glob
import numpy as np
import cv2, OSC
import time, math, io, cPickle, sys



##  --- ----- --- ----- --- ----- ---- ------ ---- --- - -- --- - - -- - - ##
if __name__ == "__main__":
	## const init
    w=320
	h=240
	i=0
	frameR = 30
	period = 10
	posTr_x = 0
	posTr_y = 180
	binThreshold = 180
	maxVal = 255
	kp_bin = []
	nD=[]
	
	# detector init
	pp=cv2.SimpleBlobDetector_Params()
	pp.minThreshold=208
	pp.maxThreshold=255
	pp.filterByArea=True
	pp.minArea=50
	pp.maxArea=1000
	pp.filterByColor=True
	pp.blobColor=255
	pp.filterByCircularity=False
	pp.filterByConvexity=False
	pp.filterByInertia=False
	detector = cv2.SimpleBlobDetector(pp)

	with PiCamera() as cam:
		cam.resolution = (w, h)
		cam.framerate = frameR
		cam.contrast = 100
		cam.brightness = 20
		#cam.start_preview()
		time.sleep(2)
		stream = PiRGBArray(cam)
		## capture loop
		for foo in cam.capture_continuous(stream, format="bgr", use_video_port=True):
			try:
				actImg = stream.array
				gImg = cv2.cvtColor(actImg,cv2.COLOR_BGR2GRAY)
				img = cv2.resize(gImg, (0,0), fx=1.0, fy=1.0)
			except:
				print "ouch"
				continue
																# preprocess
			bImg = cv2.medianBlur(img, 11)
			th, tImg = cv2.threshold(bImg, binThreshold, maxVal, cv2.THRESH_BINARY);
			keyPoints = detector.detect(tImg)
			print str(keyPoints)
																# track & ntes
			#cv2.imshow(" lights! ", tImg)
			i = i+1
																# stop vIn
			stream.seek(0)
			stream.truncate()

																# if q quit
			key = cv2.waitKey(1) & 0xFF
			if key == ord("q"):
				break

		## exit
		cv2.destroyAllWindows()
