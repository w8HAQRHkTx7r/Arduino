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

RTC_DATA_ATTR int bootCount = 0;

// MAC Address of responder - edit as required
//uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC7, 0xE4};
uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC8, 0x28};
//uint8_t broadcastAddress[] = {0x98, 0xCD, 0xAC, 0x51, 0xA9, 0x64};


// Define a data structure
typedef struct struct_message {
  unsigned long tymeStamp;
  bool door;
  int bootCount;
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
  pinMode(13, OUTPUT);       // External confirmation 
  pinMode(26, INPUT_PULLUP); // Reed switch RTC pin number
  digitalWrite(13, LOW);     // Turn LED off

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
  int door = digitalRead(26); // The switch must already have opened, because this woke up
                              // So what's the point of reading the current state?
  // Create test data
  // Format structured data
  myData.door = door;
  myData.tymeStamp = millis();
  myData.bootCount = bootCount;
  
  // Send message via ESP-NOW
  digitalWrite(13, HIGH); // Flash the LED to indicate this code is running
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
//  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33,1); //1 = High, 0 = Low
  // Won't this keep triggering over and over again because right after it goes to sleep
  // the door is in the open state and will therefore wake up.

  //If you were to use ext1, you would use it like
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  //Go to sleep now
//  Serial.println("Going to sleep now");
//  esp_deep_sleep_start();
}
