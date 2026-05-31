# Solar-Powered Smart Home Automation & Security System

An IoT-based Smart Home Automation and Security System powered entirely by solar energy and controlled through MQTT communication. The system enables remote appliance control, automatic lighting, environmental monitoring, motion detection, gas leak detection, and emergency alert activation using an ESP32 microcontroller.

---

## Project Overview

Modern smart homes often depend on continuous grid power and expensive automation platforms. This project demonstrates a low-cost, energy-efficient alternative by combining renewable energy with IoT technology.

The system uses an ESP32 connected to multiple sensors and communicates through an MQTT broker. Users can remotely monitor environmental conditions and control appliances from a smartphone using MQTT Panel.

The entire setup operates on a rechargeable battery charged by solar panels, making it suitable for sustainable smart home applications and areas with unreliable electricity supply.

---

## Key Features

### Smart Home Automation

* Remote control of three rooms/appliances.
* Manual ON/OFF operation through MQTT.
* Automatic lighting control based on environmental conditions.

### Environmental Monitoring

* Real-time temperature monitoring.
* Real-time humidity monitoring.
* Gas level monitoring for safety applications.

### Security Features

* Motion detection using a PIR sensor.
* Emergency alarm activation through MQTT.
* Real-time security status updates.

### Renewable Energy Integration

* Solar-powered operation.
* Rechargeable battery backup.
* Energy-efficient standalone system.

### IoT Connectivity

* Wi-Fi enabled ESP32 controller.
* MQTT-based communication.
* Real-time data publishing and monitoring.

---

## Hardware Components

| Component            | Purpose                        |
| -------------------- | ------------------------------ |
| ESP32                | Main controller                |
| DHT11                | Temperature & humidity sensing |
| MQ Gas Sensor        | Gas detection                  |
| PIR Sensor           | Motion detection               |
| LDR Module           | Ambient light sensing          |
| Active Buzzer        | Emergency alarm                |
| LEDs/Relays          | Appliance control              |
| Solar Panel          | Renewable energy source        |
| Rechargeable Battery | Energy storage                 |
| MQTT Panel App       | User interface                 |

---

## System Working

The ESP32 continuously collects data from multiple sensors and publishes the readings to MQTT topics.

### Automatic Lighting Logic

The lighting system uses both an LDR and PIR sensor.

* Dark environment + Motion detected → Lights ON
* Bright environment → Lights OFF
* No motion detected → Lights OFF

This helps reduce unnecessary energy consumption while improving convenience.

### Remote Appliance Control

Users can control appliances using MQTT commands:

| Mode | Function                      |
| ---- | ----------------------------- |
| ON   | Turns appliance ON            |
| OFF  | Turns appliance OFF           |
| AUTO | Uses automatic lighting logic |

Each room can operate independently.

### Emergency Alert System

An emergency command can be sent remotely through MQTT.

When activated:

* Buzzer turns ON
* Emergency status is triggered

This can be used for alerts, warnings, or security notifications.

---

## MQTT Topics

### Published Topics

| Topic        | Description            |
| ------------ | ---------------------- |
| esp32/temp   | Temperature readings   |
| esp32/hum    | Humidity readings      |
| esp32/gas    | Gas sensor values      |
| esp32/motion | Motion status          |
| esp32/light  | Automatic light status |

### Subscribed Topics

| Topic           | Description             |
| --------------- | ----------------------- |
| esp32/room1     | Room 1 control          |
| esp32/room2     | Room 2 control          |
| esp32/room3     | Room 3 control          |
| esp32/emergency | Emergency alarm control |

---

## Control Commands

### Room Commands

| Command | Action              |
| ------- | ------------------- |
| ON      | Force appliance ON  |
| OFF     | Force appliance OFF |
| AUTO    | Automatic operation |

### Emergency Commands

| Command | Action            |
| ------- | ----------------- |
| ON      | Activate buzzer   |
| OFF     | Deactivate buzzer |

---

## Solar Power Architecture

The system operates entirely from stored solar energy.

Solar Panel → Battery Charging → Battery Storage → ESP32 & Sensors

Benefits:

* Reduced electricity consumption
* Sustainable operation
* Portable deployment
* Backup during power outages

---

## Repository Structure

```text
Solar-Smart-Home-Automation/
│
├── README.md
├── LICENSE
│
├── code/
│   └── smart_home_automation.ino
│
├── images/
│   ├── project_overview.jpg
│   ├── hardware_setup.jpg
│   ├── solar_panel.jpg
│   ├── mqtt_dashboard.jpg
│   └── system_architecture.png
```

---

## Future Enhancements

* Voice assistant integration
* Mobile application development
* Cloud data logging
* Energy consumption analytics
* Smart scheduling
* AI-based automation
* Push notifications for alerts

---

## Applications

* Smart homes
* Remote monitoring systems
* Sustainable IoT projects
* Energy-efficient automation
* Educational and research projects

---

## Developed By
Meha Goswami 
ESP32-based Solar Smart Home Automation and Security System utilizing MQTT communication, environmental sensing, automated lighting, and renewable energy integration.
