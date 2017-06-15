# -*- coding: utf-8 -*-

import numpy as np
import cv2
import sys


cap = cv2.VideoCapture(0)

# Crear code y crear objeto VideoWriter
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (640, 480))

while (cap.isOpened()):
    ret, frame = cap.read()
    if ret == True:
        frame = cv2.flip(frame, 0)

        # escribir la imagen invertida
        out.write(frame)

        cv2.imshow('frame', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        else:
            break


# cerrar si el trabajo se ha terminado
cap.release()
out.release()
cv2.destroyAllWindows()
