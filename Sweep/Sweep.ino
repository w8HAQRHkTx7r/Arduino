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

int tiltMax = 90;
int tiltMin = 90;
int panMax = 95;
int panMin = 85;
int settle = 8000;

void setup() {
  pan.attach(9);  // attaches the servo on pin 9 to the servo object
  tilt.attach(10);
  Serial.begin(9600);
 }

void loop() {
  Serial.println("");
  Serial.print("Tilt to "); Serial.println(tiltMax);
  tilt.write(tiltMax);
  Serial.print("Pan to "); Serial.println(panMax);
  pan.write(panMax);
  delay(settle);

  Serial.print("Tilt to "); Serial.println(tiltMin);
  tilt.write(tiltMin);
  Serial.print("Pan to "); Serial.println(panMin);
  pan.write(panMin);
  delay(settle);
}
