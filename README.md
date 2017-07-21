# ComunicacionesEspeculativas
Bacterial AI machine


## Instalación netatalk

1- Installation:

> sudo apt-get update

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

**6- c


