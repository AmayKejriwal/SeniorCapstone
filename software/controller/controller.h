/*
  controller.h - Library for Controlling the E-Throttle.
  Created by Jacob M. Wheelock, November 13, 2022.
*/
#ifndef controller_h
#define controller_h

#include "Arduino.h"

class controller
{
  public:
    // Constructor
    controller();

    // Stimulator Methods
    void readVelocity();
    void readAccel();   
    float readPercentOpen();
    float countToVolt(int count);   
    void driveForward();
    void driveBackward();
    void holdIt();
    void setPID();       
    void zero();                             

    // Global Variables
    const int forward = 12;
    const int backward = 11;
    const int holdPin = 10;
    const int throttleRead = A0;
    const int accelPin = A1;
    const float conversion = 5.0/1024.0;
    float percentOpen, error, P, I, pState, iState, pTerm, iTerm, ref, velFloat, pedal;
    unsigned long t0, currentTime;
    bool manual, hold;
    int token[4], velIn[4], velInt;


};

#endif
