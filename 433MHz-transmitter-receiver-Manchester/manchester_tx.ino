#include <Manchester.h>

/*
  Arduino IDE 1.8.19
  Core: ATTinyCore by Spencer Konde. http://drazzy.com/package_drazzy.com_index.json
  Board: ATtiny45/85 (Optiboot)
  Chip: ATtiny85
  Clock: 8MHz internal
  Manchester library: https://github.com/mchr3k/arduino-libs-manchester (placed into ./Arduino/libraries)
  Burn bootloader first, then load program.
  Programmer: USB ISP, (USBasp). Requires avr-gcc, avrdude. 
  Transmitter: FS1000A at 5V, range 100-150m.
  Antenna: 17.3cm straight wire.

  Speeds:
  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7
*/

// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2

#define TX_PIN 0
#define PIR_PIN 1
int16_t transmit_data = 32;

void setup() {
  delay(500);
  pinMode(PIR_PIN, INPUT);
  man.setupTransmit(TX_PIN, MAN_300);
} 

void loop() {
  int pir_state = digitalRead(PIR_PIN);
  if (pir_state == 1 ) {
      man.transmit(transmit_data);
  } 
  delay(1000);
}
