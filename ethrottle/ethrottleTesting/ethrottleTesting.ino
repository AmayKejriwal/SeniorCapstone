const int forward = 12;
const int backward = 11;
const int holdPin = 10;
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

const float freq = 800;
const float cycle = 65.0 / 100.0;
const float hd = (cycle/freq) * pow(10,3);
const float ld = ((1-cycle)/freq) * pow(10,3);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
  pinMode(holdPin, OUTPUT);
  digitalWrite(forward, LOW);
  digitalWrite(backward, LOW);
  digitalWrite(holdPin, LOW);
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
      digitalWrite(holdPin, LOW);
      digitalWrite(backward, LOW);
      digitalWrite(forward, HIGH);
      Serial.println("OPEN!!!");

    }
    else if (percentOpen >= ref && hold == false) {
      digitalWrite(holdPin,LOW);
      digitalWrite(forward, LOW);
      digitalWrite(backward, HIGH);
    }
    else {
      
      digitalWrite(backward, LOW);
      digitalWrite(forward, LOW);
      digitalWrite(holdPin, HIGH);
     
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
