volatile byte revs;                                                       // Revolutions in a time period
unsigned int revsPerMilli;                                                // Revs in a 1 ms period
float velocity;                                                           // Current Speed
int sensePin = 1;                                                         // Pin attached to sensor


const float R = 5;                                                        // Radius of Wheel (meters)                        
const int countPerRev = 20;                                               // Number of Teeth on Wheel
const float wheelCirc = 2*PI*R;                                           // Circumference of Wheel
const float vConstant = wheelCirc * 3600.0;
// velocity = revsPerMilli * wheelCirc * "milliseconds per hour" / "meters per kilometer"
// velocity = rpmilli * WHEELCIRC * 3600000 / 1000
// velocity = rpmilli * WHEELCIRC * 3600

unsigned long timeOld;                                                    // Timing Counter
    

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(sensePin), revInc, RISING);       // Run revInc() routine on rising edge of pulse
  revs = 0;
  revsPerMilli = 0;
  timeOld = 0;

}

void loop() {
  if (revs >= countPerRev) {
    revs = 0;
    revsPerMilli = revs/(millis()-timeOld);
    timeOld = millis();
    velocity = revsPerMilli * vConstant;
  }

}

void revInc() {
  revs++;
}
