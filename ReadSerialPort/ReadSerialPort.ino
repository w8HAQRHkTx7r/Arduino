void setup() {
  Serial.begin(9600);
  int reading = analogRead(A0);
  Serial.println(0);
  Serial.println(reading);
}

int reading = 0;
int total = 0;
int count = 0;
float average = 0.0;
uint32_t period = 60000L;       // 1 minute
int i;
int zeros = 0;

// the loop routine runs over and over again forever:
void loop() {
  count = 0;
  total = 0;
  reading = analogRead(A0);
  while (reading == 0) {
    delay(500);
    reading = analogRead(A0);
  }
  for(uint32_t tStart = millis();  (millis()-tStart) < period;  ) {
    reading = analogRead(A0);
    if (reading == 0) {
      Serial.println(reading);
      break;
      }
    total += reading;
    count++;
    delay(500);
  }
  average = total / count;
  Serial.println(average);
}
