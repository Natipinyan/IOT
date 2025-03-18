#define DHT_PIN 16
#define DHTTYPE DHT22

DHT dhtSene(DHT_PIN, DHTTYPE);

void TempSetup() {
  dhtSene.begin();
}


float ReadTemp() {
  float temp =  dhtSene.readTemperature();
  Serial.println(temp);
  return(temp);
}

void irrigation(int duration){

}