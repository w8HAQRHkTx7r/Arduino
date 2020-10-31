#include <Stepper.h>

#define clockwise 1
#define counterclockwise -1

float stepsPerDegree;

char LorR = "";

// stepsPerRevolution controls how far the spindle rotates
// I.e., 2048 is 360 deg. and 1024 is 180 deg.
// Positive is clockwise, negative is counterclockwise
// change this to fit the number of steps per revolution
const int stepsPerRevolution = 2048;  

// Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int RevolutionsPerMinute = 17;         

// The order of this pins is important.  I've seen examples where the
// pins were listed as 8,9,10,11 and that failed.
Stepper azimuthStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper altitudeStepper(stepsPerRevolution, 2, 4, 3, 5);

void off(int p1, int p2, int p3, int p4) {
  digitalWrite(p1,LOW);
  digitalWrite(p2,LOW);
  digitalWrite(p3,LOW);
  digitalWrite(p4,LOW);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
//  Serial.begin(9600);
//  Serial.println("\nStart program!");
  stepsPerDegree = stepsPerRevolution / 360.0;
  azimuthStepper.setSpeed(RevolutionsPerMinute);
  altitudeStepper.setSpeed(RevolutionsPerMinute);
}

void loop() {
  // put your main code here, to run repeatedly:
  int degrees = 90;
  int stepsToTake = (degrees) * stepsPerDegree;
  azimuthStepper.step(stepsToTake);
  azimuthStepper.step(0);
  off(8,9,0,11);
  delay(1000);
    
  stepsToTake = (degrees) * stepsPerDegree;
  altitudeStepper.step(stepsToTake);
  altitudeStepper.step(0);
  off(2,3,4,5);
  delay(1000);
}
