CS 101 : 2014 - 2015
Team Number :	394
Team Members :	140070038 - Dipti Ranjan Sahu (Group Leader)
			140040113 - Abhay Vikram
			140070048 - Surya Teja
			14D170003 - Rohan B.Vora

Project Title:	TurtleSim Robot

Software Required:

1.Atmel Studio 6 - to compile and create the hex file to load on the FIREBIRD. Link: http://www.atmel.com/System/BaseForm.aspx?target=tcm:26-65530
2.AVR Bootloader - to bootload the hex file on the FIREBIRD. Link: http://www.nex-robotics.com/images/downloads/M2560_FBV_14MHz_115200_UART2_PE7.zip
3.Simplecpp Codeblocks - to give instructions by reading the program.txt file and transmitting it via XBee. Link: http://www.cse.iitb.ac.in/~ranade/simplecpp/CB-Simplecpp-setup.exe
4.X-CTU - to configure the two wireless XBee transmitters. Link: http://ftp1.digi.com/support/utilities/40003026_B.exe

Accessories Required:

1. Firebird V Atmega2560 Bot
2. Servo Motor
3. XBee Wireless module

Installation Instructions:

1. 1. Download AVR Bootloader. Link: http://www.nex-robotics.com/resources/avr-bootloader.html and install it
2. Download .zip file from github.com and extract the folder on the desktop.
3. This folder contains 3 subfolders viz. presentation, report and source.
4.source folder contains two subfolders viz. TurtleSim Robot(Atmel Studio code)and Simplecpp code(simplepp C++ code).
5. Configure the XBee transmitters by using X-CTU. Refer to link: http://youtu.be/mnUAcpKo-sA
6. Open \source\TurtleSim Bot\TurtleSim Bot.atsln in Atmel Studio and Build the code.
7. Burn \source\TurtleSim Bot\TurtleSim Bot\Debug\TurtleSim Bot.hex Code into the Bot With AVR bootloader.
8. Open \source\Simplecpp Code\program.txt and write your program which you want to run on Bot in real time.
9. Open \source\Simplecpp Code\TurtleSim_Robot.cpp SET the COM port as the same as the XBee COM port in the 9th line and build and run the program.

Youtube Video Links: (For Reference)

1. https://youtu.be/U_PFMgSixfY
2. http://youtu.be/mnUAcpKo-sA