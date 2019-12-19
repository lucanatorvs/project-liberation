/*
  Elements.ino, Example for the AutoConnect library.
  Copyright (c) 2019, Hieromon Ikasamo
  https://github.com/Hieromon/AutoConnect
  This software is released under the MIT License.
  https://opensource.org/licenses/MIT

  This example demonstrates the typical behavior of AutoConnectElement.
  It also represents a basic structural frame for saving and reusing
  values ​​entered in a custom web page into flash.
*/

#include "src/AutoConnect/AutoConnect.h"
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
using WebServerClass = WebServer;
#include <FS.h>
#include "time.h" // For NTP
#include <HTTPClient.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define PARAM_FILE "/wow_settings.json"

#define uS_TO_S_FACTOR    1000000ULL   // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP     1800         // Time ESP32 will go to sleep (in seconds) 30 min * 60 sec = 1800 sec
#define TIME_BEFORE_RETRY 10           // Time ESP32 will wait before WiFi  connectoin retry

RTC_DATA_ATTR int firstBoot = 1;

static const char PAGE_WOW[] PROGMEM = R"(
{
  "uri": "/wow-settings",
  "title": "WOW Settings",
  "menu": true,
  "element": [
    {
      "name": "text",
      "type": "ACText",
      "value": "<b>Stap 1:</b> Instellingen van MetOffice om de data te kunnen uploaden via de WOW-API",
      "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
    },
    {
      "name": "site_id",
      "type": "ACInput",
      "label": "Site ID",
      "placeholder": "XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX",
      "pattern": "^[a-z0-9]{8}-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{4}-[a-z0-9]{12}$"
    },
    {
      "name": "site_key",
      "type": "ACInput",
      "label": "6-Digit PIN",
      "placeholder": "6 digit site key",
      "pattern": "^[0-9]{6}$"
    },
    {
      "name": "save",
      "type": "ACSubmit",
      "value": "Volgende",
      "uri": "/save"
    }
  ]
}
)";

static const char PAGE_SAVE[] PROGMEM = R"(
{
  "uri": "/save",
  "title": "WOW Settings",
  "menu": false,
  "element": [
    {
      "name": "caption",
      "type": "ACText",
      "value": "<b>Stap 2:</b> Nu dient u te verbinden met een WiFi netwerk. Zodra dit is gebeurd wordt de verbinding (en deze website) automatisch gesloten.",
      "style": "font-family:Arial;font-size:18px;font-weight:400;color:#191970"
    },
    {
      "name": "ok",
      "type": "ACSubmit",
      "value": "Volgende",
      "uri": "/_ac/open"
    }
  ]
}
)";

unsigned long time_now = 0;

// NTP Server
const char* ntpServer = "nl.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;

WebServerClass  server;
AutoConnect portal(server);
AutoConnectConfig config;
AutoConnectAux  wowAux;
AutoConnectAux  saveAux;

String site_id;
String site_key;

float temperature;
float pressure;
float humidity;

struct tm timeinfo;
char timeStringBuff[50]; //50 chars should be enough

Adafruit_BME280 bme; // I2C

void open_portal() {
  // Load a custom web page described in JSON as PAGE_ELEMENT and
  // register a handler. This handler will be invoked from
  // AutoConnectSubmit named the Load defined on the same page.
  wowAux.load(FPSTR(PAGE_WOW));
  wowAux.on([] (AutoConnectAux& aux, PageArgument& arg) {
      SPIFFS.begin(true);
      File param = SPIFFS.open(PARAM_FILE, "r");
      if (param){
        aux.loadElement(param, { "text", "site_id", "site_key" } );
        param.close();
      }
      SPIFFS.end();
    return String();
  });

  saveAux.load(FPSTR(PAGE_SAVE));
  saveAux.on([] (AutoConnectAux& aux, PageArgument& arg) {
    SPIFFS.begin(true);
    File param = SPIFFS.open(PARAM_FILE, "w");
    
    if (param) {
      // Save as a loadable set for parameters.
      wowAux.saveElement(param, { "text", "site_id", "site_key" });
      param.close();
      // Read the saved elements again to display.
      param = SPIFFS.open(PARAM_FILE, "r");
      param.close();
    }
    
    SPIFFS.end();
    return String();
  });

  portal.join({ wowAux, saveAux });
  config.title = "WOW Monitor"; // Menu title
  config.apid = "WOW-MONITOR-" + String((uint32_t)(ESP.getEfuseMac() >> 32), HEX); // SSID
  Serial.println("apid set to: " + config.apid);
  config.immediateStart = true;
  config.portalTimeout = 60000; // Will time out in 1 minute
  config.psk  = ""; // Password
  portal.config(config);
  portal.begin();
  time_now = millis();
  while(millis() < time_now + 1000){
    //keep server alive approx. 1000 ms
    portal.handleClient();
  }
}

void takeMeasurement(){
  bme.takeForcedMeasurement();

  temperature = bme.readTemperature() * 1.8 + 32;
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature() * 1.8 + 32);
  Serial.println(" *F");

  pressure = bme.readPressure() / 3386.0F;
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 3386.0F);
  Serial.println(" inch of mercury");
  
  humidity = bme.readHumidity();
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");
  
  Serial.println();
}

void get_wow_settings(){
  SPIFFS.begin(true);
    File param = SPIFFS.open(PARAM_FILE, "r");
    if (param){
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, param);
      site_id = doc[1]["value"].as<String>();
      Serial.println("Site ID = " + site_id);
      site_key = doc[2]["value"].as<String>();
      Serial.println("Site PIN = " + site_key);
      param.close();
    }
    SPIFFS.end();
}

void sendData() {
  Serial.println("Upload measurement");
  
   HTTPClient http;   

   //Specify destination for HTTP request
   http.begin("http://wow.metoffice.gov.uk/automaticreading?siteid=" + String(site_id) + "&siteAuthenticationKey=" + String(site_key) + "&dateutc=" + String(timeStringBuff) + "&baromin=" + pressure + "&humidity=" + String(humidity) + "&tempf=" + String(temperature) + "&softwaretype=wowmonitor1.0");
   Serial.println("http://wow.metoffice.gov.uk/automaticreading?siteid=" + String(site_id) + "&siteAuthenticationKey=" + String(site_key) + "&dateutc=" + String(timeStringBuff) + "&baromin=" + pressure + "&humidity=" + String(humidity) + "&tempf=" + String(temperature) + "&softwaretype=wowmonitor1.0");
 
   int httpResponseCode = http.GET();   //Send the actual GET request
 
   if(httpResponseCode>0){
 
    String response = http.getString(); //Get the response to the request
 
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
 
   }else{
 
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
 
   }
 
   http.end();  //Free resources
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); // Wake up every X seconds
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Seconds");

  esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 1); // Wake-up when button is pressed
  Serial.println("Setup ESP32 to wake on button press");

  if (! bme.begin(&Wire)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }

  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                    Adafruit_BME280::SAMPLING_X1, // temperature
                    Adafruit_BME280::SAMPLING_X1, // pressure
                    Adafruit_BME280::SAMPLING_X1, // humidity
                    Adafruit_BME280::FILTER_OFF   );
                    
  if (firstBoot == 1){
    Serial.println("First boot, going back to sleep again");
    takeMeasurement();
    firstBoot = 0;
  } else {
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
  
    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
      Serial.println("Wakeup caused by external signal using RTC_IO");
      open_portal();
      firstBoot = 1; // Reset firstBoot to start all over
      Serial.println("Set firstBoot to true");
    } else {
      Serial.println("Wakeup caused by timer");
  
      takeMeasurement();
      get_wow_settings();
  
      config.autoReconnect = true; // Automatically attempts to reconnect past access point
      config.autoRise = false;
      portal.config(config);
      Serial.println("Setup wifi connection");
  
      Serial.println("Try to connect to WiFi...");
      portal.begin();
  
      if (WiFi.status() == WL_CONNECTED) {
          Serial.println("WiFi connection success");
          configTime(0, 0, ntpServer); // Get time
          getLocalTime(&timeinfo);
          time_now = millis();
          while(millis() < time_now + 500){
            //keep wait for time approx. 500 ms
            yield();
          }
          strftime(timeStringBuff, sizeof(timeStringBuff), "%Y-%m-%d+%H%%3A%M%%3A%S\0", &timeinfo);
          Serial.print("Time = ");
          Serial.println(timeStringBuff);
          Serial.println("Sending data...");
          sendData(); 
        } else {
          Serial.println("WiFi connection failed");
        } 
     }
  }
  
  //Go to sleep now
  Serial.println("Going to sleep now");
  Serial.println("So long and thanks for all the fish");
  esp_deep_sleep_start();
  Serial.println("WARNING: This should never be printed");
}

void loop() {
  // This will never run so it can be empty
}
