# Setup Instructions

## What You Have

This repository is ready to use! Here's what's included:

```
embedded-homeworks/
├── README.md                    # Main documentation
├── .gitignore                   # Git ignore file
├── new_exercise.sh              # Script to create new exercises
├── shared/                      # Shared code libraries
│   ├── common/utilities/
│   │   └── debug.h             # Debug utilities (already works!)
│   ├── esp/                    # ESP-specific shared code (empty for now)
│   └── stm32/                  # STM32-specific shared code (empty for now)
├── exercises/
│   └── 01-blink/               # First exercise - LED blink
│       ├── README.md
│       ├── esp/
│       │   ├── platformio.ini
│       │   └── src/main.cpp
│       └── stm32/
│           ├── platformio.ini
│           └── src/main.cpp
└── docs/
    └── QUICK_START.md          # Detailed usage guide
```

## Next Steps

1. **Extract this archive to your working directory**
   ```bash
   tar -xzf embedded-homeworks.tar.gz
   cd embedded-homeworks
   ```

2. **Initialize Git**
   ```bash
   git init
   git add .
   git commit -m "Initial commit: embedded homework structure"
   ```

3. **Open in VSCode**
   - Open VSCode
   - File → Open Folder
   - Select `embedded-homeworks/exercises/01-blink/esp/` (or `stm32/`)
   - Or use File → Add Folder to Workspace to add both

4. **Test the Setup**
   ```bash
   cd exercises/01-blink/esp/
   pio run  # This will build the project
   ```

5. **Connect your board and upload**
   ```bash
   pio run --target upload
   pio device monitor
   ```

## Creating New Exercises

Use the included script:

```bash
./new_exercise.sh 02-uart
cd exercises/02-uart/esp/
# Edit src/main.cpp
pio run --target upload
```

## Configuration Notes

### ESP32-S3 DevKitC-1-N16R8V
- Board: `esp32-s3-devkitc-1`
- Built-in RGB LED on GPIO48
- 16MB Flash, 8MB PSRAM

### BlackPill F401CC Clone
- Board: `blackpill_f401cc`
- Built-in LED on PC13 (active LOW)
- STM32F401CC MCU

### LED Pin Configuration

The blink example uses:
- ESP32-S3: GPIO48 (RGB LED) - can change to GPIO2 for external LED
- BlackPill F401: PC13 (built-in LED)

Note: BlackPill LED is active LOW, so it lights up when the pin is set to LOW.

## Read the Documentation

- `README.md` - Overview of the repository
- `docs/QUICK_START.md` - Detailed PlatformIO usage guide
- `exercises/01-blink/README.md` - First exercise details

## Troubleshooting

**Q: PlatformIO doesn't recognize my board**
A: Check USB connection, install drivers, try `pio device list`

**Q: Build fails with library errors**
A: Make sure `lib_extra_dirs` paths are correct in platformio.ini

**Q: How do I add new shared libraries?**
A: Create files in `shared/common/`, they're automatically available

For more help, check `docs/QUICK_START.md`

## Happy Coding! 🚀
