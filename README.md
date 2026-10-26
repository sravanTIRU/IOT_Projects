# IoT Experiments

### Student Details

NAME: T.G SRAVAN TEJA

1ST M.Tech - CSE

261FB04042

# IoT Experiments and Network Simulation Projects

A collection of IoT experiments and networking simulations created for learning, experimentation, and practical implementation.

## Projects

### 1. Experiment 18 — Water Level Monitoring

**Objective:** Simulate a water-level monitoring system using an ESP32 and send measurements to ThingSpeak for online monitoring.

**Tools and Components**

- ESP32 — simulated microcontroller
- Potentiometer — simulated water-level sensor
- Wokwi — circuit simulation
- PlatformIO — build environment
- ThingSpeak — cloud data logging
- Visual Studio Code — development environment

**Features**

- Reads simulated sensor values through the ESP32 ADC.
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

**Security:** Keep API keys and other credentials local. Do not commit them to a public repository.

---

### 2. Layers of IoT — Virtual Monitoring Notebook

**Objective:** Demonstrate selected IoT and OSI-layer concepts using Python, generated data, tables, charts, and simple condition checks.

**Tools**

- Python
- Jupyter Notebook
- pandas
- Matplotlib

**Layers Demonstrated**

- **Perception Layer:** Generates simulated temperature, humidity, and light readings, plots them, and flags high temperatures.
- **Network Layer:** Simulates sensor-data packets with packet size, latency, and transmission status.
- **Data Link Layer:** Simulates frames with MAC addresses, frame sizes, and checksum status.
- **Transport Layer:** Simulates TCP/UDP segments, port numbers, sizes, retries, delays, and delivery status.
- **Session Layer:** Simulates sessions with IDs, users, durations, and states.
- **Presentation Layer:** Encodes sample messages as UTF-8 hexadecimal strings, decodes them, and checks the result.

**Project File**

```text
LayersOfIoT/
└── LayersOfIOT.ipynb
```

**Note:** The notebook uses simulated/generated data. It does not by itself connect to physical sensors or transmit real network packets.

---

### 3. NS-3 Network Simulation Programs

**Objective:** Explore networking concepts by simulating nodes, links, routing, transport protocols, and network performance with NS-3 and C++.

**Programs**

1. **UDP Echo Communication Between Two Nodes** — Simulates UDP client-server communication with an echo server.
2. **Bandwidth, Delay and Throughput Analysis Using FlowMonitor** — Measures packet statistics, average delay, and throughput for UDP traffic.
3. **Three-Node Network Communication Using Routing** — Sends UDP packets from a source through an intermediate router to a destination.
4. **IoT Gateway Communication Using NS-3** — Simulates four IoT nodes sending UDP packets to a central gateway.
5. **Performance Comparison of TCP and UDP Protocols** — Runs TCP and UDP traffic and compares received bytes.
6. **Network Congestion and Throughput Analysis** — Simulates UDP traffic over a limited-bandwidth link with a small queue and measures received throughput.

**Tools**

- NS-3 — network simulator
- C++ — programming language
- Wireshark — optional tool for examining PCAP captures

**Suggested Project Structure**

```text
NS3-Network-Simulation/
├── Project-1.cpp
├── Project-2.cpp
├── Project-3.cpp
├── Project-4.cpp
├── Project-5.cpp
├── Project-6.cpp
└── README.md
```

Source files may use `.cc` or `.cpp`, depending on the NS-3 project setup.

**Note:** Project 6 calculates received bytes and throughput. Exact packet loss requires additional packet-counting or monitoring logic.

---

## Requirements

- Python and Jupyter Notebook for the Layers of IoT notebook
- Required Python packages: `pandas` and `matplotlib`
- NS-3 and a compatible C++ build environment for the network simulations
- VS Code, PlatformIO, and Wokwi for the water-level monitoring simulation
- ThingSpeak account and API credentials for cloud logging

## Future Projects

Additional IoT experiments, monitoring notebooks, and network simulation projects will be documented here as they are implemented.
