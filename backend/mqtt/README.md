## MQTT Broker

The system uses an MQTT broker for communication between ESP32 devices and the backend.

Devices publish sensor data to predefined topics.
Backend automation workflows subscribe to these topics and process incoming messages.

The broker runs as a Docker container.
A reference Docker Compose
