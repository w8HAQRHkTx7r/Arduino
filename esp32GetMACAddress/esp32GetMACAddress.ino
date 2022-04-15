#include "WiFi.h"
void setup() {
  Serial.begin(115200);
  Serial.println("Started");

  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
  
  WiFi.mode(WIFI_MODE_STA);
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

}

void loop() {
  // It helps to have SOMETHING visible
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
}
