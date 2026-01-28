# Board Reference Guide

Quick reference for your specific development boards.

## ESP32-S3 DevKitC-1-N16R8V

### Specifications
- **MCU**: ESP32-S3-WROOM-1-N16R8V
- **Flash**: 16MB
- **PSRAM**: 8MB
- **USB**: Native USB support (USB OTG)
- **WiFi**: 2.4 GHz 802.11 b/g/n
- **Bluetooth**: Bluetooth 5 (LE)

### Important Pins
- **Built-in RGB LED**: GPIO48 (WS2812)
- **Boot Button**: GPIO0
- **USB Serial**: Built-in (no need for external USB-to-Serial)
- **I2C (default)**: SDA=GPIO8, SCL=GPIO9
- **SPI (default)**: MOSI=GPIO11, MISO=GPIO13, SCK=GPIO12
- **UART**: TX=GPIO43, RX=GPIO44

### Notes
- The RGB LED on GPIO48 requires WS2812/Neopixel library for full control
- For simple blink, GPIO48 works but only controls one color
- Recommended to use GPIO2 with external LED for learning basics
- Native USB means you can use it as USB device (HID, MIDI, etc.)

### PlatformIO Board ID
```ini
board = esp32-s3-devkitc-1
```

---

## BlackPill F401CC Clone

### Specifications
- **MCU**: STM32F401CCU6
- **Flash**: 256KB
- **RAM**: 64KB
- **Clock**: 84 MHz (ARM Cortex-M4)
- **USB**: USB 2.0 full-speed device
- **FPU**: Yes (hardware floating point)

### Important Pins
- **Built-in LED**: PC13 (⚠️ Active LOW - lights when pin is LOW)
- **Boot0 Button**: Controls boot mode
- **User Button**: PA0 (if available on your clone)
- **I2C1**: SDA=PB7, SCL=PB6
- **I2C2**: SDA=PB3, SCL=PB10
- **SPI1**: MOSI=PA7, MISO=PA6, SCK=PA5
- **UART1**: TX=PA9, RX=PA10
- **USB**: PA11 (D-), PA12 (D+)

### Pin Voltage
⚠️ **WARNING**: Most pins are **3.3V ONLY**! Do not connect 5V directly to GPIO pins.
- Only 5V tolerant pins: PA9, PA10, PB6, PB7

### Notes
- LED on PC13 is active LOW (write `LOW` to turn on, `HIGH` to turn off)
- Some clones may have different LED pin - check your board
- USB can be used for both programming and as USB device
- Has hardware floating point unit (FPU) - good for math-heavy tasks

### PlatformIO Board ID
```ini
board = blackpill_f401cc
```

### Upload Methods
1. **DFU mode** (recommended for first time):
   - Hold BOOT0 button
   - Press and release RESET
   - Release BOOT0
   - Upload using DFU

2. **Serial bootloader**:
   - Connect USB-to-Serial adapter
   - Set BOOT0 to 1
   - Reset and upload

3. **ST-Link** (if you have one):
   - Connect ST-Link debugger
   - Direct upload and debugging

---

## Common Gotchas

### ESP32-S3
- ❌ Don't use GPIO26-32 (reserved for flash/PSRAM)
- ❌ Don't use GPIO19-20 (USB)
- ✅ GPIO1-18, GPIO21, GPIO35-48 are safe for general use
- The RGB LED needs special library, use GPIO2 for basic blink

### BlackPill F401
- ❌ Don't apply 5V to regular GPIO (only to 5V tolerant pins)
- ❌ LED on PC13 is inverted (LOW = on, HIGH = off)
- ✅ Remember to configure BOOT0 correctly for uploading
- If upload fails, try DFU mode

---

## Quick Pin Reference

### ESP32-S3 Safe GPIOs for Beginners
Good general-purpose pins: 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 21

### BlackPill F401 Safe 3.3V GPIOs
Good general-purpose pins: PA0-PA8, PB0-PB2, PB12-PB15, PC13-PC15

---

## Useful Resources

### ESP32-S3
- [ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
- [DevKitC-1 Schematic](https://dl.espressif.com/dl/schematics/SCH_ESP32-S3-DEVKITC-1_V1_20210312.pdf)

### BlackPill F401
- [STM32F401 Reference Manual](https://www.st.com/resource/en/reference_manual/dm00096844-stm32f401xb-c-and-stm32f401xd-e-advanced-arm-based-32-bit-mcus-stmicroelectronics.pdf)
- [Pinout Diagram](https://github.com/WeActTC/MiniSTM32F4x1)

---

## Testing Your Boards

### First Test - ESP32-S3
```cpp
// Use GPIO2 with external LED for reliable testing
#define LED_PIN 2
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, HIGH); // LED on
```

### First Test - BlackPill F401
```cpp
// Built-in LED test (remember: active LOW!)
#define LED_PIN PC13
pinMode(LED_PIN, OUTPUT);
digitalWrite(LED_PIN, LOW);  // LED on
digitalWrite(LED_PIN, HIGH); // LED off
```
