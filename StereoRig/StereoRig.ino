/*
    Stereo photography rig
    ======================
    Control a linear acctuator
    Control a pan/tilt
*/

#include <Servo.h>
#include <AccelStepper.h>

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = 0; // analog pin connected to X output
const int Y_pin = 1; // analog pin connected to Y output

Servo pan;  // create servo object to control a servo
Servo tilt;

// Define some steppers and the pins the will use
int IN11 = 3;
int IN21 = 4;
int IN31 = 5;
int IN41 = 6;

AccelStepper stepper1(AccelStepper::FULL4WIRE, IN11, IN31, IN21, IN41);  // UNL Stepper Driver sequence

// Linear acctuator
String inputBuffer = "";
bool stringComplete = false;
int pos = 0;
String direction = "";
int distance = 480;
int millisecondsHold = 3000;

// Pan / Tilt
int panOffset = 0;
int tiltOffset = 0;
int tiltAngle = 90;
int panAngle = 90;

int tiltMax = 90;
int tiltMin = 90;
int panMaxRightEye = 90;
int panMinLeftEye = 90;
int settle = 3000;

float x;
float y;

bool aimCam() {
  do {
    x = analogRead(X_pin);
    if (x > 900) {
      panOffset += 1;
    }
    if (x < 100) {
      panOffset -= 1;
    }
    pan.write(panAngle + panOffset);

    y = analogRead(Y_pin);
    if (y > 900) {
      tiltOffset -= 1;
    }
    if (y < 100) {
      tiltOffset += 1;
    }
    tilt.write(tiltAngle + tiltOffset);
    delay(50);

  }  while (digitalRead(SW_pin) == 1);
  tiltAngle += tiltOffset;
  panMaxRightEye -= panOffset;
  panMinLeftEye  += panOffset;
  return;
}

void setup() {
  // Enable the push button
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  pan.attach(9);  // attaches the servo on pin 9 to the servo object
  tilt.attach(10);

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.runToNewPosition(0);

  Serial.begin(9600);
  Serial.println("\n=========\nBegin session\n");

  aimCam();

}

void loop() {
  // Point the camera for left eye
  Serial.println("\nPoint the camera for the left eye");
  Serial.print("   Tilt to "); Serial.println(tiltMax);
  tilt.write(tiltMax);
  Serial.print("   Pan to "); Serial.println(panMinLeftEye);
  pan.write(panMinLeftEye);

  // Move the camera into position for the left eye
  Serial.println("Move into position for 1st eye");
  stepper1.runToNewPosition(distance); // blocking function
  delay(millisecondsHold);

  // Take first picture
  Serial.println("Take the left eye picture");
  delay(settle);

  // Point the camera for the right eye
  Serial.println("\nPoint the camera for the right eye");
  Serial.print("   Tilt to "); Serial.println(tiltMin);
  tilt.write(tiltMin);
  Serial.print("   Pan to "); Serial.println(panMaxRightEye);
  pan.write(panMaxRightEye);

  Serial.println("Move into position for right eye");
  stepper1.runToNewPosition(-distance);
  delay(millisecondsHold);

  // Take the second picture
  Serial.println("Take the right eye picture");
  delay(settle);
}
