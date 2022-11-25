# Smart_BankLocker-IOT
IOT project to build a security system for the locker room in the bank and light automation inside the room.

## Sensors Used :
* 1.Ultrasonic Sensor
* 2.PIR Sensor
* 3.LDR Sensor

## Components used - 
* Breadboard, 
* 3 Sensors mentioned above,
* Connecting wires or jumper wires
* NodeMCU
* LED bulb
* Resitor

## Software tools -
* Arduino IDE
* Adafruit.io - to upload the data to cloud
* IFTTT - to get data from the cloud.

## Design
  The proposed system contains two subsystems, which is Door Security subsystem using ultrasonic sensor and Indoor LightAutomation system using LDR and PIR sensor.
  ### The design of Door Security subsystem involves the incorporation of the following steps: -
  * 1. One Ultrasonic sensor is incorporated – to sense the door from inside of the home pointing towards it.
  * 2. The NodeMCU has to be programmed in order to constantly calculate the distance of the closed door from the sensor.
  * 3. When the door distance reduces, the warning intrusion mail should be sent to the owner of the house.
  ### The design of Indoor Light Automation subsystem involves the incorporation of the following steps: -
  * 1. One LDR sensor is incorporated – to sense the light intensity surrounding the sensor.
  * 2. One PIR sensor is incorporated – to sense the presence of living being in the room.
  * 3. The NodeMCU has to be programmed for constant monitoring of light intensity and presence of living being in the indoor room.
  * 4. When the intensity reduces below the specified lower value and presence of a living being in the room then light should be turned on. Else light should be turned off.
