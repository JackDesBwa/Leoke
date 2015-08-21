--------------------------------------------------------------
| Léoké Arduino Addon (based on MakeyMakey sparkfun version) |
--------------------------------------------------------------

This Arduino addon for Léoké creates an Arduino Board menu option for Léoké.

-------------------------------------------------
|         Installing the Arduino Addon          |
-------------------------------------------------

To install this addon, add "Leoke" folder into a "hardware" folder withing your Arduino sketchbook. If you don't know where your sketchbook is located, you can find it's location by going to File > Preferences within Arduino.

For Windows XP users, the sketchbook is usually located in your "My Documents/Arduino" directory. So once installed, this readme should reside in "My Documents/Arduino/hardware/Leoke". Windows 7, by default, is something like: C:\Users\<user name>\Arduino\hardware\Leoke.

Once installed, close any Arduino windows and reopen. The following board should be listed in the Tools > Board menu now:
Léoké.

-------------------------------------------------
|     Installing the Drivers (Windows only)     |
-------------------------------------------------

Windows users will need to install drivers the first time you connect Léoké. Usually a New Hardware Wizard will pop up, you'll need to direct it to the included "Drivers" folder. The driver is "Leoke.inf".

The included driver should work for Léoké with the Sparkfun VID/PID: 0x1B4F/0x2B74 (bootloader) and 0x2B75 (sketch)).

-------------------------------------------------
|            What files are included?           |
-------------------------------------------------

This addon should work with no need to modify files. If you're curious what we've done to the default Arduino files though, read on...

* bootloaders/caterina: This is a slightly modified version of the Caterina bootloader, which is used in the Arduino Leonardo. Defines were modified so the VID and PID were set to SparkFun-specific values (VID: 0x1B4F, PIDs: 0xF100/F101 [get it?!]). To compile this, you'll need to download LUFA, and point the makefile to that directory.

To compile the bootloader for Léoké, you must first set F_CPU and PID near the top of the makefile. F_CPU should be 16000000. PID should be 2B74.

This directory also includes caterina-makeymakey.hex which is the compiled images of the MaKey MaKey's bootloader. It won't be deleted after running a 'make clean'.

* cores/arduino: This is a mostly unchanged listing of all the core files required by Léoké to compile under Arduino. The files with changes are:
	USBCore.cpp: added conditional statement for seting PLLCSR.
	
* variants/leoke: This is mostly identical to the Leonardo pins_arduino.h. RX and TX macros are adapted and Léoké specific names (L1, L2...) are defined.

* boards.txt: This file is what Arduino looks at when populating its Tools > Board menu.
The "Léoké" will be added to the Tools > Board menu.

This also defines a few variables such as clock frequency, USB VID and PID, fuses, and bootloader location.
