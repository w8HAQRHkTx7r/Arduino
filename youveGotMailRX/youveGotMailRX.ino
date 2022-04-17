/*
  ESP-NOW Demo - Receive
  esp-now-demo-rcv.ino
  Reads data from Initiator
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

// Define a data structure
typedef struct struct_message {
  unsigned long tymeStamp;
  bool door;
  int bootCount;
} struct_message;

// Create a structured object
struct_message myData;

Servo flagServo;
const int servoPin = 18;

// Callback function executed when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  digitalWrite(13,HIGH);
  if (len > sizeof(myData)) {
    Serial.println("Fatal error. Too much data");
  } else {
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.print(len);
    Serial.print(" tyme: ");
    Serial.print(myData.tymeStamp);
    Serial.print(" Door: ");
    Serial.print(myData.door);
    Serial.print(" Boots: ");
    Serial.print(myData.bootCount);
    Serial.println();
    flagServo.write(90);
  }
  delay(500);
  digitalWrite(13,LOW);  
}

void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13,LOW);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  flagServo.setPeriodHertz(50);
  flagServo.attach(servoPin, 500, 2400);
  Serial.println("Zero out flag");
  flagServo.write(0);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("I'M RX MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("esp_now_init() success");
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  
}
