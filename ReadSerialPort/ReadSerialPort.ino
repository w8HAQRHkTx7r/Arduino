void setup() {
  Serial.begin(9600);
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
  i = 1;
  for(uint32_t tStart = millis();  (millis()-tStart) < period;  ) {
    count++;
    reading = analogRead(A0);
    if (reading < 1) {
      zeros++;
    if (zeros >= 3) {
      zeros = 0;
      total = 0;
      count = 1;
//      Serial.println("The blower shut off");
      delay(30000);
      break;
    }
    }
    total += reading;
    delay(500);
    i++;
  }
  average = total / count;
  Serial.println(average);
  count = 0;
  total = 0;
}
