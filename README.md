# ComunicacionesEspeculativas
Es un proyecto basado en una máquina que es capaz de observar y aprender de
microorganismos para crear un score audiovisual a partir de los patrones que encuentre en su comportamiento. Este proyecto se apoya en la creación de una inteligencia artificial, la cual reconoce comportamientos organizados reiterativos en cultivos biológicos y los transforma en eventos que dota de una gestualidad audiovisual específica con el fin de lograr una composición autogenerativa que responde a las lógicas de decisión que esta inteligencia construye con el tiempo. 

![the system](https://github.com/interspecifics/ComunicacionesEspeculativas/blob/master/ComunicacionEspeculativa.jpg?raw=true)

## Instalación CV2.4.9 en Mac
1 - Instalar brew http://brew.sh/

>brew tap homebrew/science

>brew install opencv

## Instalación CV2 en la raspberry

seguir el tutorial que se encuentra aquí:
https://www.pyimagesearch.com/2015/02/23/install-opencv-and-python-on-your-raspberry-pi-2-and-b/

## Instalación netatalk

1- Installation:

>sudo apt-get update

>sudo apt-get install netatalk

2- Configuration

**Stop the service:**

>sudo /etc/init.d/netatalk stop

**Open the configuration file:**

>sudo nano /etc/netatalk/AppleVolumes.default

**You can edit the mount folder if you wish or leave the default value:**

>~/ "Home Directory"

**Start the service again**

>sudo /etc/init.d/netatalk start

## Configurar USB como storage local

**1 - To mount a USB drive:**

>sudo mkdir /mnt/usbdrive

>sudo mount /dev/sda1 /mnt/usbdrive

>ls /mnt/usbdrive

**2 - To list your file systems:**

>sudo fdisk -l

>sudo mount -l

>df -h

**3- Before disconnecting a USB drive:**

>sudo umount /dev/sda1

**4- Format a drive to EXT4**

>sudo mkfs.ext4 /dev/sda1 -L untitled

**5- Create a mount point**

>sudo mkdir /mnt/usbdrive

**6- Check the dev directory

>/dev/sd*

**7- To mount the drive to your mount point ‘usbdrive‘.

>sudo mount /dev/sda1 /mnt/usbdrive

**8- Disconnect / Unmount A Drive**

>sudo umount /dev/sda1

## Biotracker XY

Para la construcción de biotracker xy es necesario la impresión de la piezas que se encuentran aquí 

![Biotracker](http://interspecifics.cc/comunicacionesespeculativas/wp-content/uploads/2018/05/IMG_2033.jpg?raw=true)

![Biotracker](http://interspecifics.cc/comunicacionesespeculativas/wp-content/uploads/2018/05/IMG_2030.jpg?raw=true)


## Controllers 


