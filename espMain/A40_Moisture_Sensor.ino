#define MOISTURE_SENSOR 39

int HandleMoisture() {
  return analogRead(MOISTURE_SENSOR);
}