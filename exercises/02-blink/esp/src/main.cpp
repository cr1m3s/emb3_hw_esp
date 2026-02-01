#include <Arduino.h>

#define LED_PIN 11
#define BOOT_BUTTON 0   // Built-in BOOT button (SLOW mode)
#define FAST_BUTTON 13  // External button (FAST mode)

// Beacon states
enum BeaconState {
  LEFT_ON_1,
  LEFT_OFF,
  LEFT_ON_2,
  PAUSE_MIDDLE,
  RIGHT_ON_1,
  RIGHT_OFF,
  RIGHT_ON_2,
  PAUSE_LONG
};

// Speed modes
enum SpeedMode {
  SLOW,    // BOOT button
  NORMAL,  // No button pressed
  FAST     // GPIO13 button
};

BeaconState currentState = LEFT_ON_1;
SpeedMode currentSpeed = NORMAL;

unsigned long stateStartTime = 0;
unsigned long stateDuration = 0;
unsigned long cycleCount = 0;  // Count complete cycles

// Button debouncing
unsigned long lastBootPress = 0;
unsigned long lastFastPress = 0;
const unsigned long DEBOUNCE_DELAY = 200;

int lastBootState = HIGH;
int lastFastState = HIGH;

void enterState(BeaconState newState) {
  currentState = newState;
  stateStartTime = millis();

  // Count cycles
  if (newState == LEFT_ON_1) {
    cycleCount++;
    Serial.print("[Cycle ");
    Serial.print(cycleCount);
    Serial.print("] Speed: ");
    switch(currentSpeed) {
      case SLOW:   Serial.print("SLOW  "); break;
      case NORMAL: Serial.print("NORMAL"); break;
      case FAST:   Serial.print("FAST  "); break;
    }
    Serial.println();
  }

  // Default: LED off
  digitalWrite(LED_PIN, LOW);

  // Base durations
  unsigned long baseDuration = 0;

  switch (currentState) {
    case LEFT_ON_1:
      digitalWrite(LED_PIN, HIGH);
      baseDuration = 80;
      break;

    case LEFT_OFF:
      baseDuration = 60;
      break;

    case LEFT_ON_2:
      digitalWrite(LED_PIN, HIGH);
      baseDuration = 80;
      break;

    case PAUSE_MIDDLE:
      baseDuration = 120;
      break;

    case RIGHT_ON_1:
      digitalWrite(LED_PIN, HIGH);
      baseDuration = 80;
      break;

    case RIGHT_OFF:
      baseDuration = 60;
      break;

    case RIGHT_ON_2:
      digitalWrite(LED_PIN, HIGH);
      baseDuration = 80;
      break;

    case PAUSE_LONG:
      baseDuration = 300;
      break;
  }

  // Apply speed multiplier
  float multiplier = 1.0;
  switch(currentSpeed) {
    case SLOW:   multiplier = 2.0;  break;  // 2x slower
    case NORMAL: multiplier = 1.0;  break;  // Normal
    case FAST:   multiplier = 0.5;  break;  // 2x faster
  }
  
  stateDuration = baseDuration * multiplier;
}

BeaconState nextState(BeaconState state) {
  switch (state) {
    case LEFT_ON_1:     return LEFT_OFF;
    case LEFT_OFF:      return LEFT_ON_2;
    case LEFT_ON_2:     return PAUSE_MIDDLE;
    case PAUSE_MIDDLE:  return RIGHT_ON_1;
    case RIGHT_ON_1:    return RIGHT_OFF;
    case RIGHT_OFF:     return RIGHT_ON_2;
    case RIGHT_ON_2:    return PAUSE_LONG;
    case PAUSE_LONG:    return LEFT_ON_1;
  }
  return LEFT_ON_1;
}

void checkBootButton() {
  unsigned long now = millis();
  int buttonState = digitalRead(BOOT_BUTTON);

  if (buttonState == LOW && lastBootState == HIGH) {
    if (now - lastBootPress > DEBOUNCE_DELAY) {
      lastBootPress = now;

      if (currentSpeed != SLOW) {
        currentSpeed = SLOW;
        Serial.println("🐌 SLOW mode activated (BOOT button)");
      } else {
        currentSpeed = NORMAL;
        Serial.println("⏸️  NORMAL mode (BOOT button released)");
      }
      
      enterState(currentState);
    }
  }

  lastBootState = buttonState;
}

void checkFastButton() {
  unsigned long now = millis();
  int buttonState = digitalRead(FAST_BUTTON);

  if (buttonState == LOW && lastFastState == HIGH) {
    if (now - lastFastPress > DEBOUNCE_DELAY) {
      lastFastPress = now;

      if (currentSpeed != FAST) {
        currentSpeed = FAST;
        Serial.println("🚀 FAST mode activated (GPIO13 button)");
      } else {
        currentSpeed = NORMAL;
        Serial.println("⏸️  NORMAL mode (GPIO13 button released)");
      }
      
      enterState(currentState);
    }
  }

  lastFastState = buttonState;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println();
  Serial.println("========================================");
  Serial.println("  ESP32-S3 Dual-Button Beacon");
  Serial.println("========================================");
  Serial.println("BOOT (GPIO0)  → SLOW mode (toggle)");
  Serial.println("GPIO13        → FAST mode (toggle)");
  Serial.println("========================================");
  Serial.println();

  pinMode(LED_PIN, OUTPUT);
  pinMode(BOOT_BUTTON, INPUT_PULLUP);
  pinMode(FAST_BUTTON, INPUT_PULLUP);

  Serial.println("✅ Beacon started in NORMAL mode");
  Serial.println();

  enterState(LEFT_ON_1);
}

void loop() {
  unsigned long now = millis();

  // Check both buttons
  checkBootButton();
  checkFastButton();

  // Update beacon state
  if (now - stateStartTime >= stateDuration) {
    enterState(nextState(currentState));
  }
}