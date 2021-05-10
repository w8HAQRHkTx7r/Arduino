/* 
 *  Stereo photography rig
 *  ======================
 *  Control a linear acctuator
 *  Control a pan/tilt
*/

#include <Servo.h>
#include <AccelStepper.h>

Servo pan;  // create servo object to control a servo
Servo tilt;

// Define some steppers and the pins the will use
int IN11 = 2;
int IN21 = 3;
int IN31 = 4;
int IN41 = 5;

AccelStepper stepper1(AccelStepper::FULL4WIRE, IN11, IN31, IN21, IN41);  // UNL Stepper Driver sequence

// Linear acctuator
String inputBuffer = "";
bool stringComplete = false;
int pos = 0;
String direction = "";
int distance = 510
;
int millisecondsHold = 3000;

// Pan / Tilt
int tiltMax = 88;
int tiltMin = 88;
int panMaxRightEye = 92;
int panMinLeftEye = 88;
int settle = 3000;


void setup() {
  pan.attach(9);  // attaches the servo on pin 9 to the servo object
  tilt.attach(10);

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.runToNewPosition(0);
  
  Serial.begin(9600);
  Serial.println("\n=========\nBegin session\n");

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
