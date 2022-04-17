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
RTC_DATA_ATTR unsigned long tymeStamp;

#define uS_TO_S_FACTOR    1000000ULL  /* Conversion factor for micro seconds to seconds */

#define SECONDS_TO_SLEEP  15        /* Time ESP32 will go to sleep (in seconds) */

#define FLASHY_FEEDBACK true  /* Flash the LED when transmitting to help debug
                                 Set to false for production */

// MAC Address of responder - edit as required
const uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC8, 0x28};
//const uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//const uint8_t broadcastAddress[] = {0x94, 0xB9, 0x7E, 0x79, 0xC7, 0xE4};
//const uint8_t broadcastAddress[] = {0x98, 0xCD, 0xAC, 0x51, 0xA9, 0x64};

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
  for (int hexade = 0; hexade < 6; hexade++) {
    Serial.print(broadcastAddress[hexade], HEX); if (hexade < 5) {
      Serial.print(":");
    }
  }
}

void print_wakeup_reason() {
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch (wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0  :
      Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1  :
      Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : // If you woke because of a timer, register a pin timer and go right back to sleep;
      Serial.println("Wakeup caused by timer");
      Serial.println("Go to sleep now and wait for the door to open");
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_26, 1); //1 = High, 0 = Low
      esp_deep_sleep_start();
      Serial.println("You should not have gotten this far");
      break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD :
      Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP :
      Serial.println("Wakeup caused by ULP program"); break;
    default :
      Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason); break;
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
  while (!Serial) {
    ;
  }

  // Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));

  // Initialize pins
  if (FLASHY_FEEDBACK) {
    pinMode(13, OUTPUT);       // External confirmation
    digitalWrite(13, LOW);     // Turn LED off
  }
  pinMode(26, INPUT_PULLUP); // Reed switch RTC pin number

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("I'm TX MAC Address: ");
  Serial.println(WiFi.macAddress());

  print_wakeup_reason();

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
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  // Format structured data
  int door = digitalRead(26); // The switch must already have opened, because this woke up
  Serial.print(" Door state is "); Serial.println(door);
  myData.door = door;
  tymeStamp += millis(); // Save cumulative awake-time to RTC RAM.
  myData.tymeStamp = tymeStamp;
  myData.bootCount = bootCount;

  // Send message via ESP-NOW
  if (FLASHY_FEEDBACK) {
    digitalWrite(13, HIGH); // Flash the LED to indicate this code is running
  }
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.print("esp_now_send() OK ");
    if (FLASHY_FEEDBACK) {
      delay(500);
      digitalWrite(13, LOW);
    }

    esp_sleep_enable_timer_wakeup(SECONDS_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.print("Go to sleep now and wake up in "); Serial.print(SECONDS_TO_SLEEP); Serial.println(" seconds");
    esp_deep_sleep_start();

  } else {

    Serial.print("esp_now_send() not OK ");
    // Make sure the LED stays lit for long enough to see before going low
    if (FLASHY_FEEDBACK) {
      delay(500);
      digitalWrite(13, LOW);
    }
  }
}

void loop() {
  // If we get to here, something went wrong
  // How to get word to Mikey?!
  Serial.println(millis());
  delay(2000);
}
