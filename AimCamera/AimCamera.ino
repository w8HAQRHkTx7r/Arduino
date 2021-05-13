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
int panOffset = 0;
int tiltOffset = 0;

int tiltAngle = 90;
int panAngle = 90;

int buttonPush = 1;

int settle = 3000;

float x;
float y;

void setup() {
  // Enable the push button
  pinMode(SW_pin, INPUT);
  // Pull up the resister
  digitalWrite(SW_pin, HIGH);
  
  // attaches pin 9/10 to the servo objects
  pan.attach(9);
  tilt.attach(10);
}

void logString(String) {

}

void logInt(int) {
  
}
void loop() {
  // Check for reset
  buttonPush =  digitalRead(SW_pin);
  if (buttonPush == 0) {
    logString("--- RESET ---");
    tiltOffset = 0;
    panOffset = 0;
  }
  
  // Point the camera for left eye
  logString("Aim the camera\n   Tilt Angle = "); 
  logInt(tiltAngle);
  logString("   Pan Angle  = "); 
  logInt(panAngle);

//  tilt.write(tiltAngle);
//  pan.write(panAngle);

  x = analogRead(X_pin);
  if (x > 900) {
    panOffset += 1;
  }
  if (x < 100) {
    panOffset -= 1;
  }
  pan.write(panAngle+panOffset);
  
  y = analogRead(Y_pin);
  if (y > 900) {
    tiltOffset -= 1;
  }
  if (y < 100) {
    tiltOffset += 1;
  }
  tilt.write(tiltAngle+tiltOffset);

  delay(100);

}
