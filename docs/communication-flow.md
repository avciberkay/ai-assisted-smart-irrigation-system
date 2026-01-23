## Communication Flow

The system follows a unidirectional data flow from sensors to decision logic and back to actuators.

1. ESP32 devices read soil moisture sensor values at defined intervals.
2. Sensor data is published to the backend using MQTT topics.
3. The backend subscribes to these topics and receives incoming data.
4. Weather data is fetched from an external API.
5. An AI-based automation workflow evaluates sensor and weather data together.
6. A decision is produced indicating whether irrigation is required and for how long.
7. The irrigation command is sent back to the ESP32 via MQTT.
8. A notification is sent to the user describing the decision and system status.

This flow allows real-time control while keeping device-side logic minimal.
