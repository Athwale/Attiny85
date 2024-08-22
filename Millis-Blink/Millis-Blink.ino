// PHY pin 2 -> SW Pin 3
// PHY pin 3 -> SW Pin 4
// PHY pin 5 -> SW Pin 0
// PHY pin 6 -> SW Pin 1
// PHY pin 7 -> SW Pin 2

#define LED_PIN 1
#define BLINK_INTERVAL 1000

unsigned long previousMillis = 0;
bool ledState = LOW;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= BLINK_INTERVAL) {
    previousMillis = currentMillis;  

    ledState = !ledState;            
    digitalWrite(LED_PIN, ledState);
  }
}
