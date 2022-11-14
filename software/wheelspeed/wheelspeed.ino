#include "wheelspeed.h"
wheelspeed sensor = wheelspeed();
volatile byte revs = 0;

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(sensor.sensePin), revInc, RISING);   // Run revInc() routine on rising edge of pulse
  
  sensor.timeOld = millis();
}

void loop() {
  if (millis() >= sensor.timeOld + 10) {
    sensor.timeCount = millis() - sensor.timeOld;
    sensor.revsPerMilli = sensor.getRevsPerMilli(revs, sensor.timeCount);
    sensor.velocity = sensor.revsPerMilli * sensor.vConstant;
    sensor.velocitySend = sensor.velocity * 1000;
    sensor.writeVelocity(sensor.velocitySend);
    revs = 0;
    sensor.timeOld = millis();
  }

}

void revInc() {
  revs++;
}
