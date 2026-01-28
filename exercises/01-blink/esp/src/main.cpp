#include <Arduino.h>

#define LED_PIN 4  // Change to 2 if using external LED
#define BLINK_DELAY 1000  // milliseconds

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    delay(BLINK_DELAY);
    
    digitalWrite(LED_PIN, LOW);
    delay(BLINK_DELAY);
}
