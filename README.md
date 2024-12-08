# IoT-Based Smart Irrigation System

An IoT system using NodeMCU ESP8266 to automate irrigation by monitoring soil moisture and environmental conditions.

Features
- Automatically controls a water pump based on soil moisture levels.
- Monitors temperature and humidity using a DHT sensor.
- Sends real-time data to an MQTT broker.
- Supports mobile or web-based monitoring and control.

Tech Stack
- Microcontroller: NodeMCU ESP8266
- Sensors: Soil moisture sensor, DHT11/22
- Protocol: MQTT
- Software: Arduino IDE, MQTT broker (e.g., HiveMQ)

Components Required
- NodeMCU ESP8266
- Soil Moisture Sensor (e.g., FC-28)
- DHT11/22 Sensor
- Relay Module
- Water Pump/Valve
- Jumper wires and breadboard

Setup
1. Install the required libraries:
   - [PubSubClient](https://github.com/knolleary/pubsubclient)
   - [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
2. Connect the hardware as per the circuit diagram.
3. Upload the `main.ino` file to the NodeMCU.
4. Configure the MQTT broker or use HiveMQ's free public broker.

Circuit Diagram
![Circuit Diagram](path/to/diagram.png)

Usage
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/smart-irrigation-system.git
