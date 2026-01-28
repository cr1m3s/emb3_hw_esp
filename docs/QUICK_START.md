# Quick Start Guide

## First Time Setup

1. **Install PlatformIO in VSCode**
   - Open VSCode
   - Go to Extensions (Ctrl+Shift+X)
   - Search for "PlatformIO IDE"
   - Install it
   - Restart VSCode

2. **Clone/Initialize this repository**
   ```bash
   git init
   git add .
   git commit -m "Initial commit: embedded homework structure"
   ```

## Working on Exercises

### Option 1: Open individual exercise folders
1. File → Open Folder
2. Navigate to `exercises/01-blink/esp/` (or `stm32/`)
3. PlatformIO will detect the project automatically
4. Use the PlatformIO toolbar at the bottom to build/upload

### Option 2: Use VSCode Workspace (Recommended)
1. File → Add Folder to Workspace
2. Add multiple exercise folders you're working on
3. File → Save Workspace As → `my-homework.code-workspace`
4. Switch between projects using the PlatformIO Project Tasks panel

## Building Your First Exercise

```bash
# Navigate to the exercise
cd exercises/01-blink/esp/

# Build the project
pio run

# Upload to board (connect your board first!)
pio run --target upload

# Monitor serial output
pio device monitor

# Or do everything at once
pio run --target upload && pio device monitor
```

## Creating a New Exercise

```bash
# From repository root
mkdir -p exercises/02-your-exercise/{esp,stm32}
mkdir -p exercises/02-your-exercise/esp/src
mkdir -p exercises/02-your-exercise/stm32/src

# Copy platformio.ini from exercise 01
cp exercises/01-blink/esp/platformio.ini exercises/02-your-exercise/esp/
cp exercises/01-blink/stm32/platformio.ini exercises/02-your-exercise/stm32/

# Create your main.cpp files
touch exercises/02-your-exercise/esp/src/main.cpp
touch exercises/02-your-exercise/stm32/src/main.cpp
```

## Adding Shared Libraries

When you create reusable code:

1. **Platform-agnostic code** → `shared/common/`
2. **ESP-specific code** → `shared/esp/`
3. **STM32-specific code** → `shared/stm32/`

Example structure for a new shared library:
```
shared/common/my_library/
├── my_library.h
└── my_library.cpp  (if needed)
```

The library will be automatically available in all exercises due to `lib_extra_dirs` in platformio.ini.

## Troubleshooting

**PlatformIO doesn't detect my board:**
- Make sure the board is connected
- Check USB drivers are installed
- Try `pio device list` to see connected devices

**Build fails with "library not found":**
- Check that `lib_extra_dirs` paths in platformio.ini are correct
- Paths are relative to the platformio.ini file location

**Upload fails:**
- Verify correct COM port (check Device Manager on Windows)
- Ensure no other program is using the serial port
- Press reset button on board and try again

## Useful PlatformIO Commands

```bash
pio run                      # Build
pio run -t clean             # Clean build files
pio run -t upload            # Upload to board
pio device monitor           # Serial monitor
pio device list              # List connected devices
pio boards                   # List all supported boards
pio lib search <name>        # Search for libraries
```

## VSCode Tips

- Use Ctrl+Shift+P → "PlatformIO: Build" for quick access
- Bottom toolbar shows PlatformIO shortcuts
- Install "C/C++" extension for better IntelliSense
