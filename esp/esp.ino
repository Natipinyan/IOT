#include <DHT.h>

#define dhtPin 16
#define DHTTYPE DHT11
DHT dht(dhtPin, DHTTYPE);

#define lightSensor 36
#define MoistureSensor 39

// משתני מצב
enum PumpState { TEMP_CONTROL, MOISTURE_CONTROL, SHABBAT, MANUAL };
PumpState currentState = MANUAL;

// משתנים למצב טמפרטורה
float desiredTemp = 25.0; // טמפרטורה רצויה
int highTempDuration = 10; // זמן השקיה במעלות גבוהות (בדקות)
int lowTempDuration = 5;   // זמן השקיה במעלות נמוכות (בדקות)

// משתנים למצב לחות
float desiredMoisture = 500; // ערך לחות רצויה
float moistureTolerance = 50; // סבילות ±10%

// משתנים למצב שבת
int shabbatStartHour = 18;
int shabbatStopHour = 22;

// משתנה למצב ידני
bool manualPumpOn = false;

// משתנים כלליים
unsigned long pumpStartTime = 0;
bool isPumpRunning = false;

// פונקציה להפעלת משאבה
void controlPump(bool turnOn) {
  if (turnOn) {
    if (!isPumpRunning) {
      Serial.println("Pump turned ON");
      isPumpRunning = true;
      pumpStartTime = millis();
    }
  } else {
    if (isPumpRunning) {
      Serial.println("Pump turned OFF");
      isPumpRunning = false;
    }
  }
}

// פונקציה לניהול מצבים
void handleState(float temp, int moisture) {
  switch (currentState) {
    case TEMP_CONTROL: {
      int duration = (temp > desiredTemp) ? highTempDuration : lowTempDuration;
      if (millis() - pumpStartTime >= duration * 60000) {
        controlPump(false);
      } else {
        controlPump(true);
      }
      break;
    }
    case MOISTURE_CONTROL:
      if (moisture < desiredMoisture - moistureTolerance || moisture > desiredMoisture + moistureTolerance) {
        controlPump(true);
      } else {
        controlPump(false);
      }
      break;
    case SHABBAT: {
      struct tm timeinfo;
      if (getLocalTime(&timeinfo)) {
        int hour = timeinfo.tm_hour;
        if (hour >= shabbatStartHour && hour < shabbatStopHour) {
          controlPump(true);
        } else {
          controlPump(false);
        }
      }
      break;
    }
    case MANUAL:
      if (manualPumpOn) {
        controlPump(true);
      } else {
        controlPump(false);
      }
      break;
  }
}

void setup() {
  Serial.begin(115200);
  WiFi_SETUP(); // פונקציה קיימת שלא משנים
  dht.begin();
}

void loop() {
  // קריאת חיישנים
  int light = analogRead(lightSensor);
  int moisture = analogRead(MoistureSensor);
  float temp = dht.readTemperature();

  // שליחת נתונים לשרת
  sendData(temp, light, moisture); // פונקציה קיימת שלא משנים

  // ניהול מצב המשאבה
  handleState(temp, moisture);

  delay(500);
}