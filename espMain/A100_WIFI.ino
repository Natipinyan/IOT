#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

const char* ssid = "Nati";
const char* password = "12345678";
const char* ipAddres = "192.168.116.216";
const char* port = "3000";

WiFiClient client;

void WiFi_SETUP(){
  Serial.begin(9600);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


String GetState() {
    String ret = "-1";
    HTTPClient http;
    http.begin(client, "http://" + String(ipAddres) + ":" + String(port) + "/esp/state");
    int httpCode = http.GET();
    Serial.println(httpCode);
    if (httpCode == HTTP_CODE_OK) {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      String Res = http.getString();
      Serial.println(Res);
      ret = Res;
    }
    http.end();

    return ret;
}

String getDataMode(String state){
  String json = "";
  HTTPClient http;
  http.begin(client, "http://" + String(ipAddres) + ":" + String(port) + "/esp/dataMode?state="+state);
  int httpCode = http.GET();
  Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    Serial.print("HTTP response code ");
    Serial.println(httpCode);
    json = http.getString();
  }
    http.end();
        
    return json;
}
