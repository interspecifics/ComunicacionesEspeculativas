# CE_probe



====================================================================

# para usar la pycam como cv2.videoCapture(0) hay que ejecutar
sudo apt-get install autoconf gettext libtool libjpeg62-dev
sudo apt-get install autoconf
sudo apt-get install v4l-utils
sudo modprobe bcm2835-v4l2
# cambiar resolucion para hacer una captura [parece que no se mantiene]
v4l2-ctl --set-fmt-video=width=1920,height=1080,pixelformat=3
v4l2-ctl --stream-mmap=3 --stream-count=1 --stream-to=test1.jpg

#llamar la herramienta desde otro proceso
import subprocess
subprocess.Popen(" python ce_ff_02.py -v \"0\" -s \"False\" -w \"False\"", shell=True)

#Ejecutar con distintias opciones
$ python ce_ff_4.py -v "./TL6.mp4" -w "False" -s "True" -c "True"
$ python ce_ff_4.py -v "./TL9.mp4" -w "True" -s "True" -c "False" -o "./TL9_out"


====================================================================

