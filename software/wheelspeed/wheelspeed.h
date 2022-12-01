/*
  wheelSpeed.h - Library for Wheel Speed Sensor.
  Created by Jacob M. Wheelock, November 13, 2022.
*/
#ifndef wheelspeed_h
#define wheelspeed_h

#include "Arduino.h"

class wheelspeed
{
  public:
    // Constructor
    wheelspeed();

    // Sensor Methods
    void revInc();                                                           // Method for Incrementing Tooth Counter
    void writeVelocity(int velocity);                                        // Method for Sending Velocity
    float getRevsPerMilli(volatile byte revs, unsigned long timeCount);      // Method for Calculating Revs Per Millisecond

    // Global Variables
    float revsPerMilli, velocity;
    unsigned long timeOld, timeCount;
    const float R = 9; 
    const float wheelCirc = 2 * PI * R; 
    const float vConstant = 1000.0 * 60.0 * 60.0 * wheelCirc / (12.0 * 5280.0);
    const int countPerRev = 20; const int sensePin = 2;
    int velocitySend;

};

#endif
