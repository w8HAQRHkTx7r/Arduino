/* 
 *  Stereo photography rig
 *  ======================
 *  Control a pan/tilt
*/

#include <Servo.h>

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

Servo pan;  // create servo object to control a servo
Servo tilt;

// Pan / Tilt
int tiltAngle = 90;
int panAngle = 90;
int buttonPush = 1;
int settle = 3000;

float x;
float y;

void setup() {
  // Enable the push button
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  
  pan.attach(9);  // attaches the servo on pin 9 to the servo object
  tilt.attach(10);
}

void loop() {
  buttonPush =  digitalRead(SW_pin);
  if (buttonPush == 0) {
//    Serial.println("--- RESET ---");
    tiltAngle = 90;
    panAngle = 90;
  }
  // Point the camera for left eye
//  Serial.println("Aim the camera");
//  Serial.print("   Tilt Angle = "); Serial.println(tiltAngle);
//  Serial.print("   Pan Angle  = "); Serial.println(panAngle);
  tilt.write(tiltAngle);
  pan.write(panAngle);

  x = analogRead(X_pin);
  if (x > 900) {
    panAngle += 1;
  }
  if (x < 100) {
    panAngle -= 1;
  }
  pan.write(panAngle);
  
  y = analogRead(Y_pin);
  if (y > 900) {
    tiltAngle -= 1;
  }
  if (y < 100) {
    tiltAngle += 1;
  }
  tilt.write(tiltAngle);

  delay(250);

}
