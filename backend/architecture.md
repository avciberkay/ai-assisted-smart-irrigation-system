## Backend Architecture

The backend is designed as a lightweight, containerized system running on a VPS.

ESP32 devices publish sensor data to an MQTT broker.
This data is consumed by automation workflows that evaluate irrigation conditions.

External weather data is fetched via APIs and combined with sensor data.
Based on the evaluation, irrigation actions are triggered automatically and system events are logged.

The backend is structured to be reproducible and modular using Docker.
