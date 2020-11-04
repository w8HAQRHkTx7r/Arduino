void putString(String s) {
//  Serial.print(s);
}

bool waitForZero = false;
int reading = 0;
int count = 0;
int total = 0;
uint32_t expired;

void setup() {
  Serial.begin(9600);
  putString("Start tracking...");
  putString("Initial reading...");
  // Calm down the signal
  for (int i=0; i<4; i++) {
    reading = analogRead(A0);
    delay(250);  
  }
  reading = analogRead(A0);
  Serial.println(reading, 5);
  if (reading == 0) {
    waitForZero = false;    
  }
  if (reading != 0) {
    waitForZero = true;
  }
}

uint32_t period = 60000L; 
float average;

// the loop routine runs over and over again forever:
void loop() {
  if (waitForZero) {
    uint32_t tStart = millis();
    count = 0;
    total = 0;
    reading = analogRead(A0);
    while (reading != 0) {
      count++;
      total += reading;
      delay(250);
      expired = millis() - tStart;
      if (expired > period) {
        average = total / count;
        Serial.println(average,1);
        count = 0;
        total = 0;
        tStart = millis();
      }
      reading = analogRead(A0);
    }
    Serial.println(0.0, 4);
    waitForZero = false;
  }

  if (!waitForZero) {
    reading = analogRead(A0);
    while (reading == 0) {
      delay(250);
      reading = analogRead(A0);
    }
    Serial.println(32.0, 3);
    waitForZero = true;
  }
}
