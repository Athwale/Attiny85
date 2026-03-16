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

// PHY pin 5 -> SW Pin 0 - radio transmitter
// PHY pin 6 -> SW Pin 1 - radar sensor
// PHY pin 7 -> SW Pin 2 - pir sensor
// PHY pin 2 -> SW Pin 3 - self reset
// PHY pin 3 -> SW Pin 4 - status LED 

#define TX_PIN 0
#define RADAR_PIN 1
#define PIR_PIN 2
#define RESET_PIN 3
#define LED_PIN 4
#define BLINK_INTERVAL 300

int16_t transmit_pir = 32;
int16_t transmit_rad = 42;
int16_t transmit_both = 52;

int radar_state = 0;
int pir_state = 0;

void setup() {
  delay(500);
  pinMode(RADAR_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  //todo does not work.
  pinMode(RESET_PIN, OUTPUT);
  digitalWrite(RESET_PIN, HIGH);
  
  pinMode(LED_PIN, OUTPUT);
  // Sets it's pin as output on it's own.
  man.setupTransmit(TX_PIN, MAN_300);

  // Blink status led on boot finish.
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_INTERVAL);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_INTERVAL);
} 

void loop() {
  radar_state = digitalRead(RADAR_PIN);
  pir_state = digitalRead(PIR_PIN);

  if (pir_state == 1 && radar_state == 1 ) {
      man.transmit(transmit_both);
  } else if (radar_state = 0 && pir_state == 1 ) {
      man.transmit(transmit_pir);
  } else if (pir_state = 0  && radar_state == 1) {
      man.transmit(transmit_rad);
  } 
  delay(1000);
}
