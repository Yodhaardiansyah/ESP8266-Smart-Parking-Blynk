## 📘 **README: ESP8266 Smart Parking System with Blynk**  

This project is a **Smart Parking System** using an **ESP8266**, **sensors**, and **servo motors**, with real-time monitoring via **Blynk**. It automatically detects vehicle entry and exit, updates parking slot availability, and controls the gates accordingly.  

📌 **Created by:** Yodha Ardiansyah  
📷 **Instagram:** [@yodhaar_](https://instagram.com/yodhaar_)  
🌐 **GitHub:** [Yodha Ardiansyah](https://github.com/Yodhaardiansyah)  

---  

## **🚀 Features**  
✅ Automatically detects vehicles entering and exiting the parking area  
✅ Controls entry and exit gates using servo motors  
✅ Monitors parking slot availability using sensors  
✅ Sends real-time updates to the **Blynk** app  
✅ Displays available slots on the **Blynk dashboard**  

---  

## **📜 Requirements**  
- **ESP8266 (e.g., NodeMCU)**  
- **Blynk app (for monitoring)**  
- **Servo motors (for gate control)**  
- **Infrared or ultrasonic sensors (for vehicle detection)**  
- **WiFi connection**  

---  

## **🔧 Wiring Diagram**  
| ESP8266 Pin | Component | Function |
|------------|----------|----------|
| **D3** | Entry Sensor | Detects vehicles entering |
| **D4** | Exit Sensor | Detects vehicles exiting |
| **D6** | Parking Sensor 1 | Detects occupancy of Slot 1 |
| **D8** | Parking Sensor 2 | Detects occupancy of Slot 2 |
| **D7** | Servo (Entry Gate) | Controls the entry gate |
| **D2** | Servo (Exit Gate) | Controls the exit gate |

💡 *Note: You can use IR sensors, ultrasonic sensors, or magnetic sensors for vehicle detection.*  

---  

## **📜 Code Overview**  

### **1️⃣ WiFi & Blynk Connection**  
The ESP8266 connects to WiFi and the **Blynk** cloud for real-time updates.  

```cpp
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
}
Blynk.begin(auth, ssid, pass);
```

### **2️⃣ Vehicle Detection & Gate Control**  
The system detects vehicle movement and opens/closes gates automatically.  

```cpp
if (entrySensorState == LOW && availableSlots > 0) {
    Serial.println("Entry sensor triggered. Opening entry gate.");
    openGate(entryGateServo);
    availableSlots--;
}
```

### **3️⃣ Real-time Parking Slot Update**  
Parking slot availability is updated and sent to **Blynk**.  

```cpp
Blynk.virtualWrite(V0, availableSlots);
Blynk.virtualWrite(V1, isParking1Empty ? 1 : 0);
Blynk.virtualWrite(V2, isParking2Empty ? 1 : 0);
```

---  

## **📥 Installation**  

### **1️⃣ Clone this Repository**  
```sh
git clone https://github.com/Yodhaardiansyah/ESP8266-Smart-Parking-Blynk.git
```

### **2️⃣ Install Required Libraries in Arduino IDE**  
- **ESP8266WiFi** (built-in for ESP8266)  
- **BlynkSimpleEsp8266** (for Blynk integration)  
- **Servo** (for controlling the gates)  

### **3️⃣ Update WiFi & Blynk Credentials**  
Edit the following in **Arduino code**:  
```cpp
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
```

### **4️⃣ Upload the Code to ESP8266**  
1. Connect ESP8266 to your PC  
2. Select **Board: NodeMCU 1.0 (ESP-12E Module)**  
3. Set **Baud Rate: 115200**  
4. Click **Upload**  

### **5️⃣ Setup Blynk Dashboard**  
1. Open **Blynk app** and create a new project  
2. Add widgets:  
   - **Label Display** (V0) → Available Slots  
   - **LED Widget** (V1) → Parking Slot 1 Status  
   - **LED Widget** (V2) → Parking Slot 2 Status  
3. Copy the **Blynk Auth Token** into the code  

---

## **🌍 Troubleshooting**  
🔹 **ESP8266 not connecting to WiFi?**  
- Check SSID and password  
- Restart router or move closer  

🔹 **Servo not moving?**  
- Check connections  
- Ensure correct GPIO pin assignment  

🔹 **Incorrect parking slot detection?**  
- Adjust sensor sensitivity  
- Check sensor wiring  

---

## **📜 License**  
This project is open-source under the **MIT License**.  

---

🚀 **Enjoy your Smart Parking System!** 🚀  
💡 **Follow for more projects:**  
📷 **Instagram:** [@yodhaar_](https://instagram.com/yodhaar_)  
🌐 **GitHub:** [Yodha Ardiansyah](https://github.com/Yodhaardiansyah)
