# ESP32 Project with ESP-IDF 5.4

This project is developed using ESP-IDF version 5.4 for the ESP32 microcontroller.

---

## Table of Contents

- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Installing ESP-IDF 5.4](#installing-esp-idf-54)
- [Setting up the Project](#setting-up-the-project)
- [Building the Project](#building-the-project)
- [Flashing the Firmware](#flashing-the-firmware)
- [Monitoring the Serial Output](#monitoring-the-serial-output)
- [Configuring the Project (menuconfig)](#configuring-the-project-menuconfig)
- [Troubleshooting](#troubleshooting)
- [References](#references)

---

## Introduction

This project demonstrates how to use ESP-IDF 5.4 to develop firmware for the ESP32 microcontroller. ESP-IDF (Espressif IoT Development Framework) is the official development framework for the ESP32 chip.

---

## Prerequisites

Before you start, ensure you have the following installed:

- Supported operating system:
  - Windows 10 or later
  - Linux (Ubuntu 18.04 or later recommended)
  - macOS 10.14 or later

- Python 3.8+ (used by ESP-IDF tools)

- Git

- USB driver for ESP32 (for Windows users):
  - [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)

- Required tools and libraries (will be installed via ESP-IDF installer)

---

## Installing ESP-IDF 5.4

ESP-IDF provides an all-in-one installer and a manual install method.

### Method 1: Using ESP-IDF Tools Installer (Recommended)

- Go to the official ESP-IDF download page:

  [https://docs.espressif.com/projects/esp-idf/en/v5.4/esp32/get-started/index.html](https://docs.espressif.com/projects/esp-idf/en/v5.4/esp32/get-started/index.html)

- Download the installer for your OS:
  - Windows: `esp-idf-tools-setup-x.y.z.exe`
  - Linux/macOS: Follow the instructions to use the install script

- Run the installer and follow the prompts.
- The installer will download ESP-IDF v5.4, Python, Git, and required tools.

### Method 2: Manual Installation

If you prefer manual installation, follow these steps:

```bash
# Clone ESP-IDF repo
git clone -b v5.4 --recursive https://github.com/espressif/esp-idf.git

# Enter directory
cd esp-idf

# Install prerequisites
./install.sh   # For Linux/macOS
install.bat    # For Windows (run in cmd)

# Set up environment variables (every new terminal)
. ./export.sh  # Linux/macOS
export.bat    # Windows
```

For detailed instructions, see [ESP-IDF Get Started](https://docs.espressif.com/projects/esp-idf/en/v5.4/esp32/get-started/index.html).

---

## Setting up the Project

Clone or download this project repository.

Navigate to the project folder in your terminal.

Before building, set the ESP-IDF environment:

```bash
# Linux/macOS
. $HOME/esp/esp-idf/export.sh

# Windows (PowerShell)
C:\esp\esp-idf\export.ps1
```

Adjust the path to where you installed ESP-IDF.

---

## Building the Project

Build the firmware using the following command:

```bash
idf.py build
```

This compiles the source code and generates the firmware binary.

---

## Flashing the Firmware to ESP32

Connect your ESP32 board to the computer via USB.

Identify the serial port:

- Linux/macOS: Usually `/dev/ttyUSB0` or `/dev/tty.SLAB_USBtoUART`
- Windows: Usually `COM3`, `COM4`, etc.

Flash the firmware:

```bash
idf.py -p PORT flash
```

Replace `PORT` with your serial port identifier.

Example:

```bash
idf.py -p /dev/ttyUSB0 flash
```

---

## Monitoring the Serial Output

After flashing, you can monitor the ESP32 serial output with:

```bash
idf.py -p PORT monitor
```

To exit the monitor, press `Ctrl+]`.

---

## Configuring the Project (menuconfig)

To customize project settings, run:

```bash
idf.py menuconfig
```

This opens a terminal-based configuration menu where you can:

- Set Wi-Fi credentials
- Configure peripherals (GPIO, UART, etc.)
- Adjust build options
- Enable/disable components and features

Navigate using arrow keys, select with Enter, and save your changes before exiting.

---

## Troubleshooting

- **ESP-IDF commands not found?**  
  Make sure you have run the export script for your terminal session.

- **Serial port not detected?**  
  Check drivers and cable connection. Use a known working USB cable.

- **Build errors?**  
  Verify ESP-IDF version is 5.4 and dependencies are installed correctly.

---

## References

- [ESP-IDF Official Documentation v5.4](https://docs.espressif.com/projects/esp-idf/en/v5.4/)
- [ESP32 Get Started Guide](https://docs.espressif.com/projects/esp-idf/en/v5.4/esp32/get-started/)
- [ESP-IDF GitHub Repository](https://github.com/espressif/esp-idf)

---

*This README was generated to help you get started with ESP32 development using ESP-IDF 5.4.*
