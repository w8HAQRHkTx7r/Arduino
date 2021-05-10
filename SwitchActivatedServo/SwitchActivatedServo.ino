//www.elegoo.com
//2016.12.08
#include <Servo.h>

// create servo object to control a servo
// twelve servo objects can be created on most boards
Servo myservo;

int pos = 0;    // position expressed in degrees

const int ledPin = 13; // built-in led attach to

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // servo signale pin
  pinMode(ledPin,OUTPUT); //initialize the ledPin as an output
  pinMode(2,INPUT); // tilt switch signal ping
  digitalWrite(2, HIGH);  // why set an input pin?
}

int prevVal = 0;

void loop() {
  int digitalVal = digitalRead(2);
  if (digitalVal != prevVal) {
    Serial.println("Change in switch");
    Serial.println(digitalVal);
    prevVal = digitalVal;
    if(HIGH == digitalVal) {
      Serial.println("HIGH");
      digitalWrite(ledPin,HIGH);
      pos = 90;
      Serial.println(pos);  
      myservo.write(pos);
      delay(1000); // debounce and let servo reach position
      }
    else {
      Serial.println("LOW");
      digitalWrite(ledPin,LOW);
      pos = 0;
      Serial.println(pos);
      myservo.write(pos);
      delay(1000); // debounce and let servo reach position
      }
    }
  }
