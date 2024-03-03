# Virtual Trackpad

## Description

VirtualTrackpad create a simple Trackpad UI \
that emit mouse events over serialport to a microcontroller \
that acts a Bluetooth mouse to control a remote device.

## Build from Source

### Prerequisites
- QT 5.15.2 or later
- CMake 3.19 or later
- A C++17 compiler

### Build
```bash
    qmake TrackPadApp.pro
    make
```

TODO:
- Complete the README
- Tests
- Refresh serialPort
- Windows support
- Linux support
