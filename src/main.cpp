// ****************************************************************** 
/** I, Andrew Maye, 000344062 certify that this material is my original work.
// No other person's work has been used without due acknowledgement.
//
// COMP-10184 
// Mohawk College 
**/
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
// 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

/**
 *  this function takes the tempature as a parameter and returns a judgement of tempature. 
 * */
String makeJudgement(int tempature){
  String judgement;
  if(tempature < 10){
    judgement = "Cold!";
  } else if (tempature >= 10 && tempature < 15 ){
    judgement = "Cool";
  } else if (tempature >= 15 && tempature < 25 ){
    judgement = "Perfect";
  } else if (tempature >= 25 && tempature < 30 ){
    judgement = "Warm";
  } else if (tempature >= 30 && tempature < 35 ){
    judgement = "Hot";
  } else if (tempature > 35){
    judgement = "Too Hot!";
  }
  return judgement;
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 

  // Application title
  Serial.println("\nTemperature Application");

  uint8_t address[8];

//Check if sensor is installed
  if(DS18B20.getAddress(address, 0)){
    delay(2000); //2 second delay to allow time to find sensor.
    Serial.print("Found DS18B20 sensor with address: ");
    //Print address
    for(int i = 0; i<8; i++){
      Serial.printf("%02X",address[i]);
    }
    Serial.println("");
    // Sensor not installed
  } else{
    Serial.println("No DS18B20 tempature sensors are installed!");
    Serial.println("Exiting application...");
    exit(0);
    return;
  }
} 
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
 
  // print the temp to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " C or " + makeJudgement(fTemp)); 
 
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
} 