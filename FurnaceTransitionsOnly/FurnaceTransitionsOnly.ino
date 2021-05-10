// Using the $10 anemometer that I bought on eBay, I wrote this to transmit (over the serial port) readings of the relative rotation speed
// The red wire goes to A0 on the Arduino and the yellow wire goes to GND on the Arduino.

// Strategy:  If the prior reading was zero and the current reading is zero -- then don't transmit anything.  There's no point.
//            If the prior reading was non-zero, average the current reading into a running average.  Reset the average after
//               one minute (to avoid data collection overload) or a reading of zero is received.

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
//    Serial.println(32.0, 3);  // WTF?! Why write a constant?  s/b (reading,3)??                     
    Serial.println(reading, 3);  // changed 1/20/20.  Not immediately implemented.                     
    waitForZero = true;
  }
}
