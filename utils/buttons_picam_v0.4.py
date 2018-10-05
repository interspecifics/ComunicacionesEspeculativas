#!/usr/bin/env python
# -*- coding: utf-8 -*-


"""
mouse and buttons on cv

"""
import cv2
import numpy as np
from random import randint
from time import time, sleep
from picamera.array import PiRGBArray
from picamera import PiCamera


def on_mouse(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN:
        print "L: "+str(x)+","+str(y)
        # chech photo button
        if (x>btn_photo[0][0] and x<btn_photo[1][0] and \
            y>btn_photo[0][1] and y<btn_photo[1][1]):
            ss = ["cool","random","awesome","nice"]
            print "I'm taking some "+str(ss[randint(0,len(ss)-1)]) + " photos!"
            make_photo()
        # chech photo button
        if (x>btn_video[0][0] and x<btn_video[1][0] and \
            y>btn_video[0][1] and y<btn_video[1][1]):
            ss = ["cool","random","awesome","nice"]
            print "I'm taking some "+str(ss[randint(0,len(ss)-1)]) + " vid!"
            make_video()
    elif event == cv2.EVENT_RBUTTONDOWN:
        print "R: "+str(x)+","+str(y)

def make_photo():
    timestamp = int(time())
    camera.resolution = (1920,1080)
    rawCapture = PiRGBArray(camera)
    camera.capture('photo_'+str(timestamp)+'.png')
    rawCapture.truncate(0)
    camera.resolution = (640, 480)
    rawCapture = PiRGBArray(camera)

def make_video():
    timestamp = int(time())
    camera.resolution = (1920,1080)
    rawCapture = PiRGBArray(camera)
    camera.start_recording('video_'+str(timestamp)+'.h264')
    sleep(10)
    camera.stop_recording()
    rawCapture.truncate(0)
    camera.resolution = (640, 480)
    rawCapture = PiRGBArray(camera)



##  --- ----- --- ----- --- ----- ---- ------ ---- --- - -- --- - - -- - - ##
if __name__ == "__main__":
    # setup
    n = 0
    t = 0
    window_name='[SpecComms_///b00t]'
    #cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
    cv2.namedWindow(window_name)
    cv2.setMouseCallback(window_name, on_mouse)

    try:
        """
        cam = cv2.VideoCapture(0)
        #cam.set(cv2.CAP_PROP_FRAME_WIDTH, 2*1920);
        #cam.set(cv2.CAP_PROP_FRAME_HEIGHT, 2*1080);
        cam.set(cv.CV_CAP_PROP_FRAME_WIDTH, 1920);
        cam.set(cv.CV_CAP_PROP_FRAME_HEIGHT, 1080);
        ret, old_frame = cam.read()
        """
        camera = PiCamera()
        camera.resolution = (640,480)
        rawCapture = PiRGBArray(camera)
        sleep(1)
    except:
        print "[camera]: couldnt start the camera"
    
    #old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
    #print old_frame.shape
    #h,w,c = old_frame.shape
    w,h = 1920,1080
    nh=480
    nw=640

    btn_photo = [(0,nh), (((nw+50)/2), nh+50-1),(255, 255, 255, 120 ),1]
    btn_video = [((nw+50)/2,nh),((nw+50)-1,nh+50-1),(255, 255, 255, 120 ), 1]
    btn_zin = [(nw,0), (nw+50-1, (nh/2)), (255, 255, 255, 120 ),1]
    btn_zout = [(nw,nh/2), (nw+50-1, (nh)), (255, 255, 255, 120 ),1]

    canvas_frame = np.zeros((nh+50,nw+50,3), np.uint8)
    #canvas_frame.fill(255)

    #frameStream = camera.capture_continuous(rawCapture, format="bgr", use_video_port=False)

    # loop
    while(1):
        ele = camera.capture_continuous(rawCapture, format="bgr", use_video_port=False).next()
        frame = ele.array
        rawCapture.truncate(0)
        
        #ret, frame = cam.read()
        resized_frame = cv2.resize(frame, (nw, nh))
        extract = resized_frame[0:nh,0:nw]
        canvas_frame[0:nh, 0:nw] = extract

        cv2.rectangle(canvas_frame, (0,0),(nw,nh), (255,255,255,100), 1)
        cv2.rectangle(canvas_frame, btn_photo[0],btn_photo[1], btn_photo[2], btn_photo[3])
        cv2.rectangle(canvas_frame, btn_video[0],btn_video[1], btn_video[2], btn_video[3])
        cv2.rectangle(canvas_frame, btn_zin[0],btn_zin[1], btn_zin[2], btn_zin[3])
        cv2.rectangle(canvas_frame, btn_zout[0],btn_zout[1], btn_zout[2], btn_zout[3])

        cv2.imshow(window_name, canvas_frame)

        k = cv2.waitKey(5) & 0xFF
        if k == 27:
            break


"""
##  ALT
##  --- ----- --- ----- --- ----- ---- ------ ---- --- - -- --- - - -- - - ##
"""
