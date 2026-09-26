Here is your updated documentation formatted directly in raw Markdown code so you can easily copy and paste it into your README.md:

Markdown
# Real-Time Visual Lighting Control System

An ESP32-CAM based lighting project designed to synchronize physical LEDs with video and audio playing on a PC.

The long-term goal is to create a DIY DJ-style ambient lighting system where the lighting responds to the content displayed on the computer.

## Project Idea

PC Video / Audio
│
▼
Python Controller
│
│ Wi-Fi
▼
ESP32-CAM
│
▼
LED Lighting


For example, when a video contains a strong red scene, the system will eventually detect the dominant color and generate a corresponding lighting effect.

## Current Hardware

* **Controller:** AI-Thinker ESP32-CAM
* **LEDs:** 4 × Green LEDs
* **Resistors:** 4 × 330 Ω resistors
* **Breadboard**
* **Programmer:** FTDI USB-to-Serial programmer

### Current LED Configuration

| LED | GPIO |
| :--- | :--- |
| LED 1 | GPIO 12 |
| LED 2 | GPIO 13 |
| LED 3 | GPIO 14 |
| LED 4 | GPIO 15 |

> **Note:** Each LED uses a 330 Ω current-limiting resistor.

## Development Progress

### Stage 1 — GPIO LED Controller
* **Status:** Completed
* The ESP32-CAM successfully controls four individual LEDs.
* The LEDs were tested individually and together.

### Stage 2 — Wi-Fi LED Control
* **Status:** In Progress
* **Planned architecture:**
PC ──> Wi-Fi ──> ESP32-CAM ──> 4 LEDs

* A web-server firmware was developed to allow commands such as:
* `/led1/on`
* `/led1/off`
* `/led2/on`
* `/led2/off`
* *Current Issue:* The ESP32-CAM experiences a brownout reset when Wi-Fi starts.

### Stage 3 — PC Video Analysis
* **Status:** Planned
* Python and OpenCV will be used to analyze the video displayed on the PC.
* **Planned pipeline:**
Video Frame ──> Frame Processing ──> Dominant Color Detection ──> Lighting Command   


### Stage 4 — Smart DJ Effects
* **Status:** Planned
* Future effects include:
* Color transitions
* Brightness effects
* Flash effects
* Beat synchronization
* Multiple lighting patterns
* Audio-reactive lighting

## Important Debugging Issue

# Troubleshooting: Wi-Fi Brownout Hardware Exceptions

## 🚨 Symptom & Error Log
When initializing the Wi-Fi stack during Stage 2 firmware execution, the MCU encounters a hardware exception and drops into an infinite boot loop. The UART serial monitor outputs the following trace:

```log
E BOD: Brownout detector was triggered
```

### Context & Current State
* **Isolation Test:** The issue persists even when all 4 physical LEDs and current-limiting resistors are entirely disconnected from the GPIO pins.
* **Baseline Test:** Bare-metal GPIO toggling sketches (Stage 1) execute indefinitely without errors. The crash is triggered exclusively by the high transient current draw of the Wi-Fi radio.

---

## 🔍 Root Cause Analysis

1. **FTDI Current Constraints:** Standard USB-to-Serial FTDI programmers typically limit current output to **50mA–100mA** on their power lines. While sufficient for standard logic operations, it is completely inadequate for the high-power demand of the ESP32-CAM radio.
2. **Wi-Fi Transient Spikes:** The moment the Wi-Fi stack initiates radio calibration and transmission, current consumption abruptly spikes up to **500mA+**. This sudden load causes the voltage rail to drop below the chip's internal operating threshold, forcing the Brownout Detector (BOD) to reset the system to protect flash memory from corruption.
3. **Board Topography:** Generic AI-Thinker ESP32-CAM development boards feature minimal onboard decoupling capacitance, leaving them highly sensitive to transient supply voltage drops.

---

## 🛠️ Hardware Resolutions (Permanent Fixes)

### 1. Dedicated External Power Supply
Bypass the FTDI programmer's power delivery system completely by introducing a robust external power rail.

* **Action:** Connect an external regulated **5V DC power supply rated for at least 1A to 2A** directly to the `5V` and `GND` pins of the ESP32-CAM.
* **Crucial Ground Loop Prevention:** You **must** bridge the Ground (`GND`) pin of the external power supply to the Ground (`GND`) pin of your FTDI serial adapter. Without a shared common ground reference, serial data transmission (TX/RX) will fail or become corrupted.

### 2. High-Capacity Local Decoupling
To buffer the sudden electrical demands of the radio transceiver, introduce a local energy reservoir.

* **Action:** Install a **10µF to 100µF electrolytic capacitor** directly across the `5V` and `GND` rail on your prototyping breadboard.
* **Placement:** Keep the capacitor leads as physically close to the ESP32-CAM module pins as possible to minimize inductive line resistance.

---

## 💻 Software Mitigation Strategies (Temporary Workarounds)

If you are awaiting hardware components, you can temporarily modify your C/C++ firmware configurations to dampen or ignore the current spike. 

> ⚠️ **Warning:** Software workarounds do not fix the physical power bottleneck. Disabling protection circuits can result in unstable execution or file-system corruption if the voltage sags too low.

### Configuration A: Attenuate Wi-Fi Transmit Power
Reducing the Radio Frequency (RF) output power directly clamps the peak transient current. Place this inside your `setup()` block immediately after your initialization calls:

```cpp
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    
    // Initialize Wi-Fi
    WiFi.begin("YOUR_SSID", "YOUR_PASSWORD");
    
    // Attenuate TX power to a lower threshold to reduce peak current draw.
    // Available profiles: WIFI_POWER_19_5dBm (Default), 17dBm, 15dBm, 13dBm, 11dBm, 8_5dBm
    WiFi.setTxPower(WIFI_POWER_11dBm); 
}
```

### Configuration B: Bypass Hardware Brownout Thresholds
You can forcefully clear the hardware register responsible for tracking under-voltage drops via bare-metal configuration calls.

```cpp
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void setup() {
    // Forcefully disable the hardware brownout detection register at early boot
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
    
    Serial.begin(115200);
    // Proceed to high-current Wi-Fi initialization operations...
}
```
