# Layers of IoT — Virtual Monitoring Notebook

**Name:** T G SRAVAN TEJA
**Roll No.:** 261FB04042

## Overview

`LayersOfIOT.ipynb` is a Python/Jupyter Notebook project that demonstrates selected IoT and OSI-layer concepts using simulated data. It generates sample readings and virtual network/session records, displays them in tables, plots charts, and reports basic condition checks.

> **Note:** The notebook uses simulated/random data. It does not connect to physical sensors or perform real network packet transmission.

## Layers Demonstrated

- **IoT Perception Layer** — Generates virtual temperature, humidity, and light readings; displays readings and charts; flags temperatures above 35 °C.
- **IoT Network Layer** — Simulates sensor-data packets with packet size, latency, and transmission status; displays a table and graphs.
- **OSI Data Link Layer** — Simulates frames with source and destination MAC addresses, frame sizes, checksum status, and frame-condition reporting.
- **OSI Transport Layer** — Simulates TCP/UDP segments, port numbers, segment sizes, retry counts, delays, and delivery status.
- **OSI Session Layer** — Generates virtual sessions with IDs, users, durations, and states such as Active, Timed Out, and Closed.
- **OSI Presentation Layer** — Encodes sample messages as UTF-8 hexadecimal strings, decodes them, checks whether the data matches, and compares data lengths.

## Tools and Libraries

- Python
- Jupyter Notebook
- pandas — tables and data handling
- Matplotlib — charts and visualizations
- Python standard libraries: `random`, `time`, and `datetime`

## Requirements

Install the required Python libraries if they are not already available:

```bash
pip install pandas matplotlib notebook
```

## How to Run

1. Open `LayersOfIOT.ipynb` in Jupyter Notebook or Visual Studio Code with the Jupyter extension.
2. Ensure the required libraries are installed.
3. Run the notebook cells in order from top to bottom.
4. Review the generated tables, charts, and condition-monitoring messages.

Because the notebook uses random values, results may differ each time it runs.

## Project File

```text
LayersOfIoT/
└── LayersOfIOT.ipynb
```

## Future Improvements

- Add the OSI Application Layer.
- Connect the perception layer to real sensors or an IoT simulator.
- Extend network monitoring with more realistic communication and packet-loss models.
- Export generated data and reports to CSV.

---

Replace **Your Name** and **Your Roll Number** with your details before submitting.
