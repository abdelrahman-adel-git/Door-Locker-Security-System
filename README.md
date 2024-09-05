<h1 align="center">
 🚪Door Locker Security System🚪
</h1> 

This project implements a Door Locker Security System using two ATmega32 microcontrollers, designed with a layered architecture to ensure modularity and efficient management of hardware components.

## 🛠️Project Overview

The system is divided into two main units:

- **HMI_ECU**: The Human-Machine Interface microcontroller, responsible for handling user interactions.
- **CONTROL_ECU**: The Control microcontroller, responsible for managing password verification, EEPROM storage, and controlling the door mechanism.

### 🌟Features

- **HMI_ECU**:
  - Receives user input through a 4x4 keypad.
  - Displays system messages on a 2x16 LCD.

- **CONTROL_ECU**:
  - Verifies the password entered by the user.
  - Stores and retrieves passwords using EEPROM.
  - Controls the door locking/unlocking mechanism using a DC motor.
  - Handles system warnings and alerts with a buzzer.

### 🔧Components and Drivers

- **Microcontroller**: ATmega32 (8MHz)
- **Drivers Used**:
  - GPIO (General Purpose Input/Output)
  - LCD (Liquid Crystal Display)
  - Keypad
  - DC Motor
  - EEPROM
  - I2C 
  - UART 
  - Timer1
  - Buzzer

## 🏗️System Architecture

The system is designed with a layered architecture:

1. **HMI_ECU**:
   - **Input Layer**: Handles user inputs via the keypad.
   - **Display Layer**: Communicates with the LCD to display prompts and status messages.

2. **CONTROL_ECU**:
   - **Communication Layer**: Uses UART to communicate with the HMI_ECU.
   - **Storage Layer**: Manages password storage in EEPROM.
   - **Control Layer**: Operates the DC motor and buzzer based on user authentication and system status.
  
 ## 💻Simulation of the Door Locker Security System
 ![image](https://github.com/user-attachments/assets/d92da03e-a7ac-463a-8e45-04d3905dbe42)

