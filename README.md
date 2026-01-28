# Embedded Development Homeworks

Repository for embedded systems exercises using ESP32-S3 and STM32 BlackPill F401 platforms.

## Hardware

- **ESP32**: ESP32-S3 DevKitC-1-N16R8V
- **STM32**: BlackPill F401CC clone

## Structure

- `shared/` - Reusable code across exercises
  - `common/` - Platform-agnostic utilities
  - `esp/` - ESP-specific shared code
  - `stm32/` - STM32-specific shared code
- `exercises/` - Individual homework assignments
- `docs/` - Documentation and notes

## Setup

1. Install [PlatformIO](https://platformio.org/install)
2. Clone this repository
3. Navigate to an exercise folder (e.g., `exercises/01-blink/esp/`)
4. Run `pio run` to build
5. Run `pio run --target upload` to flash

## Exercises

- 01-blink - Basic GPIO control (LED blinking)

