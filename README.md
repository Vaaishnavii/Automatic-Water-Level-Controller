# Automatic-Water-Level-Controller
A smart, low-cost embedded system that automates motor control to prevent water overflow and save electricity. This project monitors water levels in both the sump and overhead tanks using sensors and only runs the motor when necessary. It adds voltage safety logic to protect hardware and enhance system reliability.

🚀 Features
Dual-level sensing using an Ultrasonic Sensor (overhead tank) and Flow Sensor (sump tank)

Automatic motor ON/OFF control based on real-time sensor inputs

Overvoltage/Undervoltage detection to protect motor hardware

LCD display for system status (tank level, power conditions, sump availability)

Built using Arduino Uno, with simple wiring and low-cost components

🛠️ Tech Stack & Components
Arduino Uno

Ultrasonic Sensor (HC-SR04) and Flow Sensor

Relay module, DC motor, 7805 voltage regulator, LCD (16x2)

Power supply circuit with center-tapped transformer, Zener diode, and safety resistors

Code written in Embedded C (Arduino IDE)

📦 Applications
Domestic water tank automation

Load shedding-prone areas

Industrial liquid-level automation systems
