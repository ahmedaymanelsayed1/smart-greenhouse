تمام ✅ خلينا نجهز نسخة README بالإنجليزي باسم المشروع الجديد **Smart Greenhouse**، مع نفس التفاصيل اللي ذكرتها، لكن بشكل مرتب واحترافي لرفعها على GitHub:

---

# 🌱 Smart Greenhouse with IoT Monitoring

## 🔹 Project Overview

The **Smart Greenhouse** is an automated farming system that integrates **renewable energy, environmental monitoring, and IoT technology**.
It uses a **solar-powered system with dual-servo tracking** to maximize energy efficiency, while multiple sensors monitor soil, air, and light conditions.

The system is capable of **automatic irrigation, cooling, and fire/smoke detection**, with alerts and controls accessible through an **LCD display and mobile application**.

This project demonstrates how **IoT + renewable energy + smart farming** can create a more **sustainable and efficient agricultural solution**.

---

## 🛠️ Hardware Components

### 🔋 Power & Energy

* **2 × Servo Motors** – rotate solar panel for sun tracking.
* **Solar Panel** – main energy source.
* **Solar Charge Controller** – manages battery charging.
* **Rechargeable Batteries** – provide continuous power.

### 🔥 Safety & Security

* **Smoke Sensor (MQ-2 / MQ-135)** – detects smoke and harmful gases.
* **Flame Sensor** – detects presence of fire.
* **Buzzer/Alarm Module** – triggers alert in case of fire/smoke.

### 🌱 Farming & Environmental Monitoring

* **Soil Moisture Sensors** – detect soil water level.
* **DHT22 / DHT11 Sensor** – measure air temperature and humidity.
* **LDR Sensors (Light Sensors)** –

  * Ambient light detection (to supplement sunlight with artificial light).
  * Mounted on solar panel for **sun tracking**.

### 🌬️ Actuators

* **Cooling Fans** – turn on when temperature/humidity is high.
* **Water Pump Motors** – activate irrigation when soil moisture is low.

### 📟 User Interface & IoT

* **LCD Display (16x2 / 20x4)** – shows greenhouse data and allows manual control.
* **Mobile Application (IoT)** – for real-time monitoring and control via WiFi/Bluetooth.

---

## 💻 Software Requirements

### 🔹 Microcontroller Code (Arduino / ESP32)

* Reads sensor data (temperature, humidity, soil moisture, light, flame, smoke).
* Controls actuators (fans, pumps, alarm, solar tracker).
* Displays data on LCD.
* Communicates with Mobile App.

Libraries Used:

* `Servo.h` – for solar tracking servos.
* `LiquidCrystal.h` – for LCD.
* `DHT.h` – for temperature & humidity.
* `ESP32WiFi.h` / `WiFi.h` – for IoT communication.

### 🔹 Mobile Application

* Built using **MIT App Inventor / Blynk / custom app**.
* Features:

  * Display real-time sensor readings.
  * Push alerts for smoke/fire detection.
  * Manual control for pumps, fans, and alarm.

---

## ⚙️ System Workflow

1. **Solar Power System**

   * LDR sensors detect sunlight direction.
   * Servos adjust solar panel for maximum efficiency.
   * Solar charge controller charges batteries.

2. **Environmental Monitoring**

   * Soil sensors measure water content.
   * DHT sensor checks air humidity & temperature.
   * LDR checks sunlight levels for plant growth.

3. **Automatic Actions**

   * If **soil is dry** → pump irrigates plants.
   * If **temperature is high** → cooling fans activate.
   * If **smoke/fire detected** → alarm & app alert triggered.

4. **User Interaction**

   * LCD provides live feedback and manual controls.
   * Mobile app allows remote monitoring and overrides.

---

## 🌟 Features

* ✅ Solar-powered with **dual-servo sun tracking**.
* ✅ Automatic irrigation based on soil conditions.
* ✅ Fire and smoke detection with alarm alerts.
* ✅ Real-time monitoring of temperature, humidity, and light.
* ✅ Cooling fans for environmental control.
* ✅ Mobile app for remote access & LCD for local control.
* ✅ Scalable design for larger farms and greenhouses.

---

## 🔮 Future Improvements

* Cloud database integration (Firebase, ThingSpeak) for data history.
* AI-based prediction for irrigation & temperature control.
* Integration with weather forecasts for smarter automation.
* Adding AI-powered cameras for pest/disease detection.
* Expandable to larger greenhouses with modular design.

---

## 📂 Project Structure

```
├── Arduino/
│   └── smart_greenhouse.ino   # Arduino/ESP32 code
├── MobileApp/
│   └── smart_greenhouse.aia   # MIT App Inventor project file
├── Images/
│   └── greenhouse_diagram.jpg # Block diagram
├── README.md                  # Documentation
```
