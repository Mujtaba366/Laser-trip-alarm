# Laser Trip Alarm with VL53L0X

A simple yet effective **laser tripwire alarm** using the VL53L0X time-of-flight sensor, Arduino, RGB LED, and buzzer.  
Perfect for security, pranks, or monitoring doorways/hallways.

---

## Features

- **Non-visible laser trip detection** using VL53L0X sensor
- **Arm / Disarm** with single button:
  - Short press → Arm (Red)
  - Long hold (0.8s) → Reset / Disarm (Green)
- **Clear status indication** with RGB LED:
  - **Green** = Unarmed / Safe
  - **Red** = Armed
  - **Flashing Red + Blue** = Alarm triggered (police-style)
- Buzzer sounds during alarm
- Two versions included:
  - Full brightness
  - Dim mode (good for photography)

---

## Hardware Requirements

- Arduino Nano / Uno / Pro Mini
- VL53L0X Laser Distance Sensor
- Common Anode RGB LED
- Active Buzzer
- Push Button
- 3.3V or 5V power (depending on your setup)

### Pinout

| Component          | Pin          | Note                          |
|--------------------|--------------|-------------------------------|
| VL53L0X SDA        | A4           | I2C                           |
| VL53L0X SCL        | A5           | I2C                           |
| RGB Red            | 5            | PWM                           |
| RGB Green          | 6            | PWM                           |
| RGB Blue           | 9            | PWM                           |
| Buzzer             | 4            | Digital                       |
| Button             | 12           | INPUT_PULLUP                  |
| VL53L0X XSHUT      | 10           | Optional (kept LOW)           |

**Note:** RGB LED is **Common Anode** (common pin connected to 3.3V).

---

## Libraries Required

- `Wire` (built-in)
- [VL53L0X by Pololu](https://github.com/pololu/vl53l0x-arduino) (or Adafruit version)

---

## How to Use

1. Upload the code to your Arduino.
2. Power on the device → LED turns **Green** (Unarmed).
3. Place the sensor and aim it across the area you want to monitor.
4. **Short press** the button → LED turns **Red** (Armed).
5. If someone crosses the laser beam → Alarm triggers (flashing Red/Blue + buzzer).
6. **Hold** the button for ~0.8 seconds to reset and turn Green again.

---

## Files

- `laser_trip_alarm_full.ino` → Full brightness version
- `laser_trip_alarm_dim.ino` → Dim version (~50% brightness for photos)

---

## Customization

You can easily change:
- Alarm flash speed (currently 220ms)
- Button hold time (currently 800ms)
- Dim brightness level (`brightness` variable)

---

## License

Open source - feel free to modify and share!

Made with ❤️ for fun and learning.
