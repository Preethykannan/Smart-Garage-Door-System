# Smart-Garage-Door-System
#Smart Garage Door System using IoT (ESP32 + Servo Motors)

This project demonstrates a simple smart garage door system controlled remotely over Wi-Fi using an **ESP32 microcontroller** and **servo motors**, without using any sensors.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Components Used

- ESP32 – Microcontroller with built-in Wi-Fi
- Servo Motors (2x) – For opening and closing the garage door
- Breadboard– For circuit connections
- Jumper Wires
- Wi-Fi Network – For hosting the control interface

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# System Overview

The ESP32 connects to your Wi-Fi and starts a local web server on port `8080`. A simple HTTP-based interface allows you to control the garage door by sending commands (`/ON` or `/OFF`). The system uses servo motors connected to GPIO pins to simulate the door's opening and closing actions.

>> This prototype does **not use any physical sensors** to detect door state; actions are based on assumed servo positions.

---

## Folder Structure

```bash
.
├── arduino_code.ino          # Main Arduino code for ESP32
└── README.md                 # Project documentation
