## Automation Workflows (n8n)

The system uses n8n as an automation engine to process incoming sensor data and make irrigation decisions.

Workflows consume MQTT messages, combine sensor readings with external weather data, and determine whether irrigation is required.

n8n runs as a Docker container on the VPS.
Workflow logic is designed to be modular and extensible.

Production workflows are not exported directly.
This repository documents the role and structure of the automation layer.
