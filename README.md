# FanController PCB

A custom PCB for controlling fans in industrial electronic cabinets. It uses the PIC18F45K22 microcontroller and interfaces with two DS18B20 temperature sensors to regulate fan speed based on the temperature difference inside and outside the cabinet. It supports both 230V AC and 24V DC fans and has an option for logging data over TCP via an ESP01 module.

## Features

- Interfaces with two DS18B20 temperature sensors.
- Supports one 230V AC fan and one 24V DC fan.
- Regulates fan speed based on the temperature difference inside and outside the cabinet.
- Optional data logging over TCP using an ESP01 module.

## Hardware Components

- **Microcontroller**: PIC18F45K22
- **Temperature Sensors**: 2x DS18B20
- **Fan Support**:
  - 230V AC fan
  - 24V DC fan
- **Connectivity**: ESP01 module for optional data logging over TCP

### Prerequisites

- **MPLAB X IDE** for firmware development.
- **PICkit** or another compatible programmer for flashing the PIC18F45K22.
- PCB and components (refer to the Bill of Materials in the `/hardware` directory).

## Usage

Once powered on, the FanController PCB will:

- Read temperatures from the inside and outside DS18B20 sensors.
- Automatically adjust the speed of the connected 230V AC or 24V DC fan based on the temperature difference.
- Optionally, log temperature and fan speed data over TCP if the ESP01 module is connected and properly configured.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
