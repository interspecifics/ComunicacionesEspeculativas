# CE_probe



====================================================================

# Para usar la pycam como cv2.videoCapture(0) hay que ejecutar

sudo apt-get install autoconf gettext libtool libjpeg62-dev

sudo apt-get install autoconf

sudo apt-get install v4l-utils

sudo modprobe bcm2835-v4l2


# Cambiar resolucion para hacer una captura [parece que no se mantiene]

v4l2-ctl --set-fmt-video=width=1920,height=1080,pixelformat=3

v4l2-ctl --stream-mmap=3 --stream-count=1 --stream-to=test1.jpg


# Llamar la herramienta desde otro proceso

import subprocess

subprocess.Popen(" python ce_ff_02.py -v \"0\" -s \"False\" -w \"False\"", shell=True)


# Ejecutar con distintias opciones

>python ce_ff_06.py -v "./TL6.mp4" -w "False" -s "True" -c "True"

>python ce_ff_06.py -v "./TL9.mp4" -w "True" -s "True" -c "False" -o "./TL9_out"

>python ce_ff_06.py -v "./videos/TL13.mp4" -w "False" -s "True" -n "True" -c "True"

>python ce_ff_07.py -v "./TL3.mp4" -w "False" -s "False" -n "True" -c "True" -d "True" -r "192.168.1.25" -p "57120"


====================================================================

