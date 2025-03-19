#include <DHT.h>
#include <ArduinoJson.h>

#define TEMP_MODE 80
#define MOISTURE_MODE 81
#define SHABAT_MODE 82
#define MANUAL_MODE 83

// 1. tempMode
// 2. moistureMode
// 3. shabbatMode
// 4. manualMode


int plantID = 1;
int timeCnt = 0;

StaticJsonDocument<200> obj;
unsigned long lastTimeChackedServer;
unsigned long startIrrigation;
unsigned long totalIrrigation;
bool isStartIrrigation = false;
int status;
int irrigationCnt = 0;
String currentTime;
int millisToChackServer;
int ShabatIrrigationCnt = 0;

void setup() {
  millisToChackServer = 1000 * 60 * 10;
  lastTimeChackedServer = millis();
  startIrrigation = 0;
  totalIrrigation = 0;


  status = -1;

  Serial.begin(115200);
  TempSetup();
  waterPumpSetup();
  WiFi_SETUP();
}

void loop() {

  if (millis() - lastTimeChackedServer > millisToChackServer) {
    lastTimeChackedServer = millis();
    String json = GetState();
    if (json != "-1") {
      deserializeJson(obj, json);
      status = obj["state"].as<int>();
      currentTime = obj["date"].as<String>();
    } else {
      status = -1;
      Serial.println("no response!");
    }
    if (timeCnt = 144) {  //the number of tem minutes in a day
      sendData(plantID, totalIrrigation);
      timeCnt = 0;
      totalIrrigation = 0;
    } else {
      timeCnt++;
    }
  }


  switch (status) {
    case TEMP_MODE:
      {
        float currentTemp = ReadTemp();
        String json = getDataMode("TEMP_MODE");
        deserializeJson(obj, json);
        int PreferTemp = obj["preferTemp"];
        int MinTime = obj["minTime"];
        int MaxTime = obj["maxTime"];

        int currentLight = GetLight();
        if (irrigationCnt < 2) {
          if (currentTemp > PreferTemp) {
            if (currentTime > "17:00" || currentTime < "06:00") {
              irrigationCnt += irrigation(MaxTime);
            } else if (currentLight < 40) {
              irrigationCnt += irrigation(MaxTime);
            }
          } else {
            if (currentTime > "17:00" || currentTime < "06:00") {
              irrigationCnt += irrigation(MinTime);
            } else if (currentLight < 40) {
              irrigationCnt += irrigation(MinTime);
            }
          }
        }
        break;
      }


    case MOISTURE_MODE:
      {
        int currentMoist = HandleMoisture();
        String json = getDataMode("MOISTURE_MODE");
        deserializeJson(obj, json);
        float PreferMoisture = obj["moisture"];
        if (currentMoist > PreferMoisture * 1.1) {
          if (isStartIrrigation) {
            totalIrrigation += (millis() - startIrrigation);
            isStartIrrigation = false;
          }
          pumpOff();
        } else if (currentMoist < PreferMoisture * 0.9) {
          if (!isStartIrrigation) {
            startIrrigation = millis();
            isStartIrrigation = true;
          }
          pumpOn();
        }
        break;
      }

    case SHABAT_MODE:
      {
        String json = getDataMode("SHABAT_MODE");
        deserializeJson(obj, json);
        int Duration = obj["duration"];
        String FirtIrrigation = obj["firtIrrigation"];
        String SecondIrrigation = obj["secondIrrigation"];
        if (currentTime >= FirtIrrigation && currentTime <= FirtIrrigation + 10)
          ShabatIrrigationCnt += irrigation(Duration);
        else if (currentTime >= SecondIrrigation && currentTime <= SecondIrrigation + 10)
          ShabatIrrigationCnt += irrigation(Duration);
        break;
      }

    case MANUAL_MODE:
      {
        String json = getDataMode("MANUAL_MODE");
        deserializeJson(obj, json);
        String ManualCommand = obj["command"];
        if (ManualCommand == "ON") {
          if (!isStartIrrigation) {
            startIrrigation = millis();
            isStartIrrigation = true;
            pumpOn();
          } else if (ManualCommand == "OFF") {
            if (isStartIrrigation) {
              totalIrrigation += (millis() - startIrrigation);
              isStartIrrigation = false;
              pumpOff();
            }

            break;
          }
        }
      }
  }
}
