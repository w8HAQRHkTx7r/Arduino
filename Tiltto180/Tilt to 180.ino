/* Sweep
  by BARRAGAN <http://barraganstudio.com>
  This example code is in the public domain.

  modified 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo tilt;

void setup() {
  tilt.attach(9);
  Serial.begin(9600);
 }

void loop() {
  Serial.println("");
  Serial.print("Tilt to 180");
  tilt.write(180);
  delay(2000);
}
