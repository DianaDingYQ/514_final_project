# 514_final_project：Plant Monitor Device

## Overall Function
The device can monitor soil moisture, light intensity, and temperature to help people who aren’t good at taking care of plants easily understand their growth conditions, such as when to water their plants or adjust light exposure by changing their spots.

**Physical Features:**
- **Sensor Device:** Includes soil moisture sensor, BME 280 sensor, ESP32, and battery.
- **Display Device:** Contains a motor-driven gauge, LED light, OLED screen,ESP32，and battery.

## Sensor Device
The sensor device collects real-time data and sends it wirelessly to the display device.
- **Components:**
  - Soil Moisture Sensor: Measures soil moisture.
  - BME280 Sensor: Measures light intensity and temperature.
  - ESP32: Processes data and sends it.
  - Lithium Battery: Powers the device.
