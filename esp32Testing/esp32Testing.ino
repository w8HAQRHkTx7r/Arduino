void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Started");
  pinMode(13, OUTPUT);
  digitalWrite(13,HIGH);
}

void loop() {
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
}
