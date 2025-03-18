#define WATER_PUMP 15

void waterPumpSetup(){
  pinMode(WATER_PUMP, OUTPUT);
  digitalWrite(WATER_PUMP, LOW);
}

int irrigation(int duration) {
  int res = 0;
  if (!isStart) {
    isStart = true;
    irigationTimeStart = millis();
  }
  if (millis() - irigationTimeStart < (duration * 60 * 1000))
    digitalWrite(WATER_PUMP_PIN, HIGH);
  else {
    digitalWrite(WATER_PUMP_PIN, LOW);
    isStart = false;
    res = 1;
  }
  return res;
}

void pumpOn() {
  digitalWrite(WATER_PUMP_PIN, HIGH);
}
void pumpOff() {
  digitalWrite(WATER_PUMP_PIN, LOW);
}