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
LIBS:kGeigie-cache
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
L R R1
U 1 1 58317C04
P 3850 3550
F 0 "R1" V 3643 3550 50  0000 C CNN
F 1 "4.7k" V 3734 3550 50  0000 C CNN
F 2 "" V 3780 3550 50  0000 C CNN
F 3 "" H 3850 3550 50  0000 C CNN
	1    3850 3550
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 58317C74
P 4300 4650
F 0 "R2" H 4370 4696 50  0000 L CNN
F 1 "47k" H 4370 4605 50  0000 L CNN
F 2 "" V 4230 4650 50  0000 C CNN
F 3 "" H 4300 4650 50  0000 C CNN
	1    4300 4650
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 58317CA9
P 4300 5350
F 0 "R3" H 4370 5396 50  0000 L CNN
F 1 "4.7k" H 4370 5305 50  0000 L CNN
F 2 "" V 4230 5350 50  0000 C CNN
F 3 "" H 4300 5350 50  0000 C CNN
	1    4300 5350
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 58317CD3
P 5150 3550
F 0 "R4" V 4943 3550 50  0000 C CNN
F 1 "4.7k" V 5034 3550 50  0000 C CNN
F 2 "" V 5080 3550 50  0000 C CNN
F 3 "" H 5150 3550 50  0000 C CNN
	1    5150 3550
	0    1    1    0   
$EndComp
$Comp
L R R5
U 1 1 58317D1F
P 5600 3550
F 0 "R5" V 5393 3550 50  0000 C CNN
F 1 "100k" V 5484 3550 50  0000 C CNN
F 2 "" V 5530 3550 50  0000 C CNN
F 3 "" H 5600 3550 50  0000 C CNN
	1    5600 3550
	0    1    1    0   
$EndComp
$Comp
L R R6
U 1 1 58317D52
P 6200 2450
F 0 "R6" H 6270 2496 50  0000 L CNN
F 1 "56" H 6270 2405 50  0000 L CNN
F 2 "" V 6130 2450 50  0000 C CNN
F 3 "" H 6200 2450 50  0000 C CNN
	1    6200 2450
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58317E28
P 5400 4050
F 0 "C1" H 5515 4096 50  0000 L CNN
F 1 "100n" H 5515 4005 50  0000 L CNN
F 2 "" H 5438 3900 50  0000 C CNN
F 3 "" H 5400 4050 50  0000 C CNN
	1    5400 4050
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_BCE Q1
U 1 1 58317EE8
P 6100 3550
F 0 "Q1" H 6291 3596 50  0000 L CNN
F 1 "C1815" H 6291 3505 50  0000 L CNN
F 2 "" H 6300 3650 50  0000 C CNN
F 3 "" H 6100 3550 50  0000 C CNN
	1    6100 3550
	1    0    0    -1  
$EndComp
$Comp
L D D1
U 1 1 58318019
P 4750 3550
F 0 "D1" H 4750 3335 50  0000 C CNN
F 1 "N4148" H 4750 3426 50  0000 C CNN
F 2 "" H 4750 3550 50  0000 C CNN
F 3 "" H 4750 3550 50  0000 C CNN
	1    4750 3550
	-1   0    0    1   
$EndComp
$Comp
L LED D2
U 1 1 58318246
P 6200 2950
F 0 "D2" V 6246 2842 50  0000 R CNN
F 1 "LED" V 6155 2842 50  0000 R CNN
F 2 "" H 6200 2950 50  0000 C CNN
F 3 "" H 6200 2950 50  0000 C CNN
	1    6200 2950
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR4
U 1 1 583192D3
P 5400 4650
F 0 "#PWR4" H 5400 4400 50  0001 C CNN
F 1 "GND" H 5405 4477 50  0000 C CNN
F 2 "" H 5400 4650 50  0000 C CNN
F 3 "" H 5400 4650 50  0000 C CNN
	1    5400 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 58319303
P 6200 4650
F 0 "#PWR6" H 6200 4400 50  0001 C CNN
F 1 "GND" H 6205 4477 50  0000 C CNN
F 2 "" H 6200 4650 50  0000 C CNN
F 3 "" H 6200 4650 50  0000 C CNN
	1    6200 4650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 58319340
P 4300 5650
F 0 "#PWR3" H 4300 5400 50  0001 C CNN
F 1 "GND" H 4305 5477 50  0000 C CNN
F 2 "" H 4300 5650 50  0000 C CNN
F 3 "" H 4300 5650 50  0000 C CNN
	1    4300 5650
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR5
U 1 1 583195C4
P 6200 2150
F 0 "#PWR5" H 6200 2000 50  0001 C CNN
F 1 "+3.3V" H 6215 2323 50  0000 C CNN
F 2 "" H 6200 2150 50  0000 C CNN
F 3 "" H 6200 2150 50  0000 C CNN
	1    6200 2150
	1    0    0    -1  
$EndComp
Text Notes 7400 7500 0    60   ~ 0
kGeigie Schematics
$Comp
L JACK_2P J2
U 1 1 58319DC7
P 3350 5100
F 0 "J2" H 3356 5475 50  0000 C CNN
F 1 "JACK_2P" H 3356 5384 50  0000 C CNN
F 2 "" H 3350 5100 50  0000 C CNN
F 3 "" H 3350 5100 50  0000 C CNN
	1    3350 5100
	1    0    0    -1  
$EndComp
$Comp
L Screw_Terminal_1x03 J1
U 1 1 58319E54
P 3150 3550
F 0 "J1" H 3230 3992 50  0000 C CNN
F 1 "IRover" H 3230 3901 50  0000 C CNN
F 2 "" H 3150 3225 50  0001 C CNN
F 3 "" H 3125 3650 50  0001 C CNN
	1    3150 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 3350 6200 3100
Wire Wire Line
	5900 3550 5750 3550
Wire Wire Line
	5300 3550 5400 3550
Wire Wire Line
	5400 3550 5450 3550
Wire Wire Line
	5400 3900 5400 3550
Connection ~ 5400 3550
Wire Wire Line
	4900 3550 5000 3550
Wire Wire Line
	4000 3550 4300 3550
Wire Wire Line
	4300 3550 4600 3550
Wire Wire Line
	4300 3550 4300 4500
Connection ~ 4300 3550
Wire Wire Line
	4300 4800 4300 4950
Wire Wire Line
	4300 4950 4300 5200
Wire Wire Line
	6200 2800 6200 2600
Wire Wire Line
	6200 3750 6200 4650
Wire Wire Line
	5400 4200 5400 4650
Wire Wire Line
	4300 5500 4300 5550
Wire Wire Line
	4300 5550 4300 5650
Wire Wire Line
	6200 2150 6200 2300
Wire Wire Line
	3800 4950 4300 4950
Connection ~ 4300 4950
Wire Wire Line
	3800 5200 3800 5350
Wire Wire Line
	3800 5350 3800 5550
Wire Wire Line
	3800 5550 4300 5550
Connection ~ 4300 5550
Wire Wire Line
	3800 5350 3900 5350
Wire Wire Line
	3900 5350 3900 5100
Wire Wire Line
	3900 5100 3800 5100
Connection ~ 3800 5350
Wire Wire Line
	3350 3550 3700 3550
$Comp
L GND #PWR2
U 1 1 5831A165
P 3700 3950
F 0 "#PWR2" H 3700 3700 50  0001 C CNN
F 1 "GND" H 3705 3777 50  0000 C CNN
F 2 "" H 3700 3950 50  0000 C CNN
F 3 "" H 3700 3950 50  0000 C CNN
	1    3700 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3750 3700 3750
Wire Wire Line
	3700 3750 3700 3950
$Comp
L +3.3V #PWR1
U 1 1 5831A1BC
P 3500 2850
F 0 "#PWR1" H 3500 2700 50  0001 C CNN
F 1 "+3.3V" H 3515 3023 50  0000 C CNN
F 2 "" H 3500 2850 50  0000 C CNN
F 3 "" H 3500 2850 50  0000 C CNN
	1    3500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 3350 3500 3350
Wire Wire Line
	3500 3350 3500 2850
$EndSCHEMATC