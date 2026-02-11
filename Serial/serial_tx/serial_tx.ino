#include <SoftwareSerial.h>

// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2


#define RX_PIN 0
#define TX_PIN 1
#define BLINK_INTERVAL 1000


SoftwareSerial serial(RX_PIN, TX_PIN);

void setup() {             
  serial.begin(9600);
}

void loop() {                 
  serial.print('1');
  delay(BLINK_INTERVAL);
}
