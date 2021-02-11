#include <Wire.h>
#include "TimeLib.h"
#include "cactus_io_BME280_I2C.h"

// Create BME280 object
BME280_I2C bme; // I2C using address 0x77
// or BME280_I2C bme(0x76); // I2C using address 0x76

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message 

bool continous = false;
bool request = false;
String message;
char input;

void setup() {

  Serial.begin(9600);
//  Serial.println("Bosch BME280 Pressure - Humidity - Temp Sensor | cactus.io");
  
  if (!bme.begin()) {
    Serial.print("Could not find a valid BME280 sensor, check wiring!");
    Serial.print("\r\n");
    while (1);
  }
  
  setSyncProvider( requestSync );
  
  bme.setTempCal(-1);// Temp was reading high so subtract 1 degree
  
  Serial.print("send \'c\' for continous readout");
  Serial.print("\r\n");
  Serial.print("send \'r\' for single request");
  Serial.print("\r\n");
  Serial.print("send 'T<unixtime>' to set internal clock of arduino");
  Serial.print("\r\n");
  
}

void loop() {
  
//  delay(1000);
  
  request = false;
  message = "";
  
  while( Serial.available() > 0 ) {
    
    message = Serial.readString();
    
//    input = Serial.read();
    
//    if( 
//          input == '\\' 
//          || 
//          input == '^' 
//    ) 
//      break ;
      
//    message += input;
    
  }
  
  if( message.startsWith(TIME_HEADER) ){
//    Serial.print(message);
//    Serial.print("\r\n");
    message.replace( TIME_HEADER , "" );
    setTime( message.toInt() );
    Serial.print("set time to ");
    Serial.print( message.toInt() );
    Serial.print("\r\n");
    return;
  }
  
  if( message.equals("c") ){
    continous = true;
    request = false;  
  }
  
  if( message.equals("r") ){
    continous = false;
    request = true;  
  }
  
  if( request || continous ){
    
    bme.readSensor();
    
    Serial.print(now()); 
    Serial.print(" \t");
    
    Serial.print(bme.getPressure_MB()); 
    Serial.print(" \t");
    
    Serial.print(bme.getHumidity()); 
    Serial.print(" \t");
    
    Serial.print(bme.getTemperature_C());
    
    Serial.print("\r\n");
    
  }
  
  request = false;
  
  // Add a 1 second delay.
  if(continous) 
    delay(10000); //just here to slow down the output.
  
} 

time_t requestSync()
{
  Serial.write(TIME_REQUEST);  
  return 0; // the time will be sent later in response to serial mesg
}
