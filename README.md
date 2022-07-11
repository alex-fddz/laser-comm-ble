# BLE to Morse Code Laser Communication Auto-Pairing System (B.L.E.M.C.L.C.A.P.S.)

This project allows for wireless communication between a sender and a receiver. The sender is a smartphone which sends a message through Bluetooth Low Energy technology to an ESP32 board. This board then process the information and encodes the message to Morse Code. A laser is then actuated to send the message.

The receiver is a sort of antenna with a small stepper motor, which allows for automatically pairing with the emitter. A photoresistor captures the Morse Code, and an Arduino decodes it and displays it on an LCD Screen. 

## Hardware

### Sender

- ESP32
- Laser Diode
- Photoresistor (enables pairing detection)
- A smartphone (for Bluetooth communication)
- 3D Printed laser and photoresistor tray

### Receiver

- Arduino UNO
- Laser Diode (enables pairing detection)
- Photoresistor
- LCD Screen
- Stepper Motor
- 3D Printed turret (stepper motor housing)
- 3D Printed laser and photoresistor tray

## Code

Programming is done through Platformio on VS Code. It consists of two projects. Parent folder corresponds to the sender (ESP32), and `arduino-receiver` corresponds to the receiver (Arduino UNO).

## Models

3D printed models can be found in the `3DModels` folder, and `svg` files for laser cutting can be found in the `LaserCut` folder.
