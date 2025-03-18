#define WATER_PUMP 15
bool isStart;
unsigned long irrigationTimeStart;

void waterPumpSetup(){
  pinMode(WATER_PUMP, OUTPUT);
  digitalWrite(WATER_PUMP, LOW);
  isStart = false;
  irrigationTimeStart = millis();
}

int irrigation(int duration) {
  int res = 0;
  if (!isStart) {
    isStart = true;
    irrigationTimeStart = millis();
  }
  if (millis() - irrigationTimeStart < (duration * 60 * 1000))
    digitalWrite(WATER_PUMP, HIGH);
  else {
    digitalWrite(WATER_PUMP, LOW);
    isStart = false;
    res = 1;
  }
  return res;
}

void pumpOn() {
  digitalWrite(WATER_PUMP, HIGH);
}
void pumpOff() {
  digitalWrite(WATER_PUMP, LOW);
}