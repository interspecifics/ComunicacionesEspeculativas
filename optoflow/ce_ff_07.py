#!/usr/bin/env python
# -*- coding: utf-8 -*-

"""
[Comunicaciones Especulativas]: 
    -> Angular LK flowfield for multi input
-------------------------------------------

. from +X axys: math.atan2(p.y, p.x) -> angle[-PI, PI]
. multiinput
. send crazy osc

. 0.4   .load a model                           -m "./models/kmeans_1500485949.cpk"
        .send some OSC                          -c "True"
. 0.5 ::  
        .canny edge detect for finest detection -n "True"
        .discrete directions value              -d "True"
. 0.6 :: 
        .[20 vals] array for osc
. 0.7 :: 
        .ip and port addressable                -r "192.168.1.255"
                                                -p "57120"


"""

# packs
import numpy as np
import json, math, cPickle
import argparse
import OSC, cv2
from random import randint, random
from time import time
from glob import glob
from sklearn.cluster import KMeans

PI = round(math.pi, 6)


def send_actual(cOsc, ti, a0, a1):
    """form and send osc messahe"""
    route = "/cluster"
    msg = OSC.OSCMessage()
    msg.setAddress(route)
    msg.append(ti)
    msg.append(a0)
    msg.append(a1)
    cOsc.send(msg)
    print "[OSC]: " + "<<" + route + "::" + str(l) +":" + str(a0) + ":" + str(a1)


def send_actual(cOsc, ti, a20):
    """form and send osc messahe"""
    route = "/list"
    msg = OSC.OSCMessage()
    msg.setAddress(route)
    msg.append(ti)
    for a in a20:
        msg.append(a)
    #msg.append(a1)
    cOsc.send(msg)
    print "[OSC]: " + "<<" + route + "::" + str(ti)+ ":" +str(a20) 


def discretize_dir(x0, y0, x1, y1):
    """discretize [-PI, PI] direction angle to [NESWZ]"""
    angle = round(math.atan2(y1-y0, x1-x0), 2)
    rumbo = ""
    if (x0==x1 and y0==y1):
        rumbo = 'Z'
    elif (angle > -PI/4 and angle < PI/4 ):
        rumbo = 'E'
    elif (angle >= PI/4 and angle <= 3*PI/4 ):
        rumbo = 'S'
    elif (angle > 3*PI/4 or angle < -3*PI/4 ):
        rumbo = 'W'
    elif (angle <= -PI/4 and angle >= -3*PI/4 ):
        rumbo = 'N'
    return rumbo

def discretize_rum(x0, y0, x1, y1):
    """discretize [-PI, PI] direction angle to [NESWZ]"""
    angle = round(math.atan2(y1-y0, x1-x0), 2)
    rumbo = ""
    if (x0==x1 and y0==y1):
        rumbo = 0
    elif (angle > -PI/4 and angle < PI/4 ):
        rumbo = 3
    elif (angle >= PI/4 and angle <= 3*PI/4 ):
        rumbo = 2
    elif (angle > 3*PI/4 or angle < -3*PI/4 ):
        rumbo = 4
    elif (angle <= -PI/4 and angle >= -3*PI/4 ):
        rumbo = 1
    return rumbo






##  --- ----- --- ----- --- ----- ---- ------ ---- --- - -- --- - - -- - - ##
if __name__ == "__main__":
    nn_ii = 0
    t = 0
    first = True

    # argparse
    ap = argparse.ArgumentParser()
    ap.add_argument("-i", "--in-dir",   default="./imgs_in",                help="input dir path")
    ap.add_argument("-o", "--out-dir",  default="./imgs_out",               help="output dir path")
    ap.add_argument("-v", "--video",                                        help="path to the video input file")
    ap.add_argument("-s", "--show",     default="False",                    help="video output enable")
    ap.add_argument("-w", "--write",    default="True",                     help="write output images")
    ap.add_argument("-m", "--model",    default="./models/kmeans_1500555372.cpk",  help="load a custom model for cluster labeling")
    ap.add_argument("-c", "--osc",      default="False",                    help="send output messages")
    ap.add_argument("-n", "--canny",    default="False",                    help="uses canny edge detector")
    ap.add_argument("-d", "--direct",   default="False",                    help="discrete directions enable")
    ap.add_argument("-r", "--receiver-ip",      default="192.168.1.255",    help="receiver ip address")
    ap.add_argument("-p", "--receiver-port",    default="57120",            help="receiver osc port")
    args = vars(ap.parse_args())

    # load model
    model = cPickle.load(open(args["model"],"r"))

    #in_dir = in_dir

    # osc
    send_addr = args["receiver_ip"], int(args["receiver_port"])
    cOsc = OSC.OSCClient()
    cOsc.connect(send_addr)
    print "[t]: OSC : ok"

    # dirs
    in_fns = glob(args["in_dir"]+"/*.png")
    in_fns.sort()
    #print in_fns
    print "[n_imgs]:", len(in_fns)

    # modecd ..
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
    if (args["canny"] == "True"):
        old_gray = cv2.Canny(old_gray, 30, 30)


    # generate interest points
    h,w,c = old_frame.shape
    pts = []
    for i in range (0, w, 10):
        for j in range (0, h, 10):
            pts.append([[i, j]])
    #color = np.random.randint(0,255,(len(pts),3))
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
        if (args["canny"] == "True"):
            frame_gray = cv2.Canny(frame_gray, 30, 30)
        # copy interest points
        p0 = p00
        if (args["canny"] == "True"):
            vfield = np.zeros_like(frame_gray)
        else:
            vfield = np.zeros_like(old_frame)
        # calculate opticalflow
        p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)
        print p0.shape, p1.shape
        # angles and vectors
        new_angles = [round(math.atan2(p1[a][0][1]-p0[a][0][1], p1[a][0][0]-p0[a][0][0]), 2) if st[a]==1 else 0 for a in range(p0.shape[0])]
        #new_angles = [discretize_rum(p0[a][0][0], p0[a][0][1], p1[a][0][0], p1[a][0][1]) if st[a]==1 else 0 for a in range(p0.shape[0])]
        #all_angles.append(new_angles)

        # filter good motion points to draw
        good_new = p1[st==1]
        good_old = p0[st==1]
        print good_old.shape, good_new.shape

        # send message
        if (args['osc'] == "True"):
            l = model.predict(np.array(new_angles).reshape(1, -1))[0]
            #send_actual(cOsc, int(l), new_angles[1760], new_angles[3520])
            send_actual(cOsc, int(l), new_angles[2640:2660])            

        # draw tracks for good points
        for i,(new,old) in enumerate(zip(good_new,good_old)):
            a,b = new.ravel()
            c,d = old.ravel()
            if (args["direct"] == "True"):
                font = cv2.FONT_HERSHEY_SIMPLEX
                cv2.putText(vfield, discretize_dir(c,d,a,b), (int(a+2),int(b-2)), font, 0.3,(255,255,255), 1)
                cv2.rectangle(vfield, (a, b), (int(a+10), int(b-10)), (125, 125, 125), 1)
            else:
                cv2.line (vfield, (a,b),(c,d), (127, 125, 125),  1)
            #cv2.rectangle(img, pt1, pt2, color[, thickness[, lineType[, shift]]]) 
            #cv2.putText(img,'Hello World!',(10,500), font, 1,(255,255,255),2)
            #cv2.
        # merge, maybe show
        if (args["canny"] == "True"):
            #vfield = np.zeros_like(frame_gray)
            img = cv2.add(frame_gray, vfield)
        else:
            #vfield = np.zeros_like(old_frame)
            img = cv2.add(frame, vfield)
        if args["show"] == "True":
            cv2.imshow('frame', img)
        # write
        if args["write"] == "True":
            if (fromCam or fromVideo):
                cv2.imwrite(args["out_dir"]+'/img_out_%05i.png' % iii, img)
                iii+=1
            else:
                cv2.imwrite(fn.replace(args["in_dir"], args["out_dir"]), img)
		iii+=1
            all_angles.append(new_angles)
        # wait
        #if (not fromCam and not fromVideo):
        k = cv2.waitKey(10) & 0xff
        if k == 27:
            break
        # refresh reference
        old_gray = frame_gray.copy()

    if args["write"] == "True":
        kmeans = KMeans(n_clusters=3, random_state=0).fit(all_angles)
        model_name =  "./models/kmeans_"+str(int(time()))+".cpk"
        data_name  =  "./data/angles_"+str(int(time()))+".json"
        cPickle.dump(kmeans,  open(model_name, "w"))
        json.dump(all_angles, open(data_name , 'w'))
	print model_name, data_name	
    cv2.destroyAllWindows()
    #video.release()
