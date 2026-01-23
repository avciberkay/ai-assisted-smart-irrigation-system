## ESP32 Firmware

This folder contains the firmware that runs on the ESP32 field unit.

The ESP32 is responsible for:
- Reading soil moisture sensors (raw ADC values)
- Formatting sensor readings into a message payload
- Publishing sensor data to the backend via MQTT
- Subscribing to irrigation control commands via MQTT
- Activating the irrigation pump for the commanded duration

### Sensor Logic

Soil moisture sensors are read as RAW ADC values in the range 0 to 4095.
Lower values represent wetter soil and higher values represent drier soil.

### Communication

Sensor data is published to an MQTT topic used by the backend automation workflow.
The pump duration command is received from another MQTT topic and executed locally.

### Notes

This firmware is designed to keep device-side logic minimal.
Decision making is handled on the backend by combining sensor readings with weather data and AI-based evaluation.
