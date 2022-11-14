volatile byte revs;                                                       // Revolutions in a time period
float revsPerMilli;                                                       // Revs in a 1 ms period
float velocity;                                                           // Current Speed
int sensePin = 2;                                                         // Pin attached to sensor


const float R = 0.2286;                                                   // Radius of Wheel (meters)                        
const int countPerRev = 20;                                               // Number of Teeth on Wheel
const float wheelCirc = 2*PI*R;                                           // Circumference of Wheel
const float vConstant = wheelCirc * 1000.0 * wheelCirc * 3.28 * 3600 / 5280.0; // MPH


unsigned long timeOld;                                                    // Timing Counter
int velocitySend;

void setup() {
  Serial.begin(115200);
  pinMode(sensePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensePin), revInc, RISING);       // Run revInc() routine on rising edge of pulse
  revs = 0;
  revsPerMilli = 0;
  timeOld = millis();

}

void loop() {
  if (millis() >= timeOld + 10) {
    float timeCount = millis() - timeOld;
    revsPerMilli = ((float)revs/(float)countPerRev)/timeCount;
    velocity = revsPerMilli * vConstant;
    velocitySend = velocity * 1000;
    timeOld = millis();
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(0xFF);
    Serial.write(lowByte(velocitySend & 0x000000FF));
    Serial.write(lowByte((velocitySend >> 8) & 0x000000FF));
    Serial.write(lowByte((velocitySend >> 16) & 0x000000FF));
    Serial.write(lowByte((velocitySend >> 24) & 0x000000FF));
    revs = 0;
  }
  
  
}

void revInc() {
  revs++;
}
