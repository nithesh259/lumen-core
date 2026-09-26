# Hardware Connections

## Components

* AI-Thinker ESP32-CAM
* 4 × Green LEDs
* 4 × 330 Ω resistors
* Breadboard
* FTDI USB-to-Serial programmer

## LED Connections

| LED   | ESP32-CAM GPIO | Resistor |
| ----- | -------------: | -------: |
| LED 1 |        GPIO 12 |    330 Ω |
| LED 2 |        GPIO 13 |    330 Ω |
| LED 3 |        GPIO 14 |    330 Ω |
| LED 4 |        GPIO 15 |    330 Ω |

Each LED is connected through its own 330 Ω resistor.

### LED polarity

* Long LED leg (anode) → resistor → ESP32 GPIO
* Short LED leg (cathode) → GND

## Current Status

The four LEDs have been successfully tested individually and together.

The LED hardware stage is working.
