#ifndef DEBUG_H
#define DEBUG_H

// Simple debug utilities that work across platforms

#ifdef DEBUG_ENABLED
    #define DEBUG_PRINT(x) Serial.print(x)
    #define DEBUG_PRINTLN(x) Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTLN(x)
#endif

// Simple delay wrapper (milliseconds)
inline void delayMs(unsigned long ms) {
    delay(ms);
}

// Map function for float values
inline float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif // DEBUG_H
