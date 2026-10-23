# Experiment 18 — Water Level Monitoring

### Student details:

Name: T.G SRAVAN TEJA

1ST M.Tech - CSE

Roll Number: 261FB04042

## 1. Aim

To simulate a water-level monitoring system using an ESP32 and a potentiometer, measure the water level as a percentage, and upload the readings to ThingSpeak for remote monitoring.

## 2. Project Overview

This project implements a digital version of a water-level monitoring system without requiring physical hardware. A potentiometer simulates the water-level sensor, and an ESP32 processes the input and sends the calculated water level to the ThingSpeak cloud platform.

## 3. Technologies Used

- **Microcontroller:** ESP32 DevKit
- **Simulated sensor:** Potentiometer
- **Simulation:** Wokwi
- **Development environment:** Visual Studio Code
- **Build system:** PlatformIO
- **Programming language:** C++ (Arduino framework)
- **Cloud platform:** ThingSpeak

## 4. Working Principle

1. The potentiometer provides an analog input to ESP32 GPIO 34.
2. The ESP32 reads the analog value, ranging from 0 to 4095.
3. The reading is converted into a water-level percentage.
4. The percentage is printed in the serial terminal.
5. The ESP32 connects to Wi-Fi and uploads the water-level percentage to ThingSpeak.
6. ThingSpeak displays the recorded measurements in a chart.

## 5. Water-Level Calculation

The water level is calculated using:

```cpp
waterLevel = (sensorValue / 4095.0) * 100.0;
```

| Sensor value | Approximate water level |
| -----------: | ----------------------: |
|            0 |                      0% |
|         2048 |                     50% |
|         4095 |                    100% |

These values represent a simulated water level, not measurements from a physical tank.

## 6. Circuit Connections

| Potentiometer pin | ESP32 connection |
| ----------------- | ---------------- |
| GND               | GND              |
| VCC               | 3V3              |
| SIG               | GPIO 34          |

## 7. Project Structure

```text
Experiment-18-Water-Level-Monitoring/
├── diagram.json
├── platformio.ini
├── wokwi.toml
├── .gitignore
└── src/
    ├── main.cpp
    └── secrets.h       # Local file; not committed
```

The `secrets.h` file contains the ThingSpeak Write API Key and must remain excluded from version control.

## 8. Setup and Execution

1. Install Visual Studio Code and the PlatformIO IDE extension.
2. Open the project folder in VS Code.
3. Install or resolve the dependencies specified in `platformio.ini`.
4. Configure the local ThingSpeak Write API Key in `src/secrets.h`.
5. Build the project using:

   ```bash
   pio run
   ```

6. Start the Wokwi simulator.
7. Adjust the potentiometer and observe the readings in the serial terminal.
8. Open the ThingSpeak channel's Private View to monitor uploaded measurements.

**Note:** The simulation uses Wokwi's guest Wi-Fi network. The ThingSpeak channel ID and API key must be configured correctly for cloud uploads.

## 9. Results

The simulation successfully reads changing potentiometer values, converts them to percentages, and uploads the measurements to ThingSpeak. The recorded values are visible in the channel's chart.

## 10. Limitations

- The potentiometer simulates a sensor; no physical water is measured.
- The calculated percentage assumes a linear relationship between the analog reading and water level.
- The project does not include physical sensor calibration.
- Automatic high-water-level notifications are not implemented.

## 11. Security

- Never commit API keys, passwords, or other credentials.
- Keep `src/secrets.h` and `.env` excluded through `.gitignore`.
- Do not publish screenshots or logs containing secret values.
- If a key is accidentally exposed, regenerate it in ThingSpeak.

## 12. Future Improvements

- Integrate a physical ultrasonic or water-level sensor.
- Add threshold-based alerts.
- Display measurements on a custom dashboard.
- Add sensor calibration and fault handling.

## 13. References

- [Wokwi Documentation](https://docs.wokwi.com/)
- [PlatformIO Documentation](https://docs.platformio.org/)
- [ThingSpeak Documentation](https://www.mathworks.com/help/thingspeak/)
