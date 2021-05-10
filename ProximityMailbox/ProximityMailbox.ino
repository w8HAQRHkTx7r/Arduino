#include <Servo.h>
#include "SR04.h"

#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long a;

Servo myservo;
int pos = 0;    // position expressed in degrees

void setup() {
  //   Serial.begin(9600);
  myservo.attach(9);  // servo signale pin
  delay(1000);
}

void loop() {
  a = sr04.Distance();
  //   Serial.print(a);
  //   Serial.print(" cm");
  if (a <= 31) {
    pos = 85;
    //      Serial.print(" Close ");
    //      Serial.println(pos);
    myservo.write(pos);
  }
  else {
    pos = 0;
    //     Serial.print(" Far ");
    //     Serial.println(pos);
    myservo.write(pos);
  }
  delay(1000);
}
