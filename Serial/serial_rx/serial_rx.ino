#include <SoftwareSerial.h>

// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2


#define RX_PIN 0
#define TX_PIN 1
#define LED_PIN 2
#define BLINK_INTERVAL 1000


SoftwareSerial serial(RX_PIN, TX_PIN);
char received = '\0';

void setup() {             
  serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {                 
  if (serial.available() > 0) {       
    received = serial.read();
    if (received == '1') {
      digitalWrite(LED_PIN, HIGH);
      delay(BLINK_INTERVAL);
      digitalWrite(LED_PIN, LOW);
      delay(BLINK_INTERVAL);
      received = '0';
    }
  }
}
