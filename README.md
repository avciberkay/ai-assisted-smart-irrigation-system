# AI Assisted Smart Irrigation System

This project is an end to end smart irrigation system that I designed and built to solve a real problem.  
Most irrigation systems are either fully manual or based on simple threshold logic. In real conditions this does not work well. Soil behavior changes, plants have different needs, and weather conditions constantly affect irrigation decisions.

The goal of this project was to build a system that can sense the environment, understand context, and make reliable autonomous decisions without human intervention.

This system combines embedded hardware, power electronics, cloud infrastructure, automation workflows, external data sources, and AI assisted decision making.

---

## What this system does

The system continuously measures soil and environmental conditions and sends the data to a self hosted backend server.

In addition to sensor data, the system also considers the type of plant growing in the field and real time weather information obtained through external APIs. This allows irrigation decisions to be context aware instead of purely reactive.

Based on all available inputs, the system decides autonomously whether irrigation is needed.  
If irrigation is required, the pump is activated safely and the operation is logged.

Notifications are sent to the user for monitoring and transparency, not for approval.  
Human intervention was intentionally removed because the system proved to be stable and reliable during long term testing.

The system runs autonomously for long periods using solar power and a lithium ion battery pack.

---

## System overview

At a high level the system consists of:

An ESP32 based embedded node  
Soil moisture and environmental sensors  
Relay controlled water pump  
Custom power management using solar panel and battery  
Self hosted backend running on a VPS  
MQTT based communication  
Automation workflows  
AI assisted decision logic  
External weather data integration  

All parts were designed to work together as one complete system.

---

## Hardware layer

The hardware part of this project was designed to be reliable and energy efficient.

ESP32 is used as the main controller.  
Soil moisture is measured using capacitive sensors.  
Environmental data such as temperature and humidity are also collected.

Power is supplied by a solar panel and a lithium ion battery pack with BMS protection.  
CC CV charging is implemented and power paths are designed to avoid backfeeding and unsafe conditions.

A custom PCB was designed for sensor connections, power distribution, and relay control.  
The system was tested for voltage stability, current consumption, and thermal behavior.

All schematics, PCB files, BOM and power design notes are included in the hardware folder.

---

## Firmware layer

The ESP32 firmware handles sensor sampling, timing logic, safety checks, and communication.

Sensor data is filtered and sampled at defined intervals.  
Decision related preprocessing is performed before data is transmitted.

Communication with the backend is done using MQTT.  
If communication is lost or abnormal behavior is detected, the system enters a safe state to prevent uncontrolled irrigation.

The firmware was written with reliability and long term operation in mind.

Firmware source code and configuration files are available under the firmware folder.

---

## Backend and automation layer

The backend is fully self hosted on a VPS.

Docker is used to manage all services.  
MQTT broker handles device communication.  
Nginx is used as a reverse proxy.  
Automation workflows are built using n8n.

Incoming sensor data is logged and processed.  
Weather data is fetched through external APIs.  
Plant specific parameters are taken into account.

All inputs are combined to determine whether irrigation is required.  
When conditions are met, irrigation is triggered automatically and the event is recorded.

All backend services are containerized and reproducible.

Deployment notes and docker compose files are included in the backend and deployment folders.

---

## AI integration

AI is used as a decision support and interpretation layer.

The system does not rely on fixed thresholds alone.  
Sensor readings, plant type, and weather data are evaluated together.

AI helps interpret raw data and generate context aware decisions.  
It also produces human readable explanations for notifications and logs.

AI does not directly control hardware signals.  
Final control actions are executed through deterministic automation logic.

This design improves transparency while keeping the system stable and predictable.

---

## Testing and validation

The system was tested continuously for multiple days.

Battery voltage remained stable.  
No abnormal heating was observed.  
Energy consumption was very low.  
Water usage was measured and consistent.

The system operated fully autonomously without requiring human approval.  
Notifications and logging worked reliably throughout the test period.

This was a real world deployment, not a simulation.

---

## Project video

A full project demonstration video is available on YouTube.  
The video shows the hardware, system operation, and real notifications.

Link can be found in the media folder.

---

## Academic evaluation

This project received an AA grade.  
The technical report was reviewed positively and appreciated for its system level design and documentation quality.

---

## Repository structure

hardware contains PCB, power design and mechanical notes  
firmware contains ESP32 source code  
backend contains docker, mqtt, nginx and automation setup  
deployment contains VPS and security notes  
docs contains diagrams and test results  
media contains photos and video links  

---

## Future improvements

Web based monitoring dashboard  
Long term field calibration  
Multi node deployment  
More advanced fault detection  
Expanded plant database  
Predictive irrigation strategies  

---

## Final note

This project reflects how I approach engineering problems.  
I focus on complete systems, real constraints, and real validation.

Every part of this repository represents a working component of the final system.

If you are reviewing this repository as an engineer, recruiter, or researcher, feel free to explore each layer independently.
