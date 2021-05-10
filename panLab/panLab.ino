/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo pan;  // create servo object to control a servo
Servo tilt;

// twelve servo objects can be created on most boards

int tiltVertical = 80;
int panMax = 165;
int panMin = 45;
int settle = 4000;

void setup() {
  pan.attach(9);  // attaches the servo on pin 9 to the servo object
  tilt.attach(10);
  tilt.write(tiltVertical);
//  Serial.begin(9600);
}

void loop() {
  for (int i = panMin; i <= panMax; i+=5) {
    pan.write(i);
    delay(settle);
  }
  for (int i = panMax; i >= panMin; i-=5) {
    pan.write(i);
    delay(settle / 2);
  }
}