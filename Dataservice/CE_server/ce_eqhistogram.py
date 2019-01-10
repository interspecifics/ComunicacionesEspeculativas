#!/usr/bin/python

import cv2
import numpy as np
import random
import argparse
from time import time
from glob import glob

"""
	I N T E R S P E C I F I C S
	applies opencv histogram equalization to a sequence of images
	https://docs.opencv.org/3.1.0/d5/daf/tutorial_py_histogram_equalization.html

	use it as:
	$ python ce_eqhistogram.py -i "W:/A/SPECCOMS/v05_hd" -o "W:/A/SPECCOMS/V05HD_HC"

"""



if __name__ == '__main__':

    # arguments
    ap = argparse.ArgumentParser()
    ap.add_argument("-i", "--in-dir",   default="W:/A/SPECCOMS/v05_hd",                 help="input folder path")
    ap.add_argument("-o", "--out-dir",   default="W:/A/SPECCOMS/V05HD_HC",           	help="output folder path")
    args = vars(ap.parse_args())

    # load frames
    in_fns = glob(args["in_dir"]+"/*.png")[:-1]
    in_fns.sort()
    frames = []
    for fn in in_fns:
		img = cv2.imread(fn, 0)
		# create a CLAHE object (Arguments are optional).
		clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))
		cl1 = clahe.apply(img)
		fno = fn.replace(args["in_dir"], args["out_dir"])
		cv2.imwrite(fno, cl1)
		print fn, " >> ", fno