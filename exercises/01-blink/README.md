# Exercise 01 - Blink

Basic GPIO control exercise - blinking an LED.

## Objective

Learn to:
- Configure GPIO pins as output
- Control digital output states
- Use basic timing functions
- Use shared utility libraries

## Hardware Requirements

### ESP32-S3
- ESP32-S3 DevKitC-1-N16R8V
- Built-in RGB LED (GPIO48) or external LED + 220Ω resistor on GPIO2

### STM32
- BlackPill F401CC clone
- Built-in LED on PC13

## Building and Flashing

### ESP32
```bash
cd esp/
pio run                    # Build
pio run --target upload    # Flash
pio device monitor         # View serial output
```

### STM32
```bash
cd stm32/
pio run                    # Build
pio run --target upload    # Flash
pio device monitor         # View serial output
```

## Code Structure

Both implementations use the shared `utilities/debug.h` library for debug output and timing utilities, demonstrating code reuse across platforms.

## Notes

- **ESP32-S3**: Uses GPIO48 for built-in RGB LED. Change to GPIO2 if using external LED.
- **BlackPill F401**: Uses PC13 for built-in LED (active LOW - LED is ON when pin is LOW)
- Debug messages are enabled via `-DDEBUG_ENABLED` flag in platformio.ini
- Remove the build flag to disable debug output and reduce code size
