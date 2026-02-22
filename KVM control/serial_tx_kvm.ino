#include <SoftwareSerial.h>

// PHY pin 2 -> SW Pin 3 - input
// PHY pin 3 -> SW Pin 4 - TX
// PHY pin 5 -> SW Pin 0 - input
// PHY pin 6 -> SW Pin 1 - input
// PHY pin 7 -> SW Pin 2 - input
// PHY pin 1 -> SW Pin 5 - RX not used


#define RX_PIN 5
#define TX_PIN 4
#define IN_1 3
#define IN_2 0
#define IN_3 1
#define IN_4 2

SoftwareSerial serial(RX_PIN, TX_PIN);

void setup() {             
  serial.begin(9600);
  pinMode(IN_1, INPUT);
  pinMode(IN_2, INPUT);
  pinMode(IN_3, INPUT);
  pinMode(IN_4, INPUT);
}

void loop() {                 
  if (digitalRead(IN_1) == 1) {
    serial.print("PS11R\n");
    delay(200);    
  } else if (digitalRead(IN_2) == 1) {
    serial.print("PS12R\n"); 
    delay(200);   
  } else if (digitalRead(IN_3) == 1) {
    serial.print("PS13R\n");  
    delay(200);  
  } else if (digitalRead(IN_4) == 1) {
    serial.print("PS14R\n");
    delay(200);  
  } 
}
