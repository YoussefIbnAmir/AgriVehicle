#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
//#include <DFRobot_DHT11.h>
//DFRobot_DHT11 DHT;
//#define DHT11_PIN 8

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "slmn"
#define WIFI_PASSWORD "00000000"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDiLUf97TijqKl62psA5L2sznv-sX_6l1Y"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "mohannedaoka669@gmail.com"
#define USER_PASSWORD "Moha10079"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "agrivehicle-a3182-default-rtdb.firebaseio.com"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Database main path (to be updated in setup with the user UID)
String databasePath = "/Agri-Vehicle";
// Database child nodes
String tempPath = "/temperature";
String humPath = "/humidity";
String MoisPath = "/soil_moisture";
String pHPath = "/soilpH";
String UVPath = "/uV";
String timePath = "/timestamp";
String indePath = "/inde";

int inde = 0;


// Parent Node (to be updated in every loop)


FirebaseJson json;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// Variable to save current epoch time
int timestamp;

/*
  unsigned long sendDataPrevMillis = 0;
  unsigned long timerDelay = 10000;
*/

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() {
  Serial.begin(115200);

  initWiFi();
  timeClient.begin();

  // Assign the api key (required)
  config.api_key = API_KEY;

  // Assign the user sign in credentials
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  // Assign the RTDB URL (required)
  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  // Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

}

void loop() {
  // Send new readings to database
  if (Serial.available() && Firebase.ready() ) {
    String  str = Serial.readString();
    if (str.length() <= 20)
    {
      String strs[5];
      int StringCount = 0;
      delay(20);
      
      // Split the string into substrings
      while (str.length() > 0)
      {
        int index = str.indexOf(';');
        if (index == -1) // No ; found
        {
          strs[StringCount++] = str;
          //Serial.flush();
          break;
        }
        else
        {
          strs[StringCount++] = str.substring(0, index);
          str = str.substring(index + 1);

        }
      }
    

      //String date1 = String(Serial.readString());
      json.set(tempPath.c_str(), strs[0]);
      json.set(humPath.c_str(), strs[1] );
      json.set(MoisPath.c_str(), strs[2] );
      json.set(pHPath.c_str(), strs[3] );
      json.set(UVPath.c_str(), strs[4] );
      json.set(indePath.c_str(), inde );
      //json.set(timePath, String(timestamp));
      Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, databasePath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
      inde++;
    }

  }
}
