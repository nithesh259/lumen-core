# Architecture

## Current Architecture

The first stage is a simple GPIO-based lighting controller.

```text
ESP32-CAM
    │
    ├── GPIO12 → LED 1
    ├── GPIO13 → LED 2
    ├── GPIO14 → LED 3
    └── GPIO15 → LED 4
```

## Planned Architecture

The final system is planned as:

```text
PC
 │
 │ Video / Audio
 ▼
Python Controller
 │
 ├── Screen Color Analysis
 ├── Brightness Analysis
 └── Beat / Audio Analysis
 │
 │ Wi-Fi
 ▼
ESP32-CAM
 │
 ▼
LED Controller
 │
 ├── LED Zone 1
 ├── LED Zone 2
 ├── LED Zone 3
 └── LED Zone 4
```

## Planned Features

* Screen color detection
* Video-reactive lighting
* Brightness-based effects
* Smooth color transitions
* Beat-reactive effects
* Multiple lighting patterns
* PC-to-ESP32 communication

## Current Development Stage

The four-LED GPIO controller has been successfully tested.

The Wi-Fi communication stage is currently blocked by an ESP32-CAM brownout issue.
