void putString(String s) {
//  Serial.print(s);
}

void setup() {
  Serial.begin(9600);
  putString("Start tracking...");
  int reading = analogRead(A0);
  putString("First SEND and first reading...");
  Serial.println(reading,1);
}

int reading = 0;
int total = 0;
int count = 0;
float average = 0.0;
uint32_t period = 60000L;       // 1 minute
int i;
bool zero = false;

// the loop routine runs over and over again forever:
void loop() {
  count = 0;
  total = 0;
  reading = analogRead(A0);
  if (reading == 0) {
    Serial.println(0.0,4);
  }
  putString("Check for string of zeros");
  while (reading == 0) {
    delay(500);
    reading = analogRead(A0);
  }
  putString("No zeros");
  total += reading;
  count++;
  for(uint32_t tStart = millis();  (millis()-tStart) < period;  ) {
    reading = analogRead(A0);
    if (reading == 0) {
      putString("Encountered zero during 1 minute loop");
      zero = true;
      break;
      }
    total += reading;
    count++;
    delay(500);
  }
  putString("SEND average: ");
  average = total / count;
  Serial.println(average,3);
  if (zero) {
    delay(1050);
    Serial.println(0.0,2);
    zero = false;
  }
}
