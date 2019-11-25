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

## soldering!

Now it is time to start SOLDERING!!!
Start withe the small components and finish with the battery holder, remember to put some double sided tape on the battery holder befor you solder it for strength.

So start with the resistors (the small cilinders with 2 wires), the value is written on the piece of paper. you can also decode the colorcode, look at the decoder that is attached or just google "resistor color code".

Now continu with the progressively larger components. after you are done sodering, "flash" your bord with the Arduino IDE. Bob or luca can help you with that, but you can do it yourself! (witch is arguably more fun) Just follow the instructions on the GitHub projectpage. https://github.com/lucanatorvs/project-liberation

\pagebreak

## setting up your wether station to connect with the WOW server:
when you get home, start by setting up your account with the metoffice. go to http://wow.metoffice.gov.uk/sites and klick "Sign Up", "new account", fill in your info and register!
now check your email for login instructions. click the link in your mail and log back in. now go to "http://wow.metoffice.gov.uk" and click on "enter a site".

now fill in the location, and the site name, the time zone, and as the "Authentication Key" think of an 6 digit number. NOT "123456". and remember this!!!
At "Above Ground Measurements" for "Air Temperature" select "Hecto Pascal". 
At "Pressure" for "Pressure At Station" select "Hecto Pascal"
At "Other Observations" for "Relative Humidity" select "Captured"
leave the rest alone.
now fill in other relative information is aplicable.
after you filed in all your info click accept.

Now if you get the "Site Created!" message, your almost done! click "view sites" and in the colom "Search for Users Sites:" check out your new site. under the map is a code like "8b9cd787-930f-ea11-b265-0003ff5990ac", this is your site id, remember to copy it without the brackets but with the " - ".
now turn on your WOW monitor sensor bord, and hold the button. hold it until a new wifi network is avalible, "WOW-MONITOR-****" klick it and you should be redirected to a website in wich you have to fill in the "site id" and the 6 digit number. 

![http://wow.metoffice.gov.uk/sites](wow.qr)

![https://github.com/lucanatorvs/project-liberation](github.png)

![](chicken.png)

![van: https://www.resistorguide.com/standards-and-codes/resistor-color-code/resistor_color_codes_chart/](resistor_color_codes_chart.png)

\includepdf[page={1}]{schematic.pdf}


\includepdf[page={1}]{pcb.pdf} 