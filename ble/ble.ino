#include <ArduinoBLE.h>

char* uuid = "ce01088b-b99c-4894-9a2d-96c92312e4b6";

BLEService            maceService(uuid);
BLEByteCharacteristic toggleCharacteristic(uuid, BLERead | BLENotify);

byte r[16] = {0x09, 0x0d, 0x02, 0x03, 0x04, 0x05,
    0x06, 0x07, 0x0a, 0x09, 0x0A, 0x0B, 0x0C,
    0x0D, 0x0E, 0x0F};


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
  int index = random(16);
  byte byteData = r[index];

  Serial.begin(9600);
  delay(2000);
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1) {;
    }
  } else {
    Serial.println("BLE is live");
    Serial.println(BLE.address());
  }

  BLE.setLocalName("MACE");
  
  BLE.setAdvertisedService(maceService);
  maceService.addCharacteristic(toggleCharacteristic);
  BLE.addService(maceService);
  
  toggleCharacteristic.writeValue(byteData);
 
  // start advertising
  BLE.advertise();
  Serial.print("I'm advertising on");
  Serial.println(BLE.address());
  Serial.print("Index: ");
  Serial.println(index);
  Serial.print("byteData: ");
  Serial.println(byteData);
}


void loop() {
  BLEDevice central = BLE.central();
  if (central) {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    Serial.print("Value: ");
    Serial.println(toggleCharacteristic.value());
    delay(500);
  }
}
