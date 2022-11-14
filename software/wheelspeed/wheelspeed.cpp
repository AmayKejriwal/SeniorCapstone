/*
  wheelspeed.cpp - Library for Controlling Wheelspeed Arduino.
  Created by Jacob M. Wheelock, November 13, 2022.
*/


#include "Arduino.h"
#include "wheelspeed.h"

// Constructor for wheelspeed Object
wheelspeed::wheelspeed()
{
  pinMode(sensePin, INPUT_PULLUP);                                    // Unit 1 SS Pin: Output Mode
 
}

void wheelspeed::writeVelocity(int velocitySend) {
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(0xFF);
  Serial.write(lowByte(velocitySend & 0x000000FF));
  Serial.write(lowByte((velocitySend >> 8) & 0x000000FF));
  Serial.write(lowByte((velocitySend >> 16) & 0x000000FF));
  Serial.write(lowByte((velocitySend >> 24) & 0x000000FF));
}

float wheelspeed::getRevsPerMilli(volatile byte revs, unsigned long timeCount) {
  return (((float) revs / (float) countPerRev)/ (float)timeCount);
}
