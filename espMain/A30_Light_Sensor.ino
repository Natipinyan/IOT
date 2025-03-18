#define LIGHT_SENSOR 36

int GetLight() {
  return map(analogRead(LIGHT_SENSOR), 0, 4095, 0, 100);
}
