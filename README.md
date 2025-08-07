# 🔐 Smart Motion-Activated Security System

This Arduino project is a motion-detection security system using an **ESP8266**, **ultrasonic sensor**, **buzzer**, and **LED**, connected to the **Blynk app** for real-time alerts. It's designed to help secure spaces like **patient record rooms** by detecting unauthorized motion and instantly notifying the user.

---

## 🚀 Features
- 📡 Ultrasonic distance-based motion detection
- 🔔 Buzzer and LED alarm system
- 📱 Real-time alerts via Blynk (mobile notifications)
- 🕹️ Remote switch control using Blynk's virtual pin
- ⏱️ Cooldown feature to avoid repeated alerts

---

## 🧠 How It Works

When motion is detected within **10 cm**, the system:
- Triggers a buzzer and LED alarm
- Sends a **notification** to your Blynk app
- Uses a **cooldown** to avoid spammy alerts

You can also turn the system ON/OFF remotely through the **Blynk app (V1 switch)**.

---

## 🧰 Components Used
- ESP8266 Wi-Fi Module
- HC-SR04 Ultrasonic Sensor
- Passive Buzzer
- LED
- Breadboard & Jumper wires
- Blynk Mobile App (with Auth Token)

---

## 📲 Blynk Setup
1. Create a new project in the Blynk app
2. Add a **Switch** (V1) to control the system
3. Add a **Value Display** (V2) to monitor distance
4. Add an **Event Notification** widget for alerts
5. Use the following Auth Token in your code:

#define BLYNK_AUTH_TOKEN "your-token-here"

yaml
Copy code

> Replace WiFi credentials with your own SSID and password.

---

## 💻 Code Overview

```cpp
if (distance < 10) {
digitalWrite(buzzerPin, HIGH);
digitalWrite(ledPin, HIGH);
Blynk.logEvent("motion_alert", "Unauthorized motion detected!");
}

