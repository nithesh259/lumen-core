# Troubleshooting and Debugging

## ESP32-CAM Brownout

### Error

During Wi-Fi initialization, the ESP32-CAM repeatedly produced:

```text
E BOD: Brownout detector was triggered
```

The board repeatedly restarted after booting.

### Observed Behavior

The basic LED test worked correctly.

However, when the Wi-Fi firmware was uploaded, the board began restarting with the brownout message.

The LEDs were then disconnected and the Wi-Fi test was performed again. The brownout still occurred.

### Investigation

The following possibilities were considered:

1. LED load
2. Firmware problem
3. Arduino IDE issue
4. PlatformIO vs Arduino IDE
5. FTDI voltage configuration
6. ESP32-CAM power supply capability

The LEDs were disconnected, which ruled out the LED load as the immediate cause.

The FTDI was also tested using its 5 V output connected to the ESP32-CAM 5 V input, but the brownout remained.

### Understanding the Error

A brownout occurs when the ESP32 detects that its supply voltage has fallen below a safe level.

Wi-Fi can produce short periods of increased current demand. If the power source or wiring cannot maintain a stable voltage, the ESP32 resets itself.

Typical sequence:

```text
ESP32 starts
     ↓
Wi-Fi starts
     ↓
Current demand increases
     ↓
Supply voltage drops
     ↓
Brownout detector activates
     ↓
ESP32 resets
     ↓
Wi-Fi starts again
```

### Current Status

The brownout issue is not yet considered solved.

The next test is to use a stable external 5 V USB power source capable of supplying sufficient current to the ESP32-CAM.

The brownout protection should not simply be disabled to hide the problem.

## Important Lesson

The failure is useful for debugging because the LED firmware works while the Wi-Fi firmware causes the reset. This indicates that power behavior under higher load must be investigated before continuing with the network-controlled lighting stage.
