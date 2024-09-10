#!/bin/bash

echo "Compiling..."
avr-gcc -Wall -g -Os -mmcu=attiny85 -o blink.bin blink.c
if [ $? -eq 0 ]; then
    avr-objcopy -j .text -j .data -O ihex blink.bin blink.hex
    echo "Done"
    echo "Flashing:"
    avrdude -c usbasp -p attiny85 -U flash:w:blink.hex
else
    echo "error"
fi
