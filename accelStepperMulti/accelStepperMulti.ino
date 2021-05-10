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
bool stringComplete = false;
int pos = 180;
String direction = "";
int distance = 200;
int millisecondsHold = 8000;

void setup() {
  Serial.begin(9600);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.runToNewPosition(0);
//  stepper1.moveTo(distance);  // steps?

  // stepper2.setMaxSpeed(300.0);
  // stepper2.setAcceleration(100.0);
  // stepper2.moveTo(530);

  // stepper3.setMaxSpeed(300.0);
  // stepper3.setAcceleration(100.0);
  // stepper3.moveTo(1000000);
}

void loop() {
  //  while (Serial.available() > 0) {
  //  Serial.println("Available");
  //  inputBuffer = Serial.readString();
  //  Serial.println(inputBuffer);
  // }
  stepper1.runToNewPosition(distance); // blocking function
  delay(millisecondsHold);
  stepper1.runToNewPosition(-distance);
  delay(millisecondsHold);
  // stepper1.moveTo(-1000);
  // stepper1.run();
  // stepper2.run();
  // stepper3.run();
}
