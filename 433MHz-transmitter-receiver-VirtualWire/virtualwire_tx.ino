#include <VirtualWire.h>

// Arduino IDE 1.8.19
// Core: ATTinyCore by Spencer Konde. http://drazzy.com/package_drazzy.com_index.json
// Board: ATtiny45/85 Optiboot
// Chip: ATtiny85
// Clock: 8MHz internal
// VirtualWire: https://electronoobs.com/eng_arduino_virtualWire.php
// Does not work on ATTINY13A-PU (not enough memory).
// Burn bootloader first, then load program.
// Programmer: USB ISP, (USBasp). Requires avr-gcc, avrdude.
// Transmitter: FS1000A at 3.7V, range 10-20m.
// Antenna: 17.3cm straight wire.

// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2

#define PIR_PIN 1
#define TX_PIN 0
#define TX_SPEED 2000
#define COUNTER_TOP 1000

int pir_state = 0;
const char *brd = "1";

void wait(int multiplier) {
  for (int i = 0; i < multiplier; i++) {
    for (int i = 0; i < COUNTER_TOP; i++) {
    __asm__("nop\n\t");
    __asm__("nop\n\t");
    __asm__("nop\n\t");
    __asm__("nop\n\t");
    } 
  }
}

void setup() {
  pinMode(PIR_PIN, INPUT);  
  vw_set_tx_pin(TX_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(TX_SPEED); // Enabling this breaks the millis() and delay() because virtualwire uses timer0.
}

void loop() {
  pir_state = digitalRead(PIR_PIN);
  if (pir_state == 1 ) {
    vw_send((uint8_t *)brd, strlen(brd));
    vw_wait_tx();
    wait(800);
  }
}
