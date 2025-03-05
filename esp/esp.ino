#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
// ייבוא ספריות

#define TEMP_SENSOR_PIN A0
#define MOISTURE_SENSOR_PIN A1
#define PUMP_PIN D5
//הגדרת פינים

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverUrl = "http://your-server.com/getData";
// משתנים גלובליים לרשת

WiFiClient client;
HTTPClient http;
// משתני רשת
enum PumpMode { TEMP_MODE, SOIL_MOISTURE_MODE, SABBATH_MODE, MANUAL_MODE };
PumpMode currentMode = TEMP_MODE;
// הגדרת מצבי עבודה ואתחול למצב טמפרטורה

struct Settings {
    float desiredTemp;
    int highTempDuration;
    int lowTempDuration;
    int desiredMoisture;
    int shabbatStart;
    int shabbatEnd;
    int irrigationDuration;
    bool manualCommand;
};
Settings settings;
// קבלת הנתונים מהשרת

void fetchData() {
    http.begin(client, serverUrl);
    int httpCode = http.GET();
    if (httpCode > 0) {
        String payload = http.getString();
        StaticJsonDocument<256> doc;
        deserializeJson(doc, payload);
        settings.desiredTemp = doc["desiredTemp"];
        settings.highTempDuration = doc["highTempDuration"];
        settings.lowTempDuration = doc["lowTempDuration"];
        settings.desiredMoisture = doc["desiredMoisture"];
        settings.shabbatStart = doc["shabbatStart"];
        settings.shabbatEnd = doc["shabbatEnd"];
        settings.irrigationDuration = doc["irrigationDuration"];
        settings.manualCommand = doc["manualCommand"];
    }
    http.end();
}
//ייבוא הנתונים מהשרת


void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
    pinMode(PUMP_PIN, OUTPUT);
}
//הפעלת והגדרת התכנית

void handleTempMode() {
    int temp = analogRead(TEMP_SENSOR_PIN);
    int wateringTime = (temp > settings.desiredTemp) ? settings.highTempDuration : settings.lowTempDuration;
    digitalWrite(PUMP_PIN, HIGH);
    delay(wateringTime * 60000);
    digitalWrite(PUMP_PIN, LOW);
}
//מצב טמפרטורה

void handleSoilMoistureMode() {
    int moisture = analogRead(MOISTURE_SENSOR_PIN);
    int lowerBound = settings.desiredMoisture - 10;
    int upperBound = settings.desiredMoisture + 10;
    if (moisture < lowerBound || moisture > upperBound) {
        digitalWrite(PUMP_PIN, HIGH);
        delay(60000);
        digitalWrite(PUMP_PIN, LOW);
    }
}
//מצב לחות קרקע

void handleShabbatMode() {
    int currentHour = hour(); // Assuming time is retrieved from an RTC module
    if (currentHour >= settings.shabbatStart && currentHour < settings.shabbatEnd) {
        digitalWrite(PUMP_PIN, HIGH);
        delay(settings.irrigationDuration * 60000);
        digitalWrite(PUMP_PIN, LOW);
    }
}
//מצב שבת

void handleManualMode() {
    if (settings.manualCommand) {
        delay(3000);
        digitalWrite(PUMP_PIN, HIGH);
        delay(settings.irrigationDuration * 60000);
        digitalWrite(PUMP_PIN, LOW);
    }
}
//מצב ידני

void loop() {
    fetchData();
    switch (currentMode) {
        case TEMP_MODE:
            handleTempMode();
            break;
        case SOIL_MOISTURE_MODE:
            handleSoilMoistureMode();
            break;
        case SABBATH_MODE:
            handleShabbatMode();
            break;
        case MANUAL_MODE:
            handleManualMode();
            break;
    }
    delay(60000);
}
