EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:arduino_shieldsNCL
LIBS:blimb-shield-cache
EELAYER 25 0
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
L ARDUINO_SHIELD servo_bt_shield1
U 1 1 56DD8ABF
P 4550 3500
F 0 "servo_bt_shield1" H 4200 4450 60  0000 C CNN
F 1 "ARDUINO_SHIELD" H 4600 2550 60  0000 C CNN
F 2 "arduino_shields:ARDUINO SHIELD" H 4550 3500 60  0001 C CNN
F 3 "" H 4550 3500 60  0000 C CNN
	1    4550 3500
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 56DD903F
P 3100 3200
F 0 "C2" H 3125 3300 50  0000 L CNN
F 1 "220uF" H 3125 3100 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_10x10.5" H 3138 3050 50  0001 C CNN
F 3 "" H 3100 3200 50  0000 C CNN
	1    3100 3200
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 56DD9146
P 2850 3200
F 0 "C1" H 2875 3300 50  0000 L CNN
F 1 "220uF" H 2875 3100 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_10x10.5" H 2888 3050 50  0001 C CNN
F 3 "" H 2850 3200 50  0000 C CNN
	1    2850 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 3050 3500 3050
Wire Wire Line
	3500 3050 3500 3300
Wire Wire Line
	3500 3300 3600 3300
Connection ~ 3100 3050
Wire Wire Line
	2850 3400 3600 3400
Wire Wire Line
	3100 3400 3100 3350
Wire Wire Line
	2850 3400 2850 3350
Connection ~ 3100 3400
$Comp
L R R2
U 1 1 56FCD874
P 3100 4850
F 0 "R2" V 3180 4850 50  0000 C CNN
F 1 "1k" V 3100 4850 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3030 4850 50  0001 C CNN
F 3 "" H 3100 4850 50  0000 C CNN
	1    3100 4850
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 56FCD8C5
P 3100 4400
F 0 "R1" V 3180 4400 50  0000 C CNN
F 1 "2k" V 3100 4400 50  0000 C CNN
F 2 "Resistors_SMD:R_0805" V 3030 4400 50  0001 C CNN
F 3 "" H 3100 4400 50  0000 C CNN
	1    3100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 4250 3100 3500
Wire Wire Line
	3100 3500 3600 3500
Wire Wire Line
	3100 4550 3100 4700
Wire Wire Line
	3100 5000 3100 5050
Wire Wire Line
	3100 5050 5650 5050
Wire Wire Line
	5650 5050 5650 4200
Wire Wire Line
	5650 4200 5500 4200
$EndSCHEMATC
