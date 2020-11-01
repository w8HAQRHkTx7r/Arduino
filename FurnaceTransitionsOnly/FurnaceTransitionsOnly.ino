void putString(String s) {
//  Serial.print(s);
}

bool waitForZero = false;
int reading = 0;

void setup() {
  Serial.begin(9600);
  putString("Start tracking...");
  putString("Initial reading...");
  reading = analogRead(A0);
  Serial.println(reading, 5);
  if (reading == 0) {
    waitForZero = false;    
  }
  if (reading != 0) {
    waitForZero = true;
  }
}


// the loop routine runs over and over again forever:
void loop() {
  if (waitForZero) {
    reading = analogRead(A0);
    while (reading != 0) {
      delay(250);
      reading = analogRead(A0);    
    }
    Serial.println(reading, 4);
    waitForZero = false;
  }

  if (!waitForZero) {
    reading = analogRead(A0);
    while (reading == 0) {
      delay(250);
      reading = analagRead(A0);
    }
    Serial.println(reading, 3);
    waitForZero = true;
  }
}
