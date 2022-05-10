EESchema Schematic File Version 4
EELAYER 30 0
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
L Device:R R1
U 1 1 5F218D8E
P 6250 2950
F 0 "R1" V 6043 2950 50  0000 C CNN
F 1 "18k" V 6134 2950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6180 2950 50  0001 C CNN
F 3 "~" H 6250 2950 50  0001 C CNN
	1    6250 2950
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 2450 5100 2450
Wire Wire Line
	5100 2550 4700 2550
Wire Wire Line
	4700 2650 5100 2650
Wire Wire Line
	5100 2750 4700 2750
Wire Wire Line
	4700 2850 5100 2850
Wire Wire Line
	4700 2950 5100 2950
Wire Wire Line
	4700 3050 5100 3050
Wire Wire Line
	5100 3150 4700 3150
Wire Wire Line
	4700 3250 5100 3250
Wire Wire Line
	5100 3350 4700 3350
Wire Wire Line
	5800 2950 5950 2950
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 5F21AB49
P 2600 2750
F 0 "J1" H 2708 3231 50  0000 C CNN
F 1 "Conn_01x08_Male" H 2708 3140 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x08_P2.54mm_Vertical" H 2600 2750 50  0001 C CNN
F 3 "~" H 2600 2750 50  0001 C CNN
	1    2600 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 2450 3400 2650
Wire Wire Line
	3400 2650 3900 2650
Wire Wire Line
	2800 2550 3150 2550
Wire Wire Line
	3450 2550 3450 2450
Wire Wire Line
	3450 2450 3900 2450
Wire Wire Line
	3900 2550 3500 2550
Wire Wire Line
	3500 2550 3500 2600
Wire Wire Line
	3500 2600 3000 2600
Wire Wire Line
	2900 2600 2900 2650
Wire Wire Line
	2900 2650 2800 2650
Wire Wire Line
	2800 2750 2950 2750
Wire Wire Line
	2800 3150 2800 3850
Wire Wire Line
	2800 3850 3050 3850
Wire Wire Line
	6400 3850 6400 2950
Wire Wire Line
	5800 2450 5950 2450
Wire Wire Line
	5950 2450 5950 2950
Connection ~ 5950 2950
Wire Wire Line
	5950 2950 6100 2950
Wire Wire Line
	5950 2950 5950 3350
Wire Wire Line
	5950 3350 5800 3350
Wire Wire Line
	2800 2850 3500 2850
Wire Wire Line
	3500 2850 3500 3050
Wire Wire Line
	2800 3050 3500 3050
Connection ~ 3500 3050
$Comp
L power:GND #PWR01
U 1 1 5F223AA4
P 3500 4100
F 0 "#PWR01" H 3500 3850 50  0001 C CNN
F 1 "GND" H 3505 3927 50  0000 C CNN
F 2 "" H 3500 4100 50  0001 C CNN
F 3 "" H 3500 4100 50  0001 C CNN
	1    3500 4100
	1    0    0    -1  
$EndComp
Text Label 3800 2950 0    50   ~ 0
5V
Wire Wire Line
	4250 2950 4250 2500
Wire Wire Line
	3500 3300 3500 3500
Wire Wire Line
	3500 3050 3500 3300
Connection ~ 3500 3300
Wire Wire Line
	3500 3300 4250 3300
$Comp
L IN-14_Daughter-rescue:74141-DIP-74141 U1
U 1 1 5F218278
P 4250 2900
F 0 "U1" H 4300 3667 50  0000 C CNN
F 1 "74141-DIP" H 4300 3576 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 4250 2900 50  0001 C CNN
F 3 "" H 4450 3350 60  0000 C CNN
	1    4250 2900
	1    0    0    -1  
$EndComp
$Comp
L IN-14_Daughter-rescue:IN-14-nixies-us N1
U 1 1 5F227C34
P 5400 2850
F 0 "N1" H 5450 3595 45  0000 C CNN
F 1 "IN-14" H 5400 2850 45  0001 L BNN
F 2 "IN-14:CPA_13" H 5430 3000 20  0001 C CNN
F 3 "" H 5400 2850 50  0001 C CNN
	1    5400 2850
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Counter_Clockwise J2
U 1 1 5F32B282
P 2750 4450
F 0 "J2" H 2800 4767 50  0000 C CNN
F 1 "Conn_02x04_Counter_Clockwise" H 2800 4676 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x04_P2.54mm_Vertical" H 2750 4450 50  0001 C CNN
F 3 "~" H 2750 4450 50  0001 C CNN
	1    2750 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 2450 3250 2450
Wire Wire Line
	2800 2950 3300 2950
Wire Wire Line
	3050 4350 3050 3850
Connection ~ 3050 3850
Wire Wire Line
	3050 3850 6400 3850
Wire Wire Line
	3500 3500 3700 3500
Wire Wire Line
	3700 3500 3700 4450
Wire Wire Line
	3700 4450 3050 4450
Connection ~ 3500 3500
Wire Wire Line
	3500 3500 3500 4100
Wire Wire Line
	3700 4450 3700 4650
Wire Wire Line
	3700 4650 3050 4650
Connection ~ 3700 4450
Wire Wire Line
	3050 4550 3300 4550
Wire Wire Line
	3300 4550 3300 2950
Connection ~ 3300 2950
Wire Wire Line
	3300 2950 4250 2950
Wire Wire Line
	2950 2750 2950 3750
Wire Wire Line
	2950 3750 2350 3750
Wire Wire Line
	2350 3750 2350 4650
Wire Wire Line
	2350 4650 2550 4650
Connection ~ 2950 2750
Wire Wire Line
	2950 2750 3900 2750
Wire Wire Line
	3000 2600 3000 3700
Wire Wire Line
	3000 3700 2300 3700
Wire Wire Line
	2300 3700 2300 4550
Wire Wire Line
	2300 4550 2550 4550
Connection ~ 3000 2600
Wire Wire Line
	3000 2600 2900 2600
Wire Wire Line
	3150 2550 3150 3650
Wire Wire Line
	3150 3650 2150 3650
Wire Wire Line
	2150 3650 2150 4450
Wire Wire Line
	2150 4450 2550 4450
Connection ~ 3150 2550
Wire Wire Line
	3150 2550 3450 2550
Wire Wire Line
	3250 2450 3250 3600
Wire Wire Line
	3250 3600 2250 3600
Wire Wire Line
	2250 3600 2250 4350
Wire Wire Line
	2250 4350 2550 4350
Connection ~ 3250 2450
Wire Wire Line
	3250 2450 3400 2450
$EndSCHEMATC