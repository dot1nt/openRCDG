# openRCDG
An Arduino based rc drift gyro.

## Building
The easiest way to build and upload this project is to use the [platformio vscode extension](https://platformio.org/install/ide?install=vscode).

If you are building for a board other than the arduino micro, you will need to change/add the board in the platformio.ini file.

## Configuration
Configuration variables can be found in the config.h file.

## Hardware
I only tested this on an Arduino micro and nano, but it should work on most other boards as well.

Example schematic for an Arduino pro micro with GY-521 imu:

![schematic](https://github.com/dot1nt/openRCDG/blob/main/assets/schematic.PNG)

## PCB
Files for the pcb and case can be found in the pcb/case folders. The board works, but component placement/routing isn't optimal. The pcb uses components from a **3.3V** arduino pro micro and mpu6050 board. 3D printing the case works fine. 

![1](https://github.com/dot1nt/openRCDG/blob/main/assets/1.PNG)
![2](https://github.com/dot1nt/openRCDG/blob/main/assets/2.PNG)
![3](https://github.com/dot1nt/openRCDG/blob/main/assets/3.PNG)
