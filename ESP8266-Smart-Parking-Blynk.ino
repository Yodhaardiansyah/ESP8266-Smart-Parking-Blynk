/*
 * ESP8266 Smart Parking System with Blynk
 * ----------------------------------------
 * This project monitors parking slot availability using sensors 
 * and controls the entrance/exit gates using servo motors.
 * The data is sent to the Blynk app for remote monitoring.
 *
 * Created by: Yodha Ardiansyah
 * GitHub: https://github.com/Yodhaardiansyah/ESP8266-Smart-Parking-Blynk
 * Instagram: @yodhaar_
 */

#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_TEMPLATE_NAME "Smart Parking"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

#include <ESP8266WiFi.h>
#include <Servo.h>
#include <BlynkSimpleEsp8266.h>

// Pin configuration
#define ENTRY_SENSOR D3
#define EXIT_SENSOR D4
#define PARKING_SENSOR_1 D6
#define PARKING_SENSOR_2 D8
#define ENTRY_GATE_SERVO_PIN D7
#define EXIT_GATE_SERVO_PIN D2

Servo entryGateServo;
Servo exitGateServo;

// Parking slot status
bool isParking1Empty = true;
bool isParking2Empty = true;
int availableSlots = 2;

// Blynk authentication token
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";

// WiFi credentials
char ssid[] = "YOUR_WIFI_SSID";
char pass[] = "YOUR_WIFI_PASSWORD";

void setup() {
  // Serial for debugging
  Serial.begin(9600);

  // Initialize sensor pins
  pinMode(ENTRY_SENSOR, INPUT);
  pinMode(EXIT_SENSOR, INPUT);
  pinMode(PARKING_SENSOR_1, INPUT);
  pinMode(PARKING_SENSOR_2, INPUT);

  // Initialize servos
  entryGateServo.attach(ENTRY_GATE_SERVO_PIN);
  exitGateServo.attach(EXIT_GATE_SERVO_PIN);

  // Set initial servo positions (closed)
  entryGateServo.write(0);
  exitGateServo.write(0);

  // Connect to WiFi and Blynk
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Blynk.begin(auth, ssid, pass);
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read sensor states
  int entrySensorState = digitalRead(ENTRY_SENSOR);
  int exitSensorState = digitalRead(EXIT_SENSOR);
  int parkingSensor1State = digitalRead(PARKING_SENSOR_1);
  int parkingSensor2State = digitalRead(PARKING_SENSOR_2);

  // Check entry gate
  if (entrySensorState == LOW && availableSlots > 0) {
    Serial.println("Entry sensor triggered. Opening entry gate.");
    openGate(entryGateServo);
    availableSlots--;
  }

  // Check exit gate
  if (exitSensorState == LOW) {
    Serial.println("Exit sensor triggered. Opening exit gate.");
    openGate(exitGateServo);
    availableSlots++;
  }

  // Update parking slot status
  isParking1Empty = (parkingSensor1State == HIGH);
  isParking2Empty = (parkingSensor2State == HIGH);

  // Send data to Blynk
  Blynk.virtualWrite(V0, availableSlots);
  Blynk.virtualWrite(V1, isParking1Empty ? 1 : 0);
  Blynk.virtualWrite(V2, isParking2Empty ? 1 : 0);

  Blynk.run();
}

void openGate(Servo &servo) {
  servo.write(90); // Open gate
  delay(2000);     // Wait for 2 seconds
  servo.write(0);  // Close gate
}
