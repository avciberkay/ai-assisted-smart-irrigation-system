# AI Assisted Smart Irrigation System

This project is an end-to-end smart irrigation system that I designed and built to solve a real, practical problem.

Most irrigation systems are either fully manual or based on fixed threshold logic. In real environments this approach performs poorly. Soil behavior changes over time, plants have different requirements, and weather conditions continuously affect irrigation needs.

The goal of this project was to build a system that can sense the environment, understand context, and make reliable autonomous decisions without requiring human approval.

The system combines embedded hardware, power electronics, cloud infrastructure, automation workflows, external data sources, and AI-assisted decision logic into a single working system.

---

## What this system does

The system continuously measures soil and environmental conditions and transmits the data to a self-hosted backend server.

In addition to raw sensor data, the system considers:
- plant characteristics defined in the automation logic
- real-time weather data fetched through external APIs

This allows irrigation decisions to be context-aware, rather than purely reactive.

Based on all available inputs, the system decides autonomously whether irrigation is required.  
If irrigation is needed, the pump is activated for a calculated duration and the operation is logged.

Notifications are sent to the user for monitoring and transparency only, not for approval.  
Human approval was intentionally removed after long-term testing proved the system to be stable and reliable.

The system is designed to operate continuously using a multi-source power architecture.

---

## System overview

At a high level, the system consists of:

- ESP32-based embedded field node  
- Soil moisture and environmental sensors  
- Relay-controlled water pump  
- Multi-source power system (solar, grid, battery)  
- Self-hosted backend running on a VPS  
- MQTT-based communication  
- Automation workflows  
- AI-assisted decision logic  
- External weather data integration  

All components were designed and validated to operate together as a single system.

---

## Hardware layer

The hardware was designed with reliability, safety, and energy efficiency in mind.

- ESP32 is used as the main controller  
- Soil moisture is measured using capacitive sensors  
- Environmental data such as temperature and humidity are collected  
- Pump control is isolated through relay switching  

### Power system

The power system is one of the core engineering components of this project.

Instead of relying on a single source, the system integrates:
- a solar panel
- city electricity via adapter
- a custom 4S3P lithium-ion battery pack with BMS

Hardware-level source selection, CCCV charging, diode OR-ing, and fuse protection are used to ensure:
- safe charging
- no back-feeding
- uninterrupted operation during power loss

Detailed power design notes and validation results are documented in the `hardware/` directory.

### Enclosure and wiring

The system was built as a functional prototype using direct wiring rather than a full system PCB, allowing rapid iteration and debugging.

A dedicated 3D-designed battery enclosure is included to demonstrate mechanical design capability and battery safety considerations.

---

## Firmware layer (ESP32)

The ESP32 firmware is responsible for:

- sensor sampling and timing  
- preprocessing of raw ADC values  
- MQTT communication with the backend  
- receiving irrigation commands  
- controlling pump activation safely  

Soil moisture sensors return raw ADC values in the range 0–4095, where lower values indicate wetter soil.

Decision making is intentionally kept out of the firmware.  
The ESP32 focuses on deterministic, reliable execution and safe operation.

Firmware source code is available in the `firmware/` directory.

---

## Backend and automation layer

The backend is fully self-hosted on a VPS.

- Docker is used to containerize services  
- Mosquitto handles MQTT communication  
- Nginx acts as a reverse proxy  
- Automation workflows are built using n8n  

Incoming sensor data is processed together with external weather data and plant-specific parameters.

Irrigation decisions are produced automatically and executed without manual intervention.  
All services are containerized and reproducible using documented configurations.

Backend architecture and deployment notes are available in the `backend/` and `deployment/` directories.

---

## AI integration

AI is used as a decision interpretation layer, not as a direct hardware controller.

The AI component:
- evaluates sensor readings together with weather context  
- produces structured irrigation decisions  
- generates human-readable explanations for logs and notifications  

Final control actions are executed through deterministic automation logic, ensuring system stability and predictability.

---

## Testing and validation

The system was tested continuously under real operating conditions.

- Battery voltage remained stable  
- No abnormal thermal behavior was observed  
- Power consumption was low  
- Water usage was consistent and controlled  

The system operated autonomously for extended periods without human approval.  
This was a real deployment, not a simulation.

---

## Project video and public links

Project demonstration video:  
https://www.youtube.com/watch?v=rDrQLltPG3M

LinkedIn:  
https://www.linkedin.com/in/berkay-avci-istanbul

---

## Academic evaluation

This project received an AA grade.

The technical report was reviewed positively and appreciated for its system-level design, documentation quality, and practical validation.

---

## Repository structure

- `hardware/` – power system, wiring, enclosure, and mechanical design  
- `firmware/` – ESP32 source code  
- `backend/` – Docker, MQTT, automation, and service architecture  
- `deployment/` – VPS and security notes  
- `docs/` – system diagrams and architecture documentation  
- `media/` – photos, diagrams, and video links  

---

## Future improvements

- Web-based monitoring dashboard  
- Long-term field calibration  
- Multi-node deployment  
- Advanced fault detection  
- Expanded plant database  
- Predictive irrigation strategies  

---

## Final note

This project reflects how I approach engineering problems.

I focus on complete systems, real constraints, and real validation rather than isolated components or simulations.

Every part of this repository represents a working or documented component of the final system.
