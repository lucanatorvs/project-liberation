EESchema Schematic File Version 4
LIBS:liberation-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "weather bender"
Date "2019-11-15"
Rev "0.1"
Comp "HHS"
Comment1 "Bob Swinkels"
Comment2 "Luca van Straaten"
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ESP32-WROOM-32D:ESP32-WROOM-32D U?
U 1 1 5DCEDBE2
P 3550 2100
F 0 "U?" H 3550 3667 50  0000 C CNN
F 1 "ESP32-WROOM-32D" H 3550 3576 50  0000 C CNN
F 2 "MODULE_ESP32-WROOM-32D" H 3550 2100 50  0001 L BNN
F 3 "Espressif Systems" H 3550 2100 50  0001 L BNN
F 4 "None" H 3550 2100 50  0001 L BNN "Field4"
F 5 "Module Espressif Systems" H 3550 2100 50  0001 L BNN "Field5"
F 6 "Unavailable" H 3550 2100 50  0001 L BNN "Field6"
F 7 "ESP32-WROOM-32D" H 3550 2100 50  0001 L BNN "Field7"
F 8 "IC: SoC; GPIO, I2C, I2S, IR, SD, SDIO, SPI, UART; 2.7÷3.6VDC; 20dBm" H 3550 2100 50  0001 L BNN "Field8"
	1    3550 2100
	1    0    0    -1  
$EndComp
$Comp
L Sensor:BME280 U?
U 1 1 5DCF0C74
P 5500 2700
F 0 "U?" H 5071 2746 50  0000 R CNN
F 1 "BME280" H 5071 2655 50  0000 R CNN
F 2 "Package_LGA:Bosch_LGA-8_2.5x2.5mm_P0.65mm_ClockwisePinNumbering" H 7000 2250 50  0001 C CNN
F 3 "https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280-DS002.pdf" H 5500 2500 50  0001 C CNN
	1    5500 2700
	1    0    0    -1  
$EndComp
Text GLabel 6500 1000 0    50   Input ~ 0
RXD
Text GLabel 6500 1100 0    50   Input ~ 0
TXD
Text GLabel 6500 1200 0    50   Input ~ 0
DTR
Text GLabel 6500 1300 0    50   Input ~ 0
RTS
$Comp
L power:GND #PWR?
U 1 1 5DCF64FC
P 6500 1400
F 0 "#PWR?" H 6500 1150 50  0001 C CNN
F 1 "GND" H 6505 1227 50  0000 C CNN
F 2 "" H 6500 1400 50  0001 C CNN
F 3 "" H 6500 1400 50  0001 C CNN
	1    6500 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DCF691B
P 4250 3400
F 0 "#PWR?" H 4250 3150 50  0001 C CNN
F 1 "GND" H 4255 3227 50  0000 C CNN
F 2 "" H 4250 3400 50  0001 C CNN
F 3 "" H 4250 3400 50  0001 C CNN
	1    4250 3400
	1    0    0    -1  
$EndComp
Text GLabel 2550 1700 0    50   Input ~ 0
RXD
Text GLabel 2550 1800 0    50   Input ~ 0
TXD
$Comp
L Device:R R?
U 1 1 5DCF7C7E
P 2700 1800
F 0 "R?" V 2800 1800 50  0000 C CNN
F 1 "1k" V 2700 1800 50  0000 C CNN
F 2 "" V 2630 1800 50  0001 C CNN
F 3 "~" H 2700 1800 50  0001 C CNN
	1    2700 1800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DCF7556
P 2700 1700
F 0 "R?" V 2600 1700 50  0000 C CNN
F 1 "1k" V 2700 1700 50  0000 C CNN
F 2 "" V 2630 1700 50  0001 C CNN
F 3 "~" H 2700 1700 50  0001 C CNN
	1    2700 1700
	0    1    1    0   
$EndComp
Text GLabel 2850 1000 0    50   Input ~ 0
RESET
Text GLabel 1050 1200 0    50   Input ~ 0
RESET
$Comp
L power:GND #PWR?
U 1 1 5DCFA0A3
P 1200 1500
F 0 "#PWR?" H 1200 1250 50  0001 C CNN
F 1 "GND" H 1205 1327 50  0000 C CNN
F 2 "" H 1200 1500 50  0001 C CNN
F 3 "" H 1200 1500 50  0001 C CNN
	1    1200 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DCFA733
P 1200 1350
F 0 "C?" H 1315 1396 50  0000 L CNN
F 1 "1u" H 1315 1305 50  0000 L CNN
F 2 "" H 1238 1200 50  0001 C CNN
F 3 "~" H 1200 1350 50  0001 C CNN
	1    1200 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DCFB3DD
P 1200 1050
F 0 "R?" H 1270 1096 50  0000 L CNN
F 1 "10k" V 1200 1000 50  0000 L CNN
F 2 "" V 1130 1050 50  0001 C CNN
F 3 "~" H 1200 1050 50  0001 C CNN
	1    1200 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 1200 1200 1200
Connection ~ 1200 1200
Text GLabel 4250 1000 2    50   Input ~ 0
BOOT
$Comp
L Device:Battery BT?
U 1 1 5DCFFBA2
P 900 7150
F 0 "BT?" H 1008 7196 50  0000 L CNN
F 1 "Battery" H 1008 7105 50  0000 L CNN
F 2 "" V 900 7210 50  0001 C CNN
F 3 "~" V 900 7210 50  0001 C CNN
	1    900  7150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD00794
P 900 7350
F 0 "#PWR?" H 900 7100 50  0001 C CNN
F 1 "GND" H 905 7177 50  0000 C CNN
F 2 "" H 900 7350 50  0001 C CNN
F 3 "" H 900 7350 50  0001 C CNN
	1    900  7350
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_SPST SW?
U 1 1 5DD00D81
P 900 6750
F 0 "SW?" V 946 6662 50  0000 R CNN
F 1 "MHS122" V 855 6662 50  0000 R CNN
F 2 "" H 900 6750 50  0001 C CNN
F 3 "~" H 900 6750 50  0001 C CNN
	1    900  6750
	0    -1   -1   0   
$EndComp
$Comp
L Switch:SW_Push SW?
U 1 1 5DD0428B
P 10650 1100
F 0 "SW?" V 10604 1248 50  0000 L CNN
F 1 "FSM4JAH" V 10695 1248 50  0000 L CNN
F 2 "" H 10650 1300 50  0001 C CNN
F 3 "~" H 10650 1300 50  0001 C CNN
	1    10650 1100
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DD05738
P 10650 1450
F 0 "R?" H 10700 1400 50  0000 L CNN
F 1 "4.7k" V 10650 1350 50  0000 L CNN
F 2 "" V 10580 1450 50  0001 C CNN
F 3 "~" H 10650 1450 50  0001 C CNN
	1    10650 1450
	1    0    0    -1  
$EndComp
Text GLabel 10450 1300 0    50   Input ~ 0
RECONF
Wire Wire Line
	10650 1300 10450 1300
Connection ~ 10650 1300
$Comp
L power:GND #PWR?
U 1 1 5DD069E7
P 10650 1600
F 0 "#PWR?" H 10650 1350 50  0001 C CNN
F 1 "GND" H 10655 1427 50  0000 C CNN
F 2 "" H 10650 1600 50  0001 C CNN
F 3 "" H 10650 1600 50  0001 C CNN
	1    10650 1600
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DD07351
P 10650 900
F 0 "#PWR?" H 10650 750 50  0001 C CNN
F 1 "+3.3V" H 10665 1073 50  0000 C CNN
F 2 "" H 10650 900 50  0001 C CNN
F 3 "" H 10650 900 50  0001 C CNN
	1    10650 900 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DD07B08
P 4250 800
F 0 "#PWR?" H 4250 650 50  0001 C CNN
F 1 "+3.3V" H 4265 973 50  0000 C CNN
F 2 "" H 4250 800 50  0001 C CNN
F 3 "" H 4250 800 50  0001 C CNN
	1    4250 800 
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DD08266
P 6500 900
F 0 "#PWR?" H 6500 750 50  0001 C CNN
F 1 "+3.3V" H 6515 1073 50  0000 C CNN
F 2 "" H 6500 900 50  0001 C CNN
F 3 "" H 6500 900 50  0001 C CNN
	1    6500 900 
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DCF56CC
P 1250 2500
F 0 "R?" V 1150 2500 50  0000 C CNN
F 1 "10k" V 1250 2500 50  0000 C CNN
F 2 "" V 1180 2500 50  0001 C CNN
F 3 "~" H 1250 2500 50  0001 C CNN
	1    1250 2500
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 5DCF64FD
P 1250 3200
F 0 "R?" V 1150 3200 50  0000 C CNN
F 1 "10k" V 1250 3200 50  0000 C CNN
F 2 "" V 1180 3200 50  0001 C CNN
F 3 "~" H 1250 3200 50  0001 C CNN
	1    1250 3200
	0    1    1    0   
$EndComp
Text GLabel 950  2500 0    50   Input ~ 0
RTS
Text GLabel 950  3200 0    50   Input ~ 0
DTR
Text GLabel 1600 2200 0    50   Input ~ 0
BOOT
Text GLabel 1600 3500 0    50   Input ~ 0
RESET
Wire Wire Line
	1600 2200 1700 2200
Wire Wire Line
	1600 3500 1700 3500
Wire Wire Line
	1700 3500 1700 3400
Wire Wire Line
	950  2500 1100 2500
Wire Wire Line
	950  3200 1100 3200
Wire Wire Line
	1700 2200 1700 2300
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 5DCF46FB
P 1600 3200
F 0 "Q?" H 1791 3246 50  0000 L CNN
F 1 "BC547BTA" H 1791 3155 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 1800 3125 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 1600 3200 50  0001 L CNN
	1    1600 3200
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q?
U 1 1 5DCF3487
P 1600 2500
F 0 "Q?" H 1791 2546 50  0000 L CNN
F 1 "BC547BTA" H 1791 2455 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 1800 2425 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 1600 2500 50  0001 L CNN
	1    1600 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 2800 1450 2800
Wire Wire Line
	1450 2800 1600 2900
Wire Wire Line
	1600 2900 1700 2900
Wire Wire Line
	1700 2900 1700 3000
Wire Wire Line
	1100 2500 1100 2800
Connection ~ 1100 2500
Wire Wire Line
	1700 2700 1700 2800
Wire Wire Line
	1700 2800 1600 2800
Wire Wire Line
	1600 2800 1450 2900
Wire Wire Line
	1450 2900 1100 2900
Wire Wire Line
	1100 2900 1100 3200
Connection ~ 1100 3200
$Comp
L power:+3.3V #PWR?
U 1 1 5DD18507
P 1200 900
F 0 "#PWR?" H 1200 750 50  0001 C CNN
F 1 "+3.3V" H 1215 1073 50  0000 C CNN
F 2 "" H 1200 900 50  0001 C CNN
F 3 "" H 1200 900 50  0001 C CNN
	1    1200 900 
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD36853
P 5600 3300
F 0 "#PWR?" H 5600 3050 50  0001 C CNN
F 1 "GND" H 5605 3127 50  0000 C CNN
F 2 "" H 5600 3300 50  0001 C CNN
F 3 "" H 5600 3300 50  0001 C CNN
	1    5600 3300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD36CF0
P 5400 3300
F 0 "#PWR?" H 5400 3050 50  0001 C CNN
F 1 "GND" H 5405 3127 50  0000 C CNN
F 2 "" H 5400 3300 50  0001 C CNN
F 3 "" H 5400 3300 50  0001 C CNN
	1    5400 3300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD373FA
P 5750 1800
F 0 "C?" V 5498 1800 50  0000 C CNN
F 1 "100n" V 5589 1800 50  0000 C CNN
F 2 "" H 5788 1650 50  0001 C CNN
F 3 "~" H 5750 1800 50  0001 C CNN
	1    5750 1800
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD3B3D6
P 5900 1950
F 0 "#PWR?" H 5900 1700 50  0001 C CNN
F 1 "GND" H 6050 1850 50  0000 C CNN
F 2 "" H 5900 1950 50  0001 C CNN
F 3 "" H 5900 1950 50  0001 C CNN
	1    5900 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2100 5600 1800
Wire Wire Line
	5400 2100 5400 1800
Wire Wire Line
	5400 1800 5600 1800
Connection ~ 5600 1800
Wire Wire Line
	5900 1800 5900 1950
$Comp
L power:+3.3V #PWR?
U 1 1 5DD3F0CF
P 5400 1800
F 0 "#PWR?" H 5400 1650 50  0001 C CNN
F 1 "+3.3V" H 5415 1973 50  0000 C CNN
F 2 "" H 5400 1800 50  0001 C CNN
F 3 "" H 5400 1800 50  0001 C CNN
	1    5400 1800
	1    0    0    -1  
$EndComp
Connection ~ 5400 1800
Text GLabel 5250 1150 3    50   Input ~ 0
SDA
Text GLabel 6100 2600 2    50   Input ~ 0
SCL
$Comp
L power:GND #PWR?
U 1 1 5DD4022D
P 6100 2400
F 0 "#PWR?" H 6100 2150 50  0001 C CNN
F 1 "GND" H 6200 2400 50  0000 C CNN
F 2 "" H 6100 2400 50  0001 C CNN
F 3 "" H 6100 2400 50  0001 C CNN
	1    6100 2400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DD423D5
P 5050 1000
F 0 "R?" H 4950 1000 50  0000 C CNN
F 1 "4.7k" V 5050 1000 50  0000 C CNN
F 2 "" V 4980 1000 50  0001 C CNN
F 3 "~" H 5050 1000 50  0001 C CNN
	1    5050 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 5DD43EC6
P 5250 1000
F 0 "R?" H 5350 1000 50  0000 C CNN
F 1 "4.7k" V 5250 1000 50  0000 C CNN
F 2 "" V 5180 1000 50  0001 C CNN
F 3 "~" H 5250 1000 50  0001 C CNN
	1    5250 1000
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR?
U 1 1 5DD4ABDA
P 6100 3000
F 0 "#PWR?" H 6100 2850 50  0001 C CNN
F 1 "+3.3V" H 6250 3050 50  0000 C CNN
F 2 "" H 6100 3000 50  0001 C CNN
F 3 "" H 6100 3000 50  0001 C CNN
	1    6100 3000
	1    0    0    -1  
$EndComp
Text GLabel 4250 2300 2    50   Input ~ 0
SCL
Text GLabel 4250 2200 2    50   Input ~ 0
SDA
Text GLabel 5050 1150 3    50   Input ~ 0
SCL
$Comp
L power:+3.3V #PWR?
U 1 1 5DD53CFF
P 5150 850
F 0 "#PWR?" H 5150 700 50  0001 C CNN
F 1 "+3.3V" H 5150 1000 50  0000 C CNN
F 2 "" H 5150 850 50  0001 C CNN
F 3 "" H 5150 850 50  0001 C CNN
	1    5150 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 850  5150 850 
Connection ~ 5150 850 
Wire Wire Line
	5150 850  5250 850 
Text GLabel 6100 2800 2    50   Input ~ 0
SDA
$Comp
L Regulator_Linear:MCP1825S U?
U 1 1 5DD80B21
P 2050 6550
F 0 "U?" H 2050 6792 50  0000 C CNN
F 1 "NJU7223F33" H 2050 6701 50  0000 C CNN
F 2 "" H 1950 6700 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/devicedoc/22056b.pdf" H 2050 6800 50  0001 C CNN
	1    2050 6550
	1    0    0    -1  
$EndComp
Wire Wire Line
	900  6550 1450 6550
$Comp
L power:+3.3V #PWR?
U 1 1 5DD823F0
P 2900 6550
F 0 "#PWR?" H 2900 6400 50  0001 C CNN
F 1 "+3.3V" H 2915 6723 50  0000 C CNN
F 2 "" H 2900 6550 50  0001 C CNN
F 3 "" H 2900 6550 50  0001 C CNN
	1    2900 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD82D83
P 1450 6700
F 0 "C?" H 1565 6746 50  0000 L CNN
F 1 "100n" H 1565 6655 50  0000 L CNN
F 2 "" H 1488 6550 50  0001 C CNN
F 3 "~" H 1450 6700 50  0001 C CNN
	1    1450 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5DD8579B
P 2500 6700
F 0 "C?" H 2615 6746 50  0000 L CNN
F 1 "100n" H 2615 6655 50  0000 L CNN
F 2 "" H 2538 6550 50  0001 C CNN
F 3 "~" H 2500 6700 50  0001 C CNN
	1    2500 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD86141
P 1450 6850
F 0 "#PWR?" H 1450 6600 50  0001 C CNN
F 1 "GND" H 1455 6677 50  0000 C CNN
F 2 "" H 1450 6850 50  0001 C CNN
F 3 "" H 1450 6850 50  0001 C CNN
	1    1450 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD864EB
P 2050 6850
F 0 "#PWR?" H 2050 6600 50  0001 C CNN
F 1 "GND" H 2055 6677 50  0000 C CNN
F 2 "" H 2050 6850 50  0001 C CNN
F 3 "" H 2050 6850 50  0001 C CNN
	1    2050 6850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5DD868EA
P 2500 6850
F 0 "#PWR?" H 2500 6600 50  0001 C CNN
F 1 "GND" H 2505 6677 50  0000 C CNN
F 2 "" H 2500 6850 50  0001 C CNN
F 3 "" H 2500 6850 50  0001 C CNN
	1    2500 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 6550 1750 6550
Connection ~ 1450 6550
Wire Wire Line
	2350 6550 2500 6550
Wire Wire Line
	2500 6550 2900 6550
Connection ~ 2500 6550
$Comp
L Connector:Conn_01x06_Male Jserial
U 1 1 5DD8A7C9
P 6700 1200
F 0 "Jserial" H 6672 1082 50  0000 R CNN
F 1 "Hedd_01x06_Male" H 6672 1173 50  0000 R CNN
F 2 "" H 6700 1200 50  0001 C CNN
F 3 "~" H 6700 1200 50  0001 C CNN
	1    6700 1200
	-1   0    0    1   
$EndComp
$EndSCHEMATC
