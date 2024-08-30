#include "SparkFun_SGP30_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>

SGP30 mySensor; // Create an object of the SGP30 class

void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  
  // Initialize sensor
  if (mySensor.begin() == false) 
  {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  
  // Initializes sensor for air quality readings
  // measureAirQuality should be called in one-second increments after a call to initAirQuality
  mySensor.initAirQuality();
}

void loop() 
{
  const int maxValues = 300; // Maximum number of readings
  int count = 0; // Counter for readings
  
  while (count < maxValues) 
  {
    // Measure CO2 and TVOC levels
    mySensor.measureAirQuality();
    
    Serial.print("CO2: ");
    Serial.print(mySensor.CO2);
    Serial.print(" ppm\tTVOC: ");
    Serial.print(mySensor.TVOC);
    Serial.println(" ppb");
    
    // Check TVOC levels and trigger actions
    if (mySensor.TVOC > 100 ) 
    {
      Serial.println("SPRAY");
    
     if (mySensor.TVOC > 200) 
    {
      Serial.println("ALERT ALERT");
    }
    }
    
    delay(1000); // Wait 1 second between readings
    count++;
  }
  
  // Reset the counter and wait for 2 minutes before restarting
  count = 0;
  delay(120000); // 2 minutes delay
}
