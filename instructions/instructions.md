---
author:
- Bob Swinkels
- Luca van Straaten 
header-includes:
	- \usepackage{pdfpages}
...

# WOW Monitor
### A project by Bob Swinkels and Luca van Straaten
 
--- 

## start:
do you have all the components?

check your components against the bill of materials. 

|Id |Designator|Package                        |Quantity|Designation    |
|---|----------|-------------------------------|--------|---------------|
|1  |R3,R1,R2  |Weerstand                      |3       |10k            |
|2  |C1        |Condensator                    |1       |1u             |
|3  |C2,C3,C4  |Condensator                    |3       |100n           |
|4  |Jserial1  |PinHeader_1x06_P2.54mm_Vertical|1       |Hedd_01x06_Male|
|5  |Q2,Q1     |Transistor_npn                 |2       |BC547BTA       |
|6  |R5,R4     |Weerstand                      |2       |1k             |
|7  |R6,R7,R8  |Weerstand                      |3       |4.7k           |
|8  |SW1       |Schakelaar                     |1       |MHS122K        |
|9  |SW2       |Knop                           |1       |FSM4JAH        |

Now it is time to start SOLDERING!!!
Start withe the small components and finish with the battery holder, remember to put some double sided tape on the battery holder befor you solder it for strength.

So start with the resistors (the small cilinders with 2 wires), the value is written on the piece of paper. you can also decode the colorcode, look at the decoder that is attached or just google "resistor color code".

Now continu with the progressively larger components. after you are done sodering, "flash" your bord with the Arduino IDE. Bob or luca can help you with that, but you can do it yourself! (witch is arguably more fun) Just follow the instructions on the GitHub projectpage. https://github.com/lucanatorvs/project-liberation

![https://github.com/lucanatorvs/project-liberation](github.png)

![van: https://www.resistorguide.com/standards-and-codes/resistor-color-code/resistor_color_codes_chart/](resistor_color_codes_chart.png)

\includepdf[page={1}]{schematic.pdf}


\includepdf[page={1}]{pcb.pdf} 