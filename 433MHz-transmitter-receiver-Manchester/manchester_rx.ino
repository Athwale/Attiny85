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
  Receiver: RXB6 at 5V (Do not use the simple receiver with a coil, use one with a crystal).
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

#define RX_PIN 0
#define OUT_PIN 1
#define MSG 32
int16_t msg = 0;

void setup() {
  delay(500);
  pinMode(OUT_PIN, OUTPUT);
  man.setupReceive(RX_PIN, MAN_300);
  man.beginReceive();
}

void loop() {
  if (man.receiveComplete()) {
    msg = man.getMessage();
    if (msg == MSG) {
      digitalWrite(OUT_PIN, HIGH);
      delay(200);
      digitalWrite(OUT_PIN, LOW);
      delay(200);
    }
    man.beginReceive(); 
  }
}
