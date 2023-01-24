//arduino code



// wait 10 secs until all the
// down the moisture and ph sensors (done)
// take all the readings from all the sensors, each value with a function, each funcion returns the final value after calculations and mapping, each sensor data is seperated by ";"
// temperature #1 done
// humidity #2 done
// moisture #3 done (fabricate)
// pH #4 done
// uv light intensity #5 done
// move along a rectangular path based on the input and output length and width
//send the data to the esp (calculate the time required to do all this)
// pull moisture and ph sensors up again (done)
// move the car to another position (calculate the time between each send)
// loop

#include <DFRobot_DHT11.h>
#include <Wire.h>
#include <Adafruit_VEML6070.h>
DFRobot_DHT11 DHT;
Adafruit_VEML6070 uv = Adafruit_VEML6070();

#define enaph 9
#define enamt 10
#define out1 2 // high1-low2 = forward  ||  low1-high2 = backward
#define out2 7
#define out3 3 // high1-low2 = forward  ||  low1-high2 = backward
#define out4 4
#define out5 5 // for the ph, moisture motor
#define out6 6 // for the ph, moisture motor
#define DHT11_PIN 8 // temperature sensor pin
#define MOISTURE_PIN A0 // moisture sensor pin


int phspd = 180; // the car speed value. written to the enables of the 3 motors
int mospd = 255;
int mdcons = 12500; // the delay constant of the ph and moisture sensors
int otVal; // initiate a value for the soil moisture percentage
//ـــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــــ

String UV_Int() { // a function to get the value of UV intensity folowed by ";" , var: UV_Val_S. unit: mW/m^2

  int UV_mVal = uv.readUV();
  //Serial.println(UV_mVal);
  int UV_Val = (UV_mVal * 5);
  //Serial.println(UV_Val);
  String UV_Val_S = String(UV_Val);
  //Serial.println(UV_Val_S);
  return UV_Val_S;
}


String soilMoisture_pH() { // a function to get the value of the soil moisture and pH values and return them in percentage (;val), var: moist_pH. unit: percentage/Scale from 0-14

  int sensorVal = analogRead (MOISTURE_PIN) ;  // read the analog value from sensor
  otVal = map(sensorVal, 200, 1023, 100, 0); // mapping the 10-bit signal to 8-bit signal
  float  soil_pH = (-0.0646 * otVal) + 8.1246; // get the ph value based on the moisture value
  float soil_pHm = ((9 - 5) / (8.5 - 2)) * (soil_pH - 2) + 5; // mapping the results
  String moist_pH = String(otVal) + ";" + String(soil_pHm) + ";"; // convert the result to a string, followed by ";"
  return moist_pH; // return the moisture valuet
}

String tempHumid() { // a function to get the temperature and humidity data from the sensor and convert it into a string seperated by ";". var: temperature_Humidity. unti: C, percentage

  DHT.read(DHT11_PIN);
  String T = String(DHT.temperature);
  String H = String(DHT.humidity);
  String temperature_Humidity = T + ";" + H + ";";
  //Serial.println(temperature_Humidity);
  delay(100);
  return temperature_Humidity;
}

void ph_down() { //5High-6Low : down //6High-5Low : up

  analogWrite(enaph, phspd);
  digitalWrite(out5, HIGH);
  digitalWrite(out6, LOW);
  delay(mdcons);
  digitalWrite(out5, LOW);
  digitalWrite(out6, LOW);
}

void ph_up() { //5High-6Low : down //6High-5Low : up

  analogWrite(enaph, phspd);
  digitalWrite(out5, LOW);
  digitalWrite(out6, HIGH);
  delay(mdcons);
  digitalWrite(out5, LOW);
  digitalWrite(out6, LOW);
}

void moveForward_10() {

  analogWrite(enamt, mospd);
  digitalWrite(out1, HIGH);// forward
  digitalWrite(out2, LOW);// forward
  digitalWrite(out3, LOW);// forward
  digitalWrite(out4, HIGH);// forward
  delay(1000);
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
}


void setup() {

  delay(15000);

  pinMode(enaph, OUTPUT); pinMode(enamt, OUTPUT); pinMode(out1, OUTPUT); pinMode(out2, OUTPUT); pinMode(out3, OUTPUT); pinMode(out4, OUTPUT); pinMode(out5, OUTPUT); pinMode(out6, OUTPUT);
  digitalWrite(enaph, LOW);
  digitalWrite(enamt, LOW);
  Serial.begin(115200);
  uv.begin(VEML6070_1_T);


  
  //moveForward_10();
  //ph_down();
  //ph_up();
  //tempHumid();
  //Serial.println(tempHumid() + soilMoisture_pH() +  UV_Int()); // send all data sensors to the ESP module
  //Serial.println(soilMoisture_pH());
  //Serial.println(UV_Int());
  //soilMoisture_pH();
  //soil_pH();
  //delay(5000);
  
  
  //moveForward_10();
  //ph_down();
  //delay(5000);
  //ph_up();
  //moveForward_10();
  //Serial.println(tempHumid() + soilMoisture_pH() +  UV_Int());

  /*
  delay(3000);
  moveForward_10();
  delay(21000);
  moveForward_10();
  moveForward_10();
  moveForward_10();
  moveForward_10();
  moveForward_10();
  moveForward_10();
  */
  
}

void loop() {

  
  /*
  delay(1000);
  // put your main code here, to run repeatedly:
  moveForward_10();
  ph_down();
  delay(5000);
  ph_up();
  moveForward_10();
  */

  
 
  Serial.println(tempHumid() + soilMoisture_pH() +  UV_Int());
  delay(20000);
  }
