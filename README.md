# Attiny85

## 433MHz VirtualWire based transmitter and receiver
Arduino IDE 1.8.19  
Core: ATTinyCore by Spencer Konde. http://drazzy.com/package_drazzy.com_index.json  
Board: ATtiny45/85 Optiboot  
Chip: ATtiny85, does not work on ATTINY13A-PU (not enough memory).  
Clock: 8MHz internal.  
VirtualWire library: https://electronoobs.com/eng_arduino_virtualWire.php  
Burn bootloader first, then load program.  
Programmer: USB ISP, (USBasp). Requires avr-gcc, avrdude.  
Antenna: 17.3cm straight wire.  
Range: 10-20m in crowded space.  
Testable by connecting transmitter and receiver with a wire.

### Transmitter
Transmitter: FS1000A at 3.7V.

### Receiver
Receiver: RXB6 at 5V (Do not use the simple receiver with a coil, use one with a crystal).

## Manchester based transmitter and receiver
Arduino IDE 1.8.19  
Core: ATTinyCore by Spencer Konde. http://drazzy.com/package_drazzy.com_index.json  
Board: ATtiny45/85 (Optiboot)  
Chip: ATtiny85  
Clock: 8MHz internal  
Manchester library: https://github.com/mchr3k/arduino-libs-manchester (placed into ./Arduino/libraries)  
Burn bootloader first, then load program.  
Programmer: USB ISP, (USBasp). Requires avr-gcc, avrdude.  
Antenna: 17.3cm straight wire.  
Range: 100-150m in crowded space.  
Testable by connecting transmitter and receiver with a wire.  

### Transmitter
Transmitter: FS1000A at 5V. 

### Receiver:
Receiver: RXB6 at 5V (Do not use the simple receiver with a coil, use one with a crystal).

## Millis Blik
Simple LED blinking example using millis().

## Basic Blink
Simplest LED blinking example with delay().

## No-IDE-Blink
Simple blinking program without using Arduino IDE.

# Attiny13a

## Dot
Notification software that reacts to high voltage on the input pin.  
Compilation:  
avr-gcc -Wall -g -Os -mmcu=attiny13a -o dot.bin dot.c  
avr-objcopy -j .text -j .data -O ihex dot.bin dot.hex  
  
Flashing via USB ISP programmer:  
avrdude -c usbasp -p attiny13 -U flash:w:dot.hex  

## Libraries
Backup of libraries I used at the time of creating these programs.  
