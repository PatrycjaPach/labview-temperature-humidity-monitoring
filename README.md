# Temperature and Humidity Monitoring System (LabVIEW)

## 📖 Description

This project is a simple measurement system that reads temperature and humidity data from a microcontroller and visualizes it in a LabVIEW application.

The device collects environmental data using a digital sensor and sends it via serial communication (UART).
LabVIEW receives the data, parses it, displays the measurements in real time, and logs them for further analysis.

The goal of the project was to learn practical data acquisition, serial communication and building a graphical measurement interface.

---

## 🛠 Technologies

* LabVIEW
* Serial communication (UART / COM port)
* Embedded C++ (microcontroller firmware)
* Environmental sensor DHT11

---

## ⚙ System Overview

The system consists of two parts:

### 1. Embedded Device

The microcontroller:

* reads temperature and humidity from the sensor
* formats the data into a text frame
* sends the data via UART every second

### 2. LabVIEW Application

The LabVIEW VI:

* opens the COM port connection
* reads serial data continuously
* extracts temperature and humidity values
* displays values 

---

## 💻 LabVIEW Features

* real-time temperature display
* real-time humidity display
* waveform chart plotting measurements over time
* connection status indicator
* start/stop measurement button
* calculation of humidity coefficient and dew point

---

## 📂 Project Structure

* `/main` – main application logic (sensor reading, data formatting and transmission)
* `/components/DHT11` – driver responsible for communication with the DHT11 temperature and humidity sensor
* `/include` – header files and shared declarations used across the firmware
* `CMakeLists.txt` – build configuration for the ESP-IDF project
* `sdkconfig` – ESP-IDF project configuration
* `temperature_and_humidity.vi` – LabVIEW application for data acquisition and visualization


---

## ▶ How to Run

1. Connect the microcontroller to the PC via USB.
2. Upload firmware to the microcontroller.
3. Open the LabVIEW VI file.
4. Select the correct COM port.
5. Click **RUN** in Labview

The measurements should appear immediately on the front panel.

---

## 👥 Team & Responsibilities

This was a 2-person project. Each member was responsible for a different part of the system.

### 👤 Patrycja Pach contributions

* Programming reading from DHT11 in object-oriented C++
* Developed the USB communication interface in LabVIEW using VISA functions, including device detection, connection handling, and continuous data reading
* Parsed incoming UART data frames and converted them into numeric values for further processing and visualization
* Implemented dew point and heat index calculations and integrated their visualization into the graphical user interface


### 👤 Antonia Zdźiebko contributions



### Shared responsibilities

* Hardware setup and wiring
* System integration and debugging
* Testing the communication between device and PC

