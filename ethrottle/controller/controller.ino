typedef union
{
  float number;
  uint8_t bytes[4];
}FLOATUNION_t;

float error;
float P, I;
float pState, iState = 0;
float pTerm, iTerm = 0;
FLOATUNION_t out;

void setup() {
  Serial.begin(115200);
}

void loop() {
  while (Serial.available() > 0) {
    error = Serial.parseFloat();
    pState = P;
    iState += error;
    pTerm = P * pState;
    iTerm = I * iState;
    out.number = pTerm + iTerm;
    if (out.number > 100.0) out.number = 100.0;
    else if (out.number < 0) out.number = 0.0;
    Serial.write(out.bytes, 4);
  }

}
