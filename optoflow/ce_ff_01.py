#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
[Comunicaciones Especulativas]: 
    -> Angular LK flowfield for multi input
-------------------------------------------

. from +X axys: math.atan2(p.y, p.x) -> angle[-PI, PI]
. multiinput
. send crazy osc
"""

# packs
import numpy as np
import cv2
import json, math
from glob import glob
import argparse
import OSC
from random import randint, random


def send_actual(cOsc):
    """form and send osc messahe"""
    route = "/tipo_mov"
    msg = OSC.OSCMessage()
    msg.setAddress(route)
    val = randint(0, 2)
    val2 = random()
    msg.append(val)
    msg.append(val2)
    cOsc.send(msg)
    print "[OSC]: " + "<<" + route + "::" + str(val)



##  --- ----- --- ----- --- ----- ---- ------ ---- --- - -- --- - - -- - - ##
if __name__ == "__main__":
    nn_ii = 0
    t = 0
    first = True

    # argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("-v", "--video",                          help="path to the video input file")
    ap.add_argument("-s", "--show",     default="False",      help="video output enable")
    ap.add_argument("-w", "--write",    default="True",       help="write output images")
    ap.add_argument("-c", "--osc",      default="False",      help="send output messages")
    ap.add_argument("-i", "--in-dir",   default="./imgs_in",   help="input dir path")
    ap.add_argument("-o", "--out-dir",  default="./imgs_out",  help="output dir path")
    args = vars(ap.parse_args())

    #in_dir = in_dir
    """
    # osc
    send_addr = "192.168.1.255", 57120
    cOsc = OSC.OSCClient()
    cOsc.connect(send_addr)
    print "[t]: OSC : ok"
    """
    # dirs
    in_fns = glob(args["in_dir"]+"/*.png")
    in_fns.sort()
    #print in_fns
    print "[n_imgs]:", len(in_fns)

    # mode
    fromVideo = False
    fromCam = False
    if args["video"] != None:
        if args["video"] == "0":
            fromCam = True
        else:
            fromVideo = True
            video_path = args["video"]

    # input, first_frame
    if fromVideo:
        try:
            video = cv2.VideoCapture(args["video"])
            ret, old_frame = video.read()
        except:
            print "[video]: couldnt find the video"
            #break
    elif fromCam:
        try:
            video = cv2.VideoCapture(0)
            ret, old_frame = video.read()
        except:
            print "[camera]: couldnt start the camera"
            #break
    else:
        try:
            old_frame = cv2.imread(in_fns[0], cv2.IMREAD_UNCHANGED)
        except:
            print "[in_dir]: no encuentro las imágenes: ", in_fns[0]
    
    # grayscale
    old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)

    # generate interest points
    h,w,c = old_frame.shape
    pts = []
    for i in range (0, w, 10):
        for j in range (0, h, 10):
            pts.append([[i, j]])
    color = np.random.randint(0,255,(len(pts),3))
    p00 = np.array(pts, dtype="float32")

    # parameters for lucas kanade
    lk_params = dict( winSize  = (15,15),
                      maxLevel = 4,
                      criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

    # be sure to loop
    iii = 0 
    all_angles = []

    #for fn in in_fns[1:]:
    
    while(1):
        #if (not (fromCam or fromVideo)):
        #    fn = in_fns[iii]
        #    print fn
        # get new frame
        if fromCam or fromVideo:
            ret, frame = video.read()
            if ret==False:
                break
        else:
            fn = in_fns[iii]
            print fn
            frame = cv2.imread(fn, cv2.IMREAD_UNCHANGED)
        # grayscale
        frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        # copy interest points
        p0 = p00
        vfield = np.zeros_like(old_frame)
        # calculate opticalflow
        p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)
        print p0.shape, p1.shape
        # angles and vectors
        new_angles = [round(math.atan2(p1[a][0][1]-p0[a][0][1], p1[a][0][0]-p0[a][0][0]), 2) if st[a]==1 else 0 for a in range(p0.shape[0])]
        #all_angles.append(new_angles)

        # filter good motion points to draw
        good_new = p1[st==1]
        good_old = p0[st==1]
        print good_old.shape, good_new.shape

        # send message
        if (args['osc'] == "True"):
            send_actual(cOsc)

        # draw tracks for good points
        for i,(new,old) in enumerate(zip(good_new,good_old)):
            a,b = new.ravel()
            c,d = old.ravel()
            cv2.line (vfield, (a,b),(c,d), color[i].tolist(),  1)
        # merge, maybe show
        img = cv2.add(frame, vfield)
        if args["show"] == "True":
            cv2.imshow('frame',img)
        # write
        if args["write"] == "True":
            if (fromCam or fromVideo):
                cv2.imwrite(args["out_dir"]+'/img_out_%05i.png' % iii, img)
                iii+=1
            else:
                cv2.imwrite(fn.replace(args["in_dir"], args["out_dir"]), img)
            all_angles.append(new_angles)
        # wait
        #if (not fromCam and not fromVideo):
        k = cv2.waitKey(1) & 0xff
        if k == 27:
            break
        # refresh reference
        old_gray = frame_gray.copy()
    json.dump(all_angles, open("./historic_angle_vectors.json",'w'))
    #json.dump(all_angles, open("./nout/angles_vortex.json",'w'))
    cv2.destroyAllWindows()
    #video.release()
