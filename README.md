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

The ESP32-CAM currently reports:

```text
E BOD: Brownout detector was triggered
The LED-only firmware works, while the Wi-Fi firmware causes repeated resets.

The LEDs were disconnected during testing and the issue remained.

The current investigation is focused on providing a stable 5 V power source capable of handling the ESP32-CAM's Wi-Fi current demand.

See docs/troubleshooting.md for details.

Learning Goals
This project is being developed to understand:

ESP32 GPIO control

Embedded C/C++

Wi-Fi communication

HTTP communication

Python

OpenCV

Real-time systems

PC-to-embedded communication

LED control

Audio/video signal processing

Project Status
🚧 Work in Progress

The GPIO LED controller is working.

The next milestone is reliable Wi-Fi operation followed by PC-based video analysis.
