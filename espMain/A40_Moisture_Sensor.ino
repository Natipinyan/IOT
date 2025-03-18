#define MOISTURE_SENSOR 39

float HandleMoisture() {
  return analogRead(MOISTURE_SENSOR);
}