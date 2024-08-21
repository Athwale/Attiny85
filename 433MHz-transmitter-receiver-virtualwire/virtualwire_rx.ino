#include <VirtualWire.h>

// Arduino IDE 1.8.19
// Core: ATTinyCore by Spencer Konde. http://drazzy.com/package_drazzy.com_index.json
// Board: ATtiny45/85 (Optiboot)
// Chip: ATtiny85
// Clock: 8MHz internal
// VirtualWire: https://electronoobs.com/eng_arduino_virtualWire.php
// Does not work on ATTINY13A-PU (not enough memory).
// Burn bootloader first, then load program.
// Programmer: USB ISP, (USBasp). Requires avr-gcc, avrdude. 
// Receiver: RXB6 at 5V (Do not use the simple receiver with a coil, use one with a crystal).
// Antenna: 17.3cm straight wire.

// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2

#define OUT_PIN 1
#define RX_PIN 0
#define TX_SPEED 2000
#define COUNTER_TOP 1000

uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;

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
  pinMode(OUT_PIN, OUTPUT);
  digitalWrite(OUT_PIN, LOW); 
  vw_set_rx_pin(RX_PIN);
  vw_set_ptt_inverted(true);
  vw_setup(TX_SPEED);
  vw_rx_start();
}

void loop() {
  // Waits until a message is received.
  vw_wait_rx_max(1000);
  if (vw_get_message(buf, &buflen)) { 
    if (strcmp((char *)buf, "1") == 0) {
      // Send 1 to output, message is OK.
      digitalWrite(OUT_PIN, HIGH);
      wait(200);    
      digitalWrite(OUT_PIN, LOW);
      wait(100);
    }
  }
}
