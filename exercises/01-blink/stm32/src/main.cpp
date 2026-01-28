#include <Arduino.h>
#include <utilities/debug.h>

// BlackPill F401 has built-in LED on PC13
#define LED_PIN PC13
#define BLINK_DELAY 1000  // milliseconds

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    
    DEBUG_PRINTLN("BlackPill F401 Blink Example");
    DEBUG_PRINTLN("Starting...");
}

void loop() {
    digitalWrite(LED_PIN, HIGH);
    DEBUG_PRINTLN("LED ON");
    delayMs(BLINK_DELAY);
    
    digitalWrite(LED_PIN, LOW);
    DEBUG_PRINTLN("LED OFF");
    delayMs(BLINK_DELAY);
}
