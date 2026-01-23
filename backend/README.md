## Backend Overview

This backend runs on a self-hosted VPS and supports the smart irrigation system.

It receives sensor data from ESP32 devices via MQTT, processes the data, applies automation logic, and sends notifications.

The backend services are containerized using Docker.
A sanitized reference configuration is provided for reproducibility.
