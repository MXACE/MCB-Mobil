# MCB-Mobil
A selfmade RC car with mecanuum wheels.


## Important Notes
The Software written for the STM microcontroller is for the [STM32Workbench](https://www.st.com/en/development-tools/sw4stm32.html) IDE.
The Software written for the Arduino is made in [Arduino](https://www.arduino.cc/en/software)

The controller is on version 2.0. The old files are not on this github. The documentation is about the version 1.0.
See "Controller Changelog" for more information.


## Controller Changelog
v2.0
- Added BMG250 Sensor
- Removed OLED Connector
- Added OLED Screen COM connector
- Changed Microcontroller from STM32F107VC to STM32F405RGT6
- Removed connection for Lora Breakout Board
- Added RN2483 Lora Module directly on PCB.
- Replaced 20pin JTAG conntector with 5 Pin SWD Connector and TagConnect Pads
- Removed onboard STLINK and it's USB Connector.
- Added Powerswitch between Battery and USB.


## Important Files:

Schematics of the Car, Controller and the Lora Breakoutboard can be found [here](-)

### Car:
- [PCB Files](https://github.com/MXACE/MCB-Mobil/tree/master/Chassis/CAD/v1.0/Chassisv1.0)
- [3D Printed Casing Parts (Scheinwerfer & Plexiglashalter)](https://github.com/MXACE/MCB-Mobil/tree/master/Chassis/3d%20modell/new_model/3dprint)
- [Software for STM32F107](https://github.com/MXACE/MCB-Mobil/tree/master/Chassis/SW)
- [Software for Arduino Nano](https://github.com/MXACE/MCB-Mobil/tree/master/Chassis/SW_ARD)
- [BOM](https://github.com/MXACE/MCB-Mobil/tree/master/Chassis/Assembly)

### Controller:
- [PCB Files]()
- [3D Printed Casing Parts](-)
- [Software for STM32F405](-)
- [BOM]()

### RN2483 Lora Breakout Module
- [PCB Files](https://github.com/MXACE/MCB-Mobil/tree/master/Funk/CAD/v1.0/PCB_Project)
- [3D Printed Casing Parts](-)
- [BOM](https://github.com/MXACE/MCB-Mobil/tree/master/Funk/Assembly)
