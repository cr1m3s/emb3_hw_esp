#include <Arduino.h>

#define LED_LEFT     4
#define LED_RIGHT    5

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

BeaconState currentState = LEFT_ON_1;

// ====== Таймінг ======
unsigned long stateStartTime = 0;

// ====== Тривалості станів (мс) ======
unsigned long stateDuration = 0;

// ====== Функція: що робити при вході в стан ======
void enterState(BeaconState newState) {
  currentState = newState;
  stateStartTime = millis();   // запам’ятали момент входу

  // За замовчуванням — все вимкнено
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RIGHT, LOW);

  switch (currentState) {

    case LEFT_ON_1:
      digitalWrite(LED_LEFT, HIGH);
      stateDuration = 80;
      break;

    case LEFT_OFF:
      stateDuration = 60;
      break;

    case LEFT_ON_2:
      digitalWrite(LED_LEFT, HIGH);
      stateDuration = 80;
      break;

    case PAUSE_MIDDLE:
      stateDuration = 120;
      break;

    case RIGHT_ON_1:
      digitalWrite(LED_RIGHT, HIGH);
      stateDuration = 80;
      break;

    case RIGHT_OFF:
      stateDuration = 60;
      break;

    case RIGHT_ON_2:
      digitalWrite(LED_RIGHT, HIGH);
      stateDuration = 80;
      break;

    case PAUSE_LONG:
      stateDuration = 300;
      break;
  }
}

// ====== Функція: який наступний стан ======
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
  return LEFT_ON_1; // запасний варіант
}

// ====== setup ======
void setup() {
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  enterState(LEFT_ON_1); // стартовий стан
}

// ====== loop ======
void loop() {
  unsigned long now = millis();

  // Перевірка: чи час міняти стан
  if (now - stateStartTime >= stateDuration) {
    enterState(nextState(currentState));
  }
}