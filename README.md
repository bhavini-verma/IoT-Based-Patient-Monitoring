IoT-Based Patient Monitoring System (ESP32)

## Overview

This project implements a lightweight IoT-based patient monitoring system using the ESP32 microcontroller. The system acquires physiological and environmental data from multiple sensors and serves real-time metrics through an embedded HTTP web server over Wi-Fi.

The solution demonstrates end-to-end edge computing — from sensor interfacing to browser-based visualization — without requiring external cloud infrastructure.

---

## Key Features

* Real-time heart rate and SpO₂ integration (MAX30100)
* Body temperature sensing via 1-Wire interface (DS18B20)
* Ambient temperature and humidity monitoring (DHT11)
* Embedded HTTP server running directly on ESP32
* Dynamic HTML dashboard for live vitals display
* Periodic data refresh with on-device processing

---

## System Architecture

Sensors (I2C / 1-Wire / GPIO)
→ ESP32 Firmware (Embedded C++)
→ Lightweight HTTP Server
→ Web Browser Dashboard (Wi-Fi)

---

## Tech Stack

* ESP32
* Embedded C++ (Arduino Framework)
* WiFi.h
* WebServer.h
* MAX30100 Pulse Oximeter Library
* DallasTemperature & OneWire
* DHT Sensor Library
* HTML/CSS generated from firmware

---

## How It Works

1. ESP32 connects to a local Wi-Fi network.
2. Sensors are polled periodically for data.
3. Readings are processed within the firmware loop.
4. The onboard HTTP server serves dynamically generated HTML.
5. Users access the device IP address in a browser to monitor vitals in real time.

---

## Potential Enhancements

* Secure HTTPS implementation
* MQTT/cloud integration
* Real-time alert notifications
* Data logging and trend analysis
* Signal filtering and sensor calibration

---