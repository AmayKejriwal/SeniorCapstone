#include "controller.h"
controller cont = controller();
float desiredSpeed = 10.0;
int sampleTime = 1;

void setup() {
  Serial.begin(115200);
  cont.t0 = millis();
  cont.velFloat = 5.0;
  cont.manual = true;
}

void loop() {
  cont.readAccel();
  cont.percentOpen = cont.readPercentOpen();

  if (Serial.available() > 7) {
    cont.readVelocity();
    cont.error = desiredSpeed - cont.velFloat;
    cont.setPID();
  }

  if (cont.manual == true) {
    cont.ref = cont.pedal;
  }
  else {
    cont.ref = max(0, min(100, cont.pTerm + cont.iTerm));
  }
  

  if (millis() >= cont.t0) {
    cont.t0 = cont.t0 + sampleTime;
    cont.hold = (abs(cont.ref - cont.percentOpen) < 5.0);
    if (cont.percentOpen <= cont.ref && cont.hold == false) {
      cont.driveForward();
    }
    else if (cont.percentOpen >= cont.ref && cont.hold == false) {
      cont.driveBackward();
    }
    else {
      if (cont.ref > 5.0) {
        cont.holdIt();
      }
      else {
        cont.zero();
      }
    }
  }


}
