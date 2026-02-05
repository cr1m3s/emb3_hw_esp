#include <Arduino.h>

#define BUTTON_PIN 4
#define DEBOUNCE_MS 90  

volatile int16_t bounce_counter = 0;
volatile int16_t debounce_counter = 0;
volatile uint32_t lastBounce = 0;
volatile bool button_event = false;

void IRAM_ATTR reaction_button() {
  uint32_t now = millis();
  bounce_counter++;

  if (now - lastBounce > DEBOUNCE_MS) {
    debounce_counter++;
    lastBounce = now;
    button_event = true;
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  
  Serial.println("\n========================================");
  Serial.println("  Button Debounce Test");
  Serial.println("========================================");
  Serial.println("Press button and watch counters...\n");
  
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), reaction_button, FALLING);
}

void loop() {
  if (button_event) {
    button_event = false;
    
    Serial.print("Bounce: ");
    Serial.print(bounce_counter);
    Serial.print(" \tDebounced: ");
    Serial.print(debounce_counter);
    Serial.print(" \tRatio: ");
    Serial.print((float)bounce_counter / debounce_counter, 2);
    Serial.println("x");
  }
  
  delay(10);
}