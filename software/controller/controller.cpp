/*
  controller.cpp - Library for Controlling the E-Throttle.
  Created by Jacob M. Wheelock, November 13, 2022.
*/


#include "Arduino.h"
#include "controller.h"

// Constructor for controller Object
controller::controller()
{
  percentOpen = 0.0; error = 0.0;
  P = 1; I = 1;
  pState = 0.0; iState = 0.0;
  pTerm = 0.0; iTerm = 0.0;
  ref = 0.0; pedal = 0.0;
  hold = false; manual = true;


  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(holdPin, OUTPUT);
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(holdPin, LOW);
  pinMode(throttleRead, INPUT);
  pinMode(accelPin, INPUT);
}

void controller::readVelocity() {
  token[0] = Serial.read();
  token[1] = Serial.read();
  token[2] = Serial.read();
  token[3] = Serial.read();

  if (token[0] == 0xFF && token[1] == 0xFF && token[2] == 0xFF && token[3] == 0xFF) {
    velIn[0] = Serial.read();
    velIn[1] = Serial.read();
    velIn[2] = Serial.read();
    velIn[3] = Serial.read();
    velInt = (velIn[0]) | (velIn[1] << 8) | (velIn[2] << 16) | (velIn[3] << 24);
    velFloat = (float) velInt / 1000.0;
    
  }
}

void controller::readAccel() {
  pedal = max(0, min(((countToVolt(analogRead(accelPin)) - 0.03) / 0.5) * 20.0, 100));
}

float controller::readPercentOpen() {
  return max(0, min((85.0 - ((((float)analogRead(throttleRead) * conversion) - 0.91) / 0.0381)), 100));
}

float controller::countToVolt(int count) {
  return (float) count * conversion;
}

void controller::driveForward() {
  digitalWrite(holdPin, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(forward, HIGH);
}

void controller::driveBackward() {
  digitalWrite(holdPin, LOW);
  digitalWrite(forward, LOW);
  digitalWrite(backward, HIGH);
}

void controller::holdIt() {
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
  digitalWrite(holdPin, HIGH);
}

void controller::zero() {
  digitalWrite(backward, LOW);
  digitalWrite(forward, LOW);
  digitalWrite(holdPin, LOW);
}

void controller::setPID() {
  pState = error;
  iState += error;
  pTerm = P * pState;
  iTerm = I * iState;
}
