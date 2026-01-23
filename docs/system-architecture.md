## System Architecture

This project is an AI-assisted smart irrigation system designed as a distributed embedded and cloud-based system.

The system consists of four main layers:

1. Field Layer  
ESP32-based embedded devices collect soil moisture sensor data and control the irrigation pump.

2. Communication Layer  
Devices communicate with the backend using the MQTT protocol over a network connection.

3. Backend Layer  
A containerized backend running on a VPS receives sensor data, processes it, fetches external weather information, and executes automation logic.

4. Decision and Notification Layer  
An AI-based decision engine evaluates sensor and weather data to determine irrigation duration.
System decisions and status updates are sent to the user via notifications.

The architecture is modular and allows individual components to be modified or scaled independently.
