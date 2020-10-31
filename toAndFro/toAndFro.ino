#include <Stepper.h>

#define clockwise 1
#define counterclockwise -1

// Global variables to support CSV processing from Serial
const byte buffSize = 32;
char inputSeveral[buffSize];
byte maxChars = 25;

int loopCnt = 0;

float azimuth = 0.0;
float altitude = 0.0;
float stepsPerDegree;
float currentAzimuth = 0.0;
float currentAltitude = 0.0;

char LorR = "";

// stepsPerRevolution controls how far the spindle rotates
// I.e., 2048 is 360 deg. and 1024 is 180 deg.
// Positive is clockwise, negative is counterclockwise
// change this to fit the number of steps per revolution
const int stepsPerRevolution = 2048;

// Adjustable range of 28BYJ-48 stepper is 0~17 rpm
const int RevolutionsPerMinute = 3;

// The order of this pins is important.  I've seen examples where the
// pins were listed as 8,9,10,11 and that failed.
Stepper azimuthStepper(stepsPerRevolution, 8, 10, 9, 11);
Stepper altitudeStepper(stepsPerRevolution, 2, 4, 3, 5);

int direction = clockwise;

void off(int p1, int p2, int p3, int p4) {
  digitalWrite(p1, LOW);
  digitalWrite(p2, LOW);
  digitalWrite(p3, LOW);
  digitalWrite(p4, LOW);
}
float promptAndGetFloat(char* prompt) {
  Serial.println(prompt);
  while (!Serial.available()) {}
  if (Serial.available()) {
    return Serial.parseFloat();
  }
}
int promptAndGetInt(char* prompt) {
  Serial.println(prompt);
  while (!Serial.available()) {}
  if (Serial.available()) {
    return Serial.parseInt();
  }
}
char promptAndGetChar(char* prompt) {
  Serial.println(prompt);
  while (!Serial.available()) {}
  if (Serial.available()) {
    return Serial.read();
  }
}
void getAzimuthAltitude() {
  String inputString;
  String az;
  String al;

  Serial.flush();
  Serial.println("Enter az, al");

  while (!Serial.available()) {}

  inputString = Serial.readString();
  int comma = inputString.indexOf(',');
  int space = inputString.indexOf(' ');

  if (comma < 0 && (space > 0)) {
    // There is no comma, but there is a space
    // Use the space as a delimiter
    comma = space;
  }

  if (comma > 0 && inputString.length() > comma) {
    az = inputString.substring(0, comma);
    azimuth = az.toFloat();
    al = inputString.substring(comma + 1);
    altitude = al.toFloat();
  }
  Serial.flush();
}
void logFloat(char* label, float value) {
  Serial.print(label);
  Serial.println(value);
}
void logInt(char* label, int value) {
  Serial.print(label);
  Serial.println(value);
}
void logChar(char* label, char value) {
  Serial.print(label);
  Serial.println(value);
}
bool calibrate(Stepper motor) {
  // This does a binary search for the zero point on the compass
  int currentHeading = 180;
  int direction = 1;

  while (true) {
    Serial.flush();
    Serial.print("Adjustment angle:"); Serial.println(currentHeading);
    LorR = promptAndGetChar("Move L R ,(<) .(>) Q?");
    LorR = toLowerCase(LorR);
    switch (LorR) {
      case 'l':
        direction = counterclockwise;
        break;
      case 'r':
        direction = clockwise;
        break;
      case 'q':
        Serial.println("You're at zero");
        Serial.flush();
        return true;
        break;
      case '.':
        motor.step(clockwise * 1);
        direction = 0;
        break;
      case ',':
        motor.step(counterclockwise * 1);
        direction = 0;
        break;
      default:
        Serial.println("You must enter L,R or Q");
        break;
    }
    motor.step(direction * currentHeading * stepsPerDegree);
    currentHeading /= 2;
  }
  return false;
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
  Serial.flush();
  Serial.println("\nStart program! v1");
  stepsPerDegree = stepsPerRevolution / 360.0;
  azimuthStepper.setSpeed(RevolutionsPerMinute);
  altitudeStepper.setSpeed(RevolutionsPerMinute);
  Serial.println("Calibrate azimuth");
//  calibrate(azimuthStepper);
  off(8, 9, 10, 11);
  Serial.println("Calibrate altitude");
//  calibrate(altitudeStepper);
  off(2, 3, 4, 5);

  
}
void loop() {
  //  ++loopCnt;
  //  logInt("Loop Count",loopCnt);
//  getAzimuthAltitude();
  direction *= -1;

  if (direction == clockwise) {
    azimuth = 45.0;
    altitude = 45.0;
  }
  if (direction == counterclockwise) {
    azimuth = 0.0;
    altitude = 0.0;
  }
  
  //  azimuth = promptAndGetFloat("Enter azimuth");
  //  altitude = promptAndGetFloat("Enter altitude");

  Serial.print("AZ:"); Serial.print(azimuth);
  Serial.print("  AL:"); Serial.println(altitude);
  if (azimuth < 0.0) {
    azimuth = 0.0;
  }
  if (azimuth > 360) {
    azimuth = 360.0;  
  }
  
  float additionalSteps = azimuth - currentAzimuth;
  int stepsToTake = (additionalSteps) * stepsPerDegree;
  azimuthStepper.step(stepsToTake);
  azimuthStepper.step(0);
  off(8, 9, 10, 11); // kill azimuth stepper signals
  currentAzimuth = azimuth;

  if (altitude <  0.0) {
    altitude =  0.0;
  }
  if (altitude > 90.0) {
    altitude = 90.0;
  }

  additionalSteps = altitude - currentAltitude;
  stepsToTake = (additionalSteps) * stepsPerDegree;
  altitudeStepper.step(stepsToTake);
  altitudeStepper.step(0);
  off(2, 3, 4, 5); // kill altitude stepper signals
  currentAltitude = altitude;

  delay(1000);
}
