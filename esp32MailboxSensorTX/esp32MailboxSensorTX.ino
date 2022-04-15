/*
  ESP-NOW Demo - Transmit
  esp-now-demo-xmit.ino
  Sends data to Responder
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/

// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

// Variables for test data
int int_value;
float float_value;
bool bool_value = true;

// MAC Address of responder - edit as required
//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC7, 0xE4}; // Short cord
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC8, 0x28}; // Long cord
//uint8_t broadcastAddress[] = {0x98, 0xCD, 0xAC, 0x51, 0xA9, 0x64}; // ESP32

// Define a data structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  bool d;
} struct_message;

// Create a structured object
struct_message myData;

// Peer info
esp_now_peer_info_t peerInfo;

void printBroadcastAddress() {
  for (int hexade=0; hexade<6; hexade++) {
    Serial.print(broadcastAddress[hexade], HEX); if (hexade < 5) {Serial.print(":");}  
  }
}

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print(millis());
  Serial.print(" ");
  Serial.print("MAC "); Serial.print(WiFi.macAddress());
  Serial.print(" is Broadcasting --> to ");
  printBroadcastAddress();
  Serial.print(" Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  
  // Set up Serial Monitor
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("I'm TX MAC Address: ");
  Serial.println(WiFi.macAddress());

  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {

  // Create test data

  // Generate a random integer
  int_value = random(1,20);

  // Use integer to make a new float
  float_value = 1.3 * int_value;

  // Invert the boolean value
  bool_value = !bool_value;
  
  // Format structured data
  strcpy(myData.a, "Welcome to the Workshop!");
  myData.b = int_value;
  myData.c = float_value;
  myData.d = bool_value;
  
  // Send message via ESP-NOW
  digitalWrite(13, HIGH);
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.print("esp_now_send() OK ");
  }
  else {
    Serial.print("esp_now_send() not OK ");
  }
  delay(500);
  digitalWrite(13, LOW);
  delay(2000);

}
