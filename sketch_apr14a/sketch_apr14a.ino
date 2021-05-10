// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define some steppers and the pins the will use
int IN11 = 2;
int IN21 = 3;
int IN31 = 4;
int IN41 = 5;

int IN12 = 7;
int IN22 = 8;
int IN32 = 9;
int IN42 = 10;

//AccelStepper stepper1(AccelStepper::FULL4WIRE, 2, 4, 3, 5);  // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper1(AccelStepper::FULL4WIRE, IN11, IN31, IN21, IN41);  // UNL Stepper Driver sequence
// AccelStepper stepper2(AccelStepper::FULL4WIRE, IN12, IN32, IN22, IN42);  // UNL Stepper Driver sequence
//AccelStepper stepper2(AccelStepper::FULL4WIRE, 2, 4, 3, 5);
//AccelStepper stepper3(AccelStepper::FULL2WIRE, 10, 11);

String inputBuffer = "";
String direction = "";

int pos = 1024;
int steps = 1024;

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(300.0);
  stepper1.setAcceleration(100.0);
  stepper1.moveTo(pos);
  Serial.println("Begin");
}

void loop() {
//  while (Serial.available() > 0) {
//    inputBuffer = Serial.readString();
//    Serial.println(inputBuffer);
//    if (inputBuffer.startsWith("l")) {
//      direction = "CCW";
//      steps = steps / 2;
//      pos = pos - steps;
//    }
//    if (inputBuffer.startsWith("r")) {
//      direction = "CW";
//      steps = steps / 2;
//      pos = pos + steps;
//    }
//    Serial.print("Move ");
//    Serial.print(steps);
//    Serial.print(" steps ");
//    Serial.print(direction);
//    Serial.print(" to ");
//    Serial.print(pos);
//    Serial.println("");
//    stepper1.moveTo(pos);
//  }
  Serial.print("Distance to go ");
  Serial.print(stepper1.distanceToGo());
  Serial.println("");
  if (stepper1.distanceToGo() == 0) {
      stepper1.moveTo(-stepper1.currentPosition());
      Serial.println("Change direction");
  }
    stepper1.run();
  //  stepper1.move(1000);
  //  stepper1.run();

  // stepper1.moveTo(100);
  // stepper1.run();
  // stepper2.run();
  // stepper3.run();
}
