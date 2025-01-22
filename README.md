# 514_final_project：Plant Monitor Device

## Overall Function
The device can monitor soil moisture, light intensity, and temperature to help people who aren’t good at taking care of plants easily understand their growth conditions, such as when to water their plants or adjust light exposure by changing their spots.

![Plant Monitor Overview](https://github.com/DianaDingYQ/514_final_project/blob/7444408b749473ad43dd18be3c126cc7b980fd3b/plant_monitor.jpg)

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

![Sensor Device Overview](https://github.com/DianaDingYQ/514_final_project/blob/7d88aa1ccbae8d68a91a3e4248ebb06e63b5c618/sensor_slide.jpg)

## Display Device
The display device translates data into visual outputs.
- **Features:**
  - Motor-Driven Gauge: Displays soil moisture levels.
  - LED Light Indicator: Lights up when the soil moisture is below a threshold.
  - OLED Screen: Displays numerical data for soil moisture, light intensity, and temperature.
  - Tac Button: Switches between light intensity and temperature displays.
![Display Sensor Device Overview](https://github.com/DianaDingYQ/514_final_project/blob/7d88aa1ccbae8d68a91a3e4248ebb06e63b5c618/display_slide.jpg)

## Communication and Workflow
![Communication Diagram](https://github.com/DianaDingYQ/514_final_project/blob/e170dd6a9a0a8a7d84ec6e1c5b2751c2766cb2f4/communication.jpg)
![Workflow Diagram](https://github.com/DianaDingYQ/514_final_project/blob/e170dd6a9a0a8a7d84ec6e1c5b2751c2766cb2f4/workflow.jpg)


## Datasheets

Below are the datasheets for the components used in this project:

1. [ESP32-WROOM-32 Datasheet](https://github.com/DianaDingYQ/514_final_project/blob/245f632a71dc274b233177428b37fe5e066069aa/esp32-wroom-32_datasheet_en.pdf)
2. [BME280 Datasheet](https://github.com/DianaDingYQ/514_final_project/blob/245f632a71dc274b233177428b37fe5e066069aa/BST-BME280-DS002-1509607.pdf)
3. [Soil Moisture Sensor Datasheet](https://github.com/DianaDingYQ/514_final_project/blob/245f632a71dc274b233177428b37fe5e066069aa/soilmoisturesensor.pdf)
