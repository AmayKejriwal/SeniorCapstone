const int forward = 12;
const int backward = 11;
const int reader = A1;
const int accelPin = A3;
bool onOff = false;
float potVoltage = 0;
const float conversion = 5.0 / 1024.0;
float percentOpen = 0;

unsigned long t0 = 0;
unsigned long t1 = 0;
int sampleTime = 1;

float ref = 0;
bool hold = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  pinMode(reader, INPUT);
  pinMode(accelPin, INPUT);
}

void loop() {
  ref = analogRead(accelPin) / 10.24;
  potVoltage = countToVolt(analogRead(reader));
  percentOpen = voltsToPercent(potVoltage);
  Serial.println(percentOpen);
  

  if (millis() >= t0) {
    t0 = t0 + sampleTime;
    hold = (abs(ref - percentOpen) < 2.0);
    if (percentOpen <= ref && hold == false) {
      digitalWrite(backward, LOW);
      digitalWrite(forward, HIGH);

    }
    else if (percentOpen >= ref && hold == false) {
      digitalWrite(forward, LOW);
      digitalWrite(backward, HIGH);
    }
    else {
      
      digitalWrite(backward, LOW);
      digitalWrite(forward, LOW);
      delay(1);
      digitalWrite(forward, HIGH);
      delay(1);
     
      Serial.println("OFF");
    }
  }
}

float countToVolt(int count) {
  return (float) count * conversion;
}

float voltsToPercent(float volts) {
  return ((volts - 0.91) / 0.0381);
}
