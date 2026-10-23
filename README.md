# IoT Experiments

### Student Details

NAME: T.G SRAVAN TEJA

1ST M.Tech - CSE

261FB04042

A collection of Internet of Things (IoT) experiments and projects developed for learning, simulation, and practical implementation.

## Projects

### Experiment 18 — Water Level Monitoring

**Objective:** Simulate a water-level monitoring system using an ESP32 and send measurements to ThingSpeak for online monitoring.

**Components and Tools**

- ESP32 — simulated microcontroller
- Potentiometer — simulated water-level sensor
- Wokwi — circuit simulation
- PlatformIO — build environment
- ThingSpeak — cloud data logging
- Visual Studio Code — development environment

**Features**

- Reads simulated sensor values using the ESP32 ADC.
- Converts readings into a water-level percentage from 0% to 100%.
- Displays readings in the serial terminal.
- Uploads water-level measurements to ThingSpeak.
- Displays recorded measurements on a ThingSpeak chart.

**Project Structure**

```text
Experiment-18-Water-Level-Monitoring/
├── diagram.json
├── platformio.ini
├── wokwi.toml
└── src/
    └── main.cpp
```

**Security Note:** API keys and other credentials are stored locally and must not be committed to the public repository.

## Future Projects

Additional IoT experiments will be documented here as they are implemented.

## License

A license will be added when the repository's sharing requirements are decided.
