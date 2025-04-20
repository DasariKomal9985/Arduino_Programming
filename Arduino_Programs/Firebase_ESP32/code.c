#include <WiFi.h>
#include <FirebaseESP32.h>
#define WIFI_SSID "OTA"
#define WIFI_PASSWORD "135792468"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#define API_KEY "AIzaSyAasvBq72dZRJy9ARtKGigchSyKrGJjBKc"
#define DATABASE_URL "https://vehicle-to-grid-09-march-2025-default-rtdb.asia-southeast1.firebasedatabase.app/"  //<databaseName>.firebaseio.com or <databaseName>.<region>.firebasedatabase.app
#define USER_EMAIL "vehicletogrid_09_march_2025@gmail.com"
#define USER_PASSWORD "123456789"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;


void setup(){
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    lcd.print("Waiting");
    Serial.println("Waiting");
    delay(300);
  }
Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
}



void loop(){
unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    readSensors();
  }
  if (Firebase.ready() && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    FirebaseJson json;
   // json.add("Temperature", temperature);
    json.add("Voltage", motorVoltage);
    json.add("Current", current_A);
   // json.set("Temperature", temperature);
    json.set("Voltage", motorVoltage);
    json.set("Current", current_A);
    Serial.printf("Update json... %s\n\n", Firebase.updateNode(fbdo, String("/Vehicle_to_Grid/Data/" + fbdo.pushName()), json) ? "ok" : fbdo.errorReason().c_str());
  }
}