## Mosquitto Broker

Mosquitto is used as the MQTT broker implementation in this system.

It handles message exchange between ESP32 devices and backend services.
The broker listens on standard MQTT ports and supports both unencrypted and encrypted connections.

Mosquitto runs as a Docker container.
Configuration files are mounted into the container to define listeners, persistence, and security options.

Only a sanitized reference configuration is shared in this repository.
