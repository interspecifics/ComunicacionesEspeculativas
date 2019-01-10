EESchema Schematic File Version 4
LIBS:biotracker-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L teensy:Teensy3.2 U1
U 1 1 5C28F1BC
P 4350 5000
F 0 "U1" H 4350 6587 60  0000 C CNN
F 1 "Teensy3.2" H 4350 6481 60  0000 C CNN
F 2 "teensy:Teensy30_31_32_LC" H 4350 4200 60  0001 C CNN
F 3 "" H 4350 4200 60  0000 C CNN
	1    4350 5000
	1    0    0    -1  
$EndComp
$Comp
L biotrack:DRV8833 U3
U 1 1 5C28F8DA
P 8500 2500
F 0 "U3" H 8500 3115 50  0000 C CNN
F 1 "DRV8833" H 8500 3024 50  0000 C CNN
F 2 "teensy:ADA_DRV8833" H 8500 3000 50  0001 C CNN
F 3 "" H 8500 3000 50  0001 C CNN
	1    8500 2500
	1    0    0    -1  
$EndComp
$Comp
L biotrack:DRV8833 U4
U 1 1 5C297062
P 8500 3800
F 0 "U4" H 8500 4415 50  0000 C CNN
F 1 "DRV8833" H 8500 4324 50  0000 C CNN
F 2 "teensy:ADA_DRV8833" H 8500 4300 50  0001 C CNN
F 3 "" H 8500 4300 50  0001 C CNN
	1    8500 3800
	1    0    0    -1  
$EndComp
$Comp
L biotrack:TB6612 U5
U 1 1 5C297905
P 8550 5250
F 0 "U5" H 8550 5965 50  0000 C CNN
F 1 "TB6612" H 8550 5874 50  0000 C CNN
F 2 "teensy:ADA_TB6612" H 8550 5850 50  0001 C CNN
F 3 "" H 8550 5850 50  0001 C CNN
	1    8550 5250
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5C297A10
P 4000 1500
F 0 "SW1" H 4000 1650 50  0000 C CNN
F 1 "SWPush_A" H 4000 1400 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 4000 1700 50  0001 C CNN
F 3 "" H 4000 1700 50  0001 C CNN
	1    4000 1500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5C297B61
P 4000 2300
F 0 "SW2" H 4000 2450 50  0000 C CNN
F 1 "SWPush_B" H 4000 2200 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH-12mm" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5C297BD3
P 4200 1350
F 0 "R1" H 4270 1396 50  0000 L CNN
F 1 "10K" H 4270 1305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 1350 50  0001 C CNN
F 3 "~" H 4200 1350 50  0001 C CNN
	1    4200 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C297C99
P 4200 2150
F 0 "R2" H 4270 2196 50  0000 L CNN
F 1 "10K" H 4270 2105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4130 2150 50  0001 C CNN
F 3 "~" H 4200 2150 50  0001 C CNN
	1    4200 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_POT RV1
U 1 1 5C297D47
P 2700 5700
F 0 "RV1" H 2630 5746 50  0000 R CNN
F 1 "10K" H 2630 5655 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Alps_RK163_Single_Horizontal" H 2700 5700 50  0001 C CNN
F 3 "~" H 2700 5700 50  0001 C CNN
	1    2700 5700
	1    0    0    -1  
$EndComp
$Comp
L biotrack:ADA_Joystick U2
U 1 1 5C297FD8
P 5550 1500
F 0 "U2" H 5500 1950 50  0000 L CNN
F 1 "ADA_Joystick" H 5300 1850 50  0000 L CNN
F 2 "teensy:ADA_joystick" H 5550 1850 50  0001 C CNN
F 3 "" H 5550 1850 50  0001 C CNN
	1    5550 1500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5C2989BD
P 2800 3750
F 0 "#PWR07" H 2800 3500 50  0001 C CNN
F 1 "GND" H 2805 3577 50  0000 C CNN
F 2 "" H 2800 3750 50  0001 C CNN
F 3 "" H 2800 3750 50  0001 C CNN
	1    2800 3750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5C298A02
P 7550 3600
F 0 "#PWR026" H 7550 3350 50  0001 C CNN
F 1 "GND" H 7555 3427 50  0000 C CNN
F 2 "" H 7550 3600 50  0001 C CNN
F 3 "" H 7550 3600 50  0001 C CNN
	1    7550 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5C298A21
P 7500 5050
F 0 "#PWR022" H 7500 4800 50  0001 C CNN
F 1 "GND" H 7505 4877 50  0000 C CNN
F 2 "" H 7500 5050 50  0001 C CNN
F 3 "" H 7500 5050 50  0001 C CNN
	1    7500 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3700 2800 3700
Wire Wire Line
	2800 3700 2800 3750
$Comp
L power:GND #PWR024
U 1 1 5C2989E3
P 7550 2300
F 0 "#PWR024" H 7550 2050 50  0001 C CNN
F 1 "GND" H 7555 2127 50  0000 C CNN
F 2 "" H 7550 2300 50  0001 C CNN
F 3 "" H 7550 2300 50  0001 C CNN
	1    7550 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR014
U 1 1 5C298C64
P 5550 5750
F 0 "#PWR014" H 5550 5600 50  0001 C CNN
F 1 "+5V" H 5565 5923 50  0000 C CNN
F 2 "" H 5550 5750 50  0001 C CNN
F 3 "" H 5550 5750 50  0001 C CNN
	1    5550 5750
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR023
U 1 1 5C298C9A
P 7550 2100
F 0 "#PWR023" H 7550 1950 50  0001 C CNN
F 1 "+5V" H 7565 2273 50  0000 C CNN
F 2 "" H 7550 2100 50  0001 C CNN
F 3 "" H 7550 2100 50  0001 C CNN
	1    7550 2100
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR025
U 1 1 5C298CC0
P 7550 3400
F 0 "#PWR025" H 7550 3250 50  0001 C CNN
F 1 "+5V" H 7565 3573 50  0000 C CNN
F 2 "" H 7550 3400 50  0001 C CNN
F 3 "" H 7550 3400 50  0001 C CNN
	1    7550 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5800 5550 5800
Wire Wire Line
	5550 5800 5550 5750
$Comp
L power:+12V #PWR021
U 1 1 5C298EBD
P 7500 4750
F 0 "#PWR021" H 7500 4600 50  0001 C CNN
F 1 "+12V" H 7515 4923 50  0000 C CNN
F 2 "" H 7500 4750 50  0001 C CNN
F 3 "" H 7500 4750 50  0001 C CNN
	1    7500 4750
	1    0    0    -1  
$EndComp
NoConn ~ 3350 3800
NoConn ~ 3350 3900
Text GLabel 3350 4000 0    50   Output ~ 0
LED1
Text GLabel 3350 4100 0    50   Output ~ 0
LED2
Text GLabel 3350 4200 0    50   Output ~ 0
MotY_AIn2
Text GLabel 3350 4300 0    50   Output ~ 0
MotY_AIn1
Text GLabel 3350 4400 0    50   Output ~ 0
MotY_BIn1
Text GLabel 3350 4500 0    50   Output ~ 0
MotY_BIn2
$Comp
L Motor:Stepper_Motor_bipolar M3
U 1 1 5C299B2B
P 10200 5400
F 0 "M3" H 10388 5523 50  0000 L CNN
F 1 "Stepper_Z" H 10388 5432 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10210 5390 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 10210 5390 50  0001 C CNN
	1    10200 5400
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_bipolar M2
U 1 1 5C299C00
P 10200 3950
F 0 "M2" H 10387 4073 50  0000 L CNN
F 1 "MiniStepper_Y" H 10387 3982 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10210 3940 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 10210 3940 50  0001 C CNN
	1    10200 3950
	1    0    0    -1  
$EndComp
$Comp
L Motor:Stepper_Motor_bipolar M1
U 1 1 5C299C4C
P 10200 2650
F 0 "M1" H 10388 2773 50  0000 L CNN
F 1 "MiniStepper_X" H 10388 2682 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10210 2640 50  0001 C CNN
F 3 "http://www.infineon.com/dgdl/Application-Note-TLE8110EE_driving_UniPolarStepperMotor_V1.1.pdf?fileId=db3a30431be39b97011be5d0aa0a00b0" H 10210 2640 50  0001 C CNN
	1    10200 2650
	1    0    0    -1  
$EndComp
Text GLabel 3350 4600 0    50   Output ~ 0
MotX_AIn2
Text GLabel 3350 4700 0    50   Output ~ 0
MotX_AIn1
Text GLabel 3350 4800 0    50   Output ~ 0
MotX_BIn1
Text GLabel 3350 4900 0    50   Output ~ 0
MotX_BIn2
NoConn ~ 3350 5000
NoConn ~ 3350 5600
$Comp
L power:GND #PWR06
U 1 1 5C29A364
P 2700 6000
F 0 "#PWR06" H 2700 5750 50  0001 C CNN
F 1 "GND" H 2705 5827 50  0000 C CNN
F 2 "" H 2700 6000 50  0001 C CNN
F 3 "" H 2700 6000 50  0001 C CNN
	1    2700 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 5700 3350 5700
NoConn ~ 3350 5800
Text GLabel 3350 5900 0    50   Input ~ 0
Joy_X
Text GLabel 3350 6000 0    50   Input ~ 0
Joy_Y
Text GLabel 3350 6100 0    50   Input ~ 0
Push_A
Text GLabel 3350 6200 0    50   Input ~ 0
Push_B
$Comp
L power:GND #PWR09
U 1 1 5C29CB90
P 3650 1500
F 0 "#PWR09" H 3650 1250 50  0001 C CNN
F 1 "GND" H 3655 1327 50  0000 C CNN
F 2 "" H 3650 1500 50  0001 C CNN
F 3 "" H 3650 1500 50  0001 C CNN
	1    3650 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5C29CBB5
P 3650 2300
F 0 "#PWR010" H 3650 2050 50  0001 C CNN
F 1 "GND" H 3655 2127 50  0000 C CNN
F 2 "" H 3650 2300 50  0001 C CNN
F 3 "" H 3650 2300 50  0001 C CNN
	1    3650 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 1500 3650 1500
Wire Wire Line
	3650 2300 3800 2300
Text GLabel 4400 1500 2    50   Output ~ 0
Push_A
Text GLabel 4400 2300 2    50   Output ~ 0
Push_B
Wire Wire Line
	4400 1500 4200 1500
Connection ~ 4200 1500
Wire Wire Line
	4400 2300 4200 2300
Connection ~ 4200 2300
$Comp
L power:+5V #PWR016
U 1 1 5C29E419
P 6050 1250
F 0 "#PWR016" H 6050 1100 50  0001 C CNN
F 1 "+5V" H 6065 1423 50  0000 C CNN
F 2 "" H 6050 1250 50  0001 C CNN
F 3 "" H 6050 1250 50  0001 C CNN
	1    6050 1250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5C29E43E
P 6050 1750
F 0 "#PWR017" H 6050 1500 50  0001 C CNN
F 1 "GND" H 6055 1577 50  0000 C CNN
F 2 "" H 6050 1750 50  0001 C CNN
F 3 "" H 6050 1750 50  0001 C CNN
	1    6050 1750
	1    0    0    -1  
$EndComp
Text GLabel 5950 1400 2    50   Output ~ 0
Joy_X
Text GLabel 5950 1500 2    50   Output ~ 0
Joy_Y
NoConn ~ 5950 1600
Wire Wire Line
	5950 1300 6050 1300
Wire Wire Line
	6050 1300 6050 1250
Wire Wire Line
	5950 1700 6050 1700
Wire Wire Line
	6050 1700 6050 1750
Text GLabel 3350 6300 0    50   Output ~ 0
MotZ_BIn2
Text GLabel 5350 6300 2    50   Output ~ 0
MotZ_BIn1
Text GLabel 5350 6200 2    50   Output ~ 0
MotZ_AIn1
Text GLabel 5350 6100 2    50   Output ~ 0
MotZ_AIn2
Text GLabel 5850 6000 2    50   Output ~ 10
3V_bus
Text GLabel 8150 2450 0    50   Input ~ 0
MotX_BIn1
Text GLabel 8150 2550 0    50   Input ~ 0
MotX_BIn2
Text GLabel 8150 2750 0    50   Input ~ 0
MotX_AIn2
Text GLabel 8150 2850 0    50   Input ~ 0
MotX_AIn1
Text GLabel 8150 3750 0    50   Input ~ 0
MotY_BIn1
Text GLabel 8150 3850 0    50   Input ~ 0
MotY_BIn2
Text GLabel 8150 4050 0    50   Input ~ 0
MotY_AIn2
Text GLabel 8150 4150 0    50   Input ~ 0
MotY_AIn1
Text GLabel 8150 5200 0    50   Input ~ 0
MotZ_BIn2
Text GLabel 8150 5300 0    50   Input ~ 0
MotZ_BIn1
Text GLabel 8150 5500 0    50   Input ~ 0
MotZ_AIn1
Text GLabel 8150 5600 0    50   Input ~ 0
MotZ_AIn2
Wire Wire Line
	8150 2150 7550 2150
Wire Wire Line
	7550 2150 7550 2100
Wire Wire Line
	8150 2250 7550 2250
Wire Wire Line
	7550 2250 7550 2300
NoConn ~ 8150 2350
NoConn ~ 8150 3650
Wire Wire Line
	8150 3450 7550 3450
Wire Wire Line
	7550 3450 7550 3400
Wire Wire Line
	8150 3550 7550 3550
Wire Wire Line
	7550 3550 7550 3600
NoConn ~ 8150 4900
Wire Wire Line
	7500 4800 7500 4750
Wire Wire Line
	7500 5000 7500 5050
Wire Wire Line
	2700 5850 2700 6000
$Comp
L power:+3.3V #PWR011
U 1 1 5C2AC67E
P 4200 1200
F 0 "#PWR011" H 4200 1050 50  0001 C CNN
F 1 "+3.3V" H 4215 1373 50  0000 C CNN
F 2 "" H 4200 1200 50  0001 C CNN
F 3 "" H 4200 1200 50  0001 C CNN
	1    4200 1200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR012
U 1 1 5C2AC983
P 4200 2000
F 0 "#PWR012" H 4200 1850 50  0001 C CNN
F 1 "+3.3V" H 4215 2173 50  0000 C CNN
F 2 "" H 4200 2000 50  0001 C CNN
F 3 "" H 4200 2000 50  0001 C CNN
	1    4200 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5C2ACF28
P 2700 5450
F 0 "#PWR05" H 2700 5300 50  0001 C CNN
F 1 "+3.3V" H 2715 5623 50  0000 C CNN
F 2 "" H 2700 5450 50  0001 C CNN
F 3 "" H 2700 5450 50  0001 C CNN
	1    2700 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 5550 2700 5450
Wire Wire Line
	7500 4800 8150 4800
Wire Wire Line
	7500 5000 8150 5000
$Comp
L power:+3.3V #PWR015
U 1 1 5C2AE178
P 5750 5950
F 0 "#PWR015" H 5750 5800 50  0001 C CNN
F 1 "+3.3V" H 5765 6123 50  0000 C CNN
F 2 "" H 5750 5950 50  0001 C CNN
F 3 "" H 5750 5950 50  0001 C CNN
	1    5750 5950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 6000 5750 6000
Wire Wire Line
	5750 5950 5750 6000
Connection ~ 5750 6000
Wire Wire Line
	5750 6000 5850 6000
$Comp
L power:+3.3V #PWR020
U 1 1 5C2AF6B0
P 7150 5350
F 0 "#PWR020" H 7150 5200 50  0001 C CNN
F 1 "+3.3V" H 7165 5523 50  0000 C CNN
F 2 "" H 7150 5350 50  0001 C CNN
F 3 "" H 7150 5350 50  0001 C CNN
	1    7150 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 5100 7600 5100
Wire Wire Line
	7600 5100 7600 5400
Wire Wire Line
	7600 5400 8150 5400
Wire Wire Line
	8150 5700 7600 5700
Wire Wire Line
	7600 5700 7600 5400
Connection ~ 7600 5400
Wire Wire Line
	7150 5350 7150 5400
Wire Wire Line
	7150 5400 7600 5400
$Comp
L power:+3.3V #PWR019
U 1 1 5C2B1C0D
P 7150 3900
F 0 "#PWR019" H 7150 3750 50  0001 C CNN
F 1 "+3.3V" H 7165 4073 50  0000 C CNN
F 2 "" H 7150 3900 50  0001 C CNN
F 3 "" H 7150 3900 50  0001 C CNN
	1    7150 3900
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR018
U 1 1 5C2B1C32
P 7150 2600
F 0 "#PWR018" H 7150 2450 50  0001 C CNN
F 1 "+3.3V" H 7165 2773 50  0000 C CNN
F 2 "" H 7150 2600 50  0001 C CNN
F 3 "" H 7150 2600 50  0001 C CNN
	1    7150 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 3950 7150 3950
Wire Wire Line
	7150 3950 7150 3900
Wire Wire Line
	8150 2650 7150 2650
Wire Wire Line
	7150 2650 7150 2600
NoConn ~ 8850 2250
NoConn ~ 8850 2350
NoConn ~ 8850 3550
NoConn ~ 8850 3650
NoConn ~ 8950 5200
NoConn ~ 8950 5300
Wire Wire Line
	8850 4050 9900 4050
Wire Wire Line
	8850 3950 9900 3950
Wire Wire Line
	9900 3950 9900 3850
Wire Wire Line
	8850 3850 9850 3850
Wire Wire Line
	9850 3850 9850 3600
Wire Wire Line
	9850 3600 10100 3600
Wire Wire Line
	10100 3600 10100 3650
Wire Wire Line
	8850 3750 9800 3750
Wire Wire Line
	9800 3750 9800 3550
Wire Wire Line
	9800 3550 10300 3550
Wire Wire Line
	10300 3550 10300 3650
Wire Wire Line
	8850 2750 9900 2750
Wire Wire Line
	8850 2650 9900 2650
Wire Wire Line
	9900 2650 9900 2550
Wire Wire Line
	8850 2550 9850 2550
Wire Wire Line
	9850 2550 9850 2300
Wire Wire Line
	9850 2300 10100 2300
Wire Wire Line
	10100 2300 10100 2350
Wire Wire Line
	8850 2450 9800 2450
Wire Wire Line
	9800 2450 9800 2250
Wire Wire Line
	9800 2250 10300 2250
Wire Wire Line
	10300 2250 10300 2350
Wire Wire Line
	8950 5500 9900 5500
Wire Wire Line
	8950 5400 9850 5400
Wire Wire Line
	9850 5400 9850 5300
Wire Wire Line
	9850 5300 9900 5300
Wire Wire Line
	8950 5100 9800 5100
Wire Wire Line
	9800 5100 9800 5050
Wire Wire Line
	9800 5050 10100 5050
Wire Wire Line
	10100 5050 10100 5100
Wire Wire Line
	8950 5000 9750 5000
Wire Wire Line
	9750 5000 9750 4950
Wire Wire Line
	9750 4950 10300 4950
Wire Wire Line
	10300 4950 10300 5100
Text Notes 9250 2750 0    50   Italic 0
Negro\nVerde\nAzul\nRojo
Text Notes 9250 4050 0    50   Italic 0
Negro\nVerde\nAzul\nRojo
Text Notes 9250 5500 0    50   Italic 0
Rojo\nCafé\n\n\n\nNegro\nBlanco
Text Notes 7450 7500 0    50   ~ 10
3Axis BioTracker by [ I N T E R S P E C I F I C S ]
Text Notes 8150 7750 0    50   ~ 0
2018.12\n\n
Text Notes 10600 7650 0    50   ~ 10
[e] 1.0
$Comp
L Connector:USB_B_Micro J1
U 1 1 5C2CA140
P 1950 1500
F 0 "J1" H 2005 1967 50  0000 C CNN
F 1 "USB_B_Micro" H 2005 1876 50  0000 C CNN
F 2 "Connector_USB:USB_Micro-B_Amphenol_10103594-0001LF_Horizontal" H 2100 1450 50  0001 C CNN
F 3 "~" H 2100 1450 50  0001 C CNN
	1    1950 1500
	1    0    0    -1  
$EndComp
NoConn ~ 2100 1500
NoConn ~ 2250 1600
NoConn ~ 2250 1700
Text GLabel 2550 1300 2    50   Output ~ 10
5V_bus
$Comp
L power:+5V #PWR02
U 1 1 5C2CDC7B
P 2400 1250
F 0 "#PWR02" H 2400 1100 50  0001 C CNN
F 1 "+5V" H 2415 1423 50  0000 C CNN
F 2 "" H 2400 1250 50  0001 C CNN
F 3 "" H 2400 1250 50  0001 C CNN
	1    2400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 1300 2400 1300
Wire Wire Line
	2400 1300 2400 1250
Wire Wire Line
	2550 1300 2400 1300
Connection ~ 2400 1300
$Comp
L power:GND #PWR01
U 1 1 5C2D42B9
P 1950 2050
F 0 "#PWR01" H 1950 1800 50  0001 C CNN
F 1 "GND" H 1955 1877 50  0000 C CNN
F 2 "" H 1950 2050 50  0001 C CNN
F 3 "" H 1950 2050 50  0001 C CNN
	1    1950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1900 1950 2000
Wire Wire Line
	1850 1900 1850 2000
Wire Wire Line
	1850 2000 1950 2000
Connection ~ 1950 2000
Wire Wire Line
	1950 2000 1950 2050
$Comp
L Connector:Jack-DC J2
U 1 1 5C2DC0F7
P 1950 2800
F 0 "J2" H 2005 3125 50  0000 C CNN
F 1 "Jack-DC" H 2005 3034 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 2000 2760 50  0001 C CNN
F 3 "~" H 2000 2760 50  0001 C CNN
	1    1950 2800
	1    0    0    -1  
$EndComp
Text GLabel 2550 2700 2    50   Output ~ 10
12V_bus
$Comp
L power:+12V #PWR03
U 1 1 5C2DC5B4
P 2400 2650
F 0 "#PWR03" H 2400 2500 50  0001 C CNN
F 1 "+12V" H 2415 2823 50  0000 C CNN
F 2 "" H 2400 2650 50  0001 C CNN
F 3 "" H 2400 2650 50  0001 C CNN
	1    2400 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 2700 2400 2700
Wire Wire Line
	2400 2700 2400 2650
Wire Wire Line
	2550 2700 2400 2700
Connection ~ 2400 2700
$Comp
L power:GND #PWR04
U 1 1 5C2E17AC
P 2400 2950
F 0 "#PWR04" H 2400 2700 50  0001 C CNN
F 1 "GND" H 2405 2777 50  0000 C CNN
F 2 "" H 2400 2950 50  0001 C CNN
F 3 "" H 2400 2950 50  0001 C CNN
	1    2400 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	2250 2900 2400 2900
Wire Wire Line
	2400 2900 2400 2950
NoConn ~ 5350 5100
NoConn ~ 5350 5000
NoConn ~ 5350 4900
NoConn ~ 5350 4800
NoConn ~ 5350 4700
NoConn ~ 5350 4600
NoConn ~ 5350 4500
NoConn ~ 5350 4400
NoConn ~ 5350 4300
NoConn ~ 5350 4200
NoConn ~ 3350 5500
NoConn ~ 5350 5300
NoConn ~ 5350 5400
NoConn ~ 5350 5500
NoConn ~ 5350 5600
NoConn ~ 5350 5700
NoConn ~ 5350 4000
NoConn ~ 5350 3900
NoConn ~ 3350 5100
NoConn ~ 3350 5400
NoConn ~ 5350 5900
NoConn ~ 5350 3700
NoConn ~ 5350 3800
$Comp
L Connector:Conn_01x03_Male J3
U 1 1 5C2D6F24
P 5900 2500
F 0 "J3" H 5873 2523 50  0000 R CNN
F 1 "Conn_01x03_Male" H 5873 2432 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5900 2500 50  0001 C CNN
F 3 "~" H 5900 2500 50  0001 C CNN
	1    5900 2500
	-1   0    0    -1  
$EndComp
Text GLabel 5700 2500 0    50   Input ~ 0
LED1
Text GLabel 5700 2400 0    50   Input ~ 0
LED2
$Comp
L power:GND #PWR0101
U 1 1 5C2D701F
P 5600 2650
F 0 "#PWR0101" H 5600 2400 50  0001 C CNN
F 1 "GND" H 5605 2477 50  0000 C CNN
F 2 "" H 5600 2650 50  0001 C CNN
F 3 "" H 5600 2650 50  0001 C CNN
	1    5600 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2650 5600 2600
Wire Wire Line
	5600 2600 5700 2600
NoConn ~ 5350 5200
NoConn ~ 5350 4100
NoConn ~ 3350 5200
NoConn ~ 3350 5300
NoConn ~ 6400 1450
$EndSCHEMATC
