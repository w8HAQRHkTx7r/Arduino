/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo tilt;
Servo pan;

void setup() {
  tilt.attach(10);
  pan.attach(9);
 }

void loop() {
  tilt.write(80);
  pan.write(90);
  delay(2000);
}
