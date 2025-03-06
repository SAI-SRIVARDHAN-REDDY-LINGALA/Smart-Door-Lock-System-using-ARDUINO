# Smart Door Lock System using Arduino, Keypad, LCD & Servo Motor

## 📌 Project Overview
This project demonstrates a **smart door lock system** using an **Arduino UNO**, a **4x4 keypad**, an **LCD display**, a **servo motor**, and a **buzzer**. The user enters a predefined password to unlock the door.

## 🛠️ Components Required
- Arduino UNO
- 16x2 LCD Display (I2C)
- 4x4 Matrix Keypad
- Servo Motor (SG90 or similar)
- Buzzer
- Jumper Wires
- Power Supply

## 🏗️ Circuit Connections
| Component | Arduino Pin |
|-----------|------------|
| **LCD Display (I2C)** | SDA (A4), SCL (A5) |
| **Buzzer** | Digital Pin 11 |
| **Servo Motor** | Digital Pin 10 |
| **Keypad Rows** | 9, 8, 7, 6 |
| **Keypad Columns** | 5, 4, 3, 2 |

## 🔌 Wiring Diagram
See **circuit_diagram/** folder for connection images.

## 📜 Code
The Arduino `.ino` file is included in this repo. Upload it to your board using the **Arduino IDE**.

## 🛠️ Setup Instructions
1. Connect the components as per the wiring diagram.
2. Upload the `smart_lock.ino` file to Arduino.
3. Use the keypad to enter the password (default: `0123`).
4. The door unlocks when the correct password is entered.
5. A wrong password triggers the buzzer.

## 📜 License
This project is open-source under the **MIT License**.
