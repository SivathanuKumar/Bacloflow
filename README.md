Instruction Manual – For Bacloflow 2.0 and Bacloflow 3.0

Table Of Contents:
1.	Introduction
2.	Precautions
3.	Equipment and Materials
4.	Circuit Pinout
5.	Required Libraries
6.	Wi-Fi connectivity
7.	Analyzing results
8.	Troubleshooting and Contact Information.

Introduction:

Intrathecal baclofen therapy (IBT) is used to treat severe spasticity in patients with multiple sclerosis (MS). However, the catheter that carries medication from the implanted drug pump can fail, leading to a return of symptoms or possibly lethal baclofen withdrawal. Current methods for detecting catheter failure are time and resource intensive and come with a high degree of uncertainty. Bacloflow is an internal flow rate monitoring device that reads the flow at the beginning and end of the catheter to detect possible catheter failure. The initial prototype Bacloflow 2.0 is accurate and sensitive to small changes in flow, however, it still depends on Arduino to interface with and process relevant data for the user. Bacloflow 3.0 aims to address this issue by connecting the sensor with an external source that interfaces wirelessly with an external server that computes and displays the results remotely to the requested parties. This instruction manual guides the user in the setup process of both iteration of the device, and lists the relevant libraries required to make the device work, as well as the necessary pin diagrams, plate size description and casing structure.
Precautions:
The sensor currently utilizes unlaminated copper sheets that can be subject to contamination and oxidation, when exposed to air, which in turn can be harmful to the user when and if implanted and requires a similar alternative if planning to implant in a patient or run animal tests on. 
While the sensor itself is a low power draining add-on, the Arduino and ESP8266 used as microcontrollers require a constant 5V of power to function normally. This would ideally require a 9V battery or a USB-BB cable supplying power to the Arduino and ESP8266 regularly whenever the device is running. Over long periods of time, the readings obtained on the Arduino tend to drift from the median point and thus changes need to be accounted for. If powered using a single 9V battery, it is to be noted that the power runs out of the battery every 10 hours and will be required to replace it in order for uni9nterruptedf readings when testing. It’s recommended to use a DC 5V, 2.4A 12 Watt maximum power cell, for longer periods of isolated testing.
The current device and materials used are not suitable for implantation for animal testing and clinical trials. The current prototype acts only as proof of concept and the materials used to build it need to be substituted. This would include the copper strips as the main components of the capacitive sensor, the outer PLA casing, the aluminum shielding around the device and the plastic layer that isolates the casing from the inner sensing plates. The external wires that are connected to the copper plates also need to be accounted for. Care needs to be taken when testing in moist environments, as the device is prone to short circuiting and can cause issues. 

Equipment and materials:

Bacloflow 2.0:

1.	Arduino Uno R3
2.	Bacloflow 2.0 Casing, PLA based 3D print
3.	2x Identical copper strips, 1.5 x 2.0 inch, with a 0.4-inch diameter hole punched 0.2 inches from the top.
4.	Aluminum foil and tape to shield the casing and secure the wire connection to the strips.
5.	Thin plastic sheet to isolate the metal shielding layer from the conducting layer.
6.	0.96-inch I2C OLED display
7.	External Power source (DC 5V, 2.1A, 12 W)

Changes in equipment for Bacloflow 3.0:

1.	Using a ESP8266 Wi-Fi module over the Arduino Uno
2.	Moving from 2 analog In-Out pins to 1 analog and 1 digital pin
3.	2x 1.5 kΩ external pullup resistors
4.	2x thinner identical cooper strips, 1.0 x 1.5 inch
5.	Connecting wires and power source

Circuit Pinout:
Can be seen in the pdf



Bacloflow 3.0:
Replace the ATMEGA328P microcontroller with the ESP8266, and A0 replaced with D2 and A1 replaced to A0. Add external pull up resistor configuration to the discharge pin.
ATMEGA328P
[Bacloflow 2.0]	Change	ESP8266
[Bacloflow 3.0]
Pin A0	→	Pin D2
Pin A1	→ (Add external Pull-up)	Pin A0 
Pin-diagram for external Pull-up configuration:
 

Required Libraries:
Bacloflow is coded on the Arduino IDE version 2.0.3 (latest build as of 03/20/2023) and the following libraries are required for the programs in GitHub to run.
For Bacloflow 2.0:
1.	When using the I2C display, the respective library needs to be installed.
Adafruit GFX library by Adafruit
Adafruit BusIO by Adafruit
Adafruit SSWD1306 by Adafruit
U8g2 by Oliver – for non-Adafruit based displays.
[Link: https://github.com/olikraus/u8g2]
2.	Essential Libraries for Arduino:
SPI – interface with Arduino
Wire.h - interface with Arduino
For Bacloflow 3.0:
1.	AsyncTCP – by dvarrel – Master for building web server with files saved in flash.
[Link: https://github.com/dvarrel/ESPAsyncWebSrv]
2.	DHT sensor library – used for testing purposes to obtain temperature and humidity readings.
Installing ESP8266 for Arduino Core:
Under Boards manager: NodeMCU 0.9 (ESP-12 Module) needs to be installed and added on.
[Link: https://github.com/esp8266/Arduino]
[Stable Release used: http://arduino.esp8266.com/stable/package_esp8266com_index.json]

Wi-Fi connectivity:
Essential Libraries for establishing Wi-Fi connectivity and Asynchronous TCP access:
1.	ESPAsyncWebServer.h
2.	ESP8266WiFi.h
3.	ESPAsyncTCP.h
All other required libraries are included in the code for Bacloflow 3.0. Only the network credentials need to be changed.
SSID: change to name of current Wi-Fi network
Password: Encrypted password for the Wi-Fi network
Highcharts API is used to visualize the graph obtained on the display. Better translation to the webpage than using the Arduino IDE built-in serial monitor and plotter.
[Link: https://code.highcharts.com/8.0/highcharts.js]
Adjustments can be made to incorporate additional elements into the HTML file as in the Bacloflow 3.0 code internally. The HTML file can first have a mockup on Publisher before importing onto the code.
Analyzing Results:
While the method of receiving the results from the device varies between the two versions, the basic observations made are similar in both cases. The pull up resistor setup in Bacloflow 3.0 is designed to mirror the results obtained from Bacloflow 2.0, compensating for the change from one microcontroller to the other. During the testing and verification phase of the device, Bacloflow 2.0 was the model used to do so. All results obtained were derived from values observed on the serial plotter and serial monitor feature in the Arduino IDE. The results of the testing were tabulated and shared on GitHub. A deep analysis of the results obtained as well as inferences on those results are shared in the following presentation link below. 
Link to the results: 
https://github.com/SivathanuKumar/Bacloflow/blob/main/Testing%20Bacloflow.xlsx
Link to presentation detailing Testing and Analysis methods, process, and results:
https://shorturl.at/clmK8
Troubleshooting and Contact Information:
Bacloflow is created by two master’s students of Applied Bioengineering at the University of Washington: Sivathanu Kumar and Cormack Pegau, under the guidance of our clinical mentor, Dr. Allison Wallingford and academic mentor Soraya Bailey.

All troubleshooting requests can be submitted as Pull requests in the GitHub page where all relevant information and code is included. Requests for ideation processes, design files, and further information regarding stakeholder interviews can be received upon request to the designated email addresses.
GitHub Main link: https://github.com/SivathanuKumar/Bacloflow/tree/main
Email address: bsivathanukumar@gmail.com







