# MP3 Player

## Description
This is a sample MP3 Player project to check the functionality of the MbedDFPLayer library.
It also shows an example of usage of the library.

## Using the library
to use only the library in your project, use `git clone https://github.com/fahidsh/mbed-mp3player`

## Using this project
to use this sample project as base and extend it with platformio, use `git clone https://github.com/fahidsh/mbed-mp3player-sample`, if you do, don't forget to check the `platformio.ini` file and update it according to your needs, especially the following:

```ini
; Firmware upload options
upload_port = E:
; Serial Monitor options
monitor_speed = 115200
monitor_port = COM10
```

## My setup
In this project, I used the following hardware:
- NUCLEO-L152RE
- Arduino Multifunction Shield (https://www.ebay.de/itm/233410022083)
- DFPlayer Mini MP3 Player

MF-Shield Buttons are set/used to control the MP3 Player.

DFPlayer Mini MP3 Player is connected to the following pins on my L152RE board:
- TX: PC_10
- RX: PC_11 (1k resister is used between L152RE-TX and DFPlayer-RX)
- VCC: 5V (support 3.3v to 5v, recommended 4.3v)
- GND: GND