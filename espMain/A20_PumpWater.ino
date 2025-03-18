#define WATER_PUMP 15

void waterPumpSetup(){
  pinMode(WATER_PUMP, OUTPUT);
  digitalWrite(WATER_PUMP, LOW);
}