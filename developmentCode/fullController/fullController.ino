const int forward = 12; const int backward = 11; const int holdPin = 10;
const int throttleRead = A0; const int accelPin = A1;
const float conversion = 5 / 1024.0;
float potVoltage = 0;
float percentOpen = 0;
float error = 5.0;
float P = 1; float I = 1;
float pState, iState = 0;
float pTerm, iTerm = 0;

float test = 0;

unsigned long t0 = 0;
int sampleTime = 1;

float ref = 0;
float pedal = 0;
bool hold = false;
//bool manual = false;

int token[4];
int velIn[4];
int velInt;
float velFloat = 5.0;
float testError = 10.0;
bool manual = true;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(holdPin, OUTPUT);
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(holdPin, LOW);
  pinMode(throttleRead, INPUT);
  pinMode(accelPin, INPUT);
}

void loop() {
  pedal = max(0,min(((countToVolt(analogRead(accelPin)) - 0.03) / 0.5) * 20.0, 100));
  if (Serial.available() > 7) {
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
      error = testError - velFloat;
    }
  }

  pState = error;
  iState += error;
  pTerm = P * pState;
  iTerm = I * iState;
  ref = pTerm + iTerm;
  

  if (velFloat > 10.0 && manual == true) {
    manual = false;
  }
  ref = pedal;
  if (manual == false) {
    ref = pTerm + iTerm;
    ref = max(0, min(100.0, ref));
  }

  percentOpen = 90.0 - countToPercent(analogRead(throttleRead));

  // Serial.println(percentOpen);
  // Serial.println(velFloat);

  if (millis() >= t0) {
    t0 = t0 + sampleTime;
    hold = (abs(ref - percentOpen) < 10.0);
    if (percentOpen <= ref && hold == false) {
                  digitalWrite(holdPin, LOW);
                  digitalWrite(backward, LOW);
                  digitalWrite(forward, HIGH);
     //            Serial.println("FWD");
    }
    else if (percentOpen >= ref && hold == false) {
                  digitalWrite(holdPin, LOW);
                  digitalWrite(forward, LOW);
                  digitalWrite(backward, HIGH);
   //    Serial.println("BACK");
    }
    else {
                  digitalWrite(backward, LOW);
                  digitalWrite(forward, LOW);
                  digitalWrite(holdPin, HIGH);
     //   Serial.println("HOLD");
    }
  }
}

float countToVolt(int count) {
  return (float) count * conversion;
}

float voltsToPercent(float volts) {
  return ((volts - 0.91) / 0.0381);
}

float countToPercent(int count) {
  return ((((float)count * conversion) - 0.91) / 0.0381);
}
