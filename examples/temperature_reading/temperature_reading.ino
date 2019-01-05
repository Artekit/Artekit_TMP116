// Example for the AK-TMP116N temperature sensor breakout board.
// This example configures the sensor for temperature reading and
// ALARM sensing.

#include <Artekit_TMP116.h>

// The pin on which we connect the ALERT pin
#define TEMP_ALERT_PIN    A0
// Low limit for temperature alert
#define TEMP_LOW_LIMIT    20
// High limit for temperature alert
#define TEMP_HIGH_LIMIT   30

// Instantiate the Artekit_TMP116N class
Artekit_TMP116 temp_sensor;

bool initialized = false;

void setup()
{
  // Initialize serial port
  Serial.begin(9600);

  // Initialize the input pin for the ALERT indication
  pinMode(TEMP_ALERT_PIN, INPUT);

  // Initialize temperature sensor
  initialized = temp_sensor.begin();
  
  if (initialized)
  {
    Serial.println("AK-TMP116N sensor initialized");
  } else {
    Serial.println("Error initializing AK-TMP116N sensor");
  }

  // Configure the alert on a 20 degrees low limit 
  // and a high limit on 30 degrees
  temp_sensor.setLowHighLimit(TEMP_LOW_LIMIT, TEMP_HIGH_LIMIT);
}

void loop()
{
  if (!initialized)
    return;
    
  // Read and print the temperature
  delay(500);
  float temperature = temp_sensor.readTemperature();
  Serial.print(temperature);
  Serial.println("ºC");
  
  // As an alternative you can do:
  //if (temp_sensor.readTemperature(&temperature))
  //{
  //  Serial.print(temperature);
  //  Serial.println("ºC");
  //}
  
  // Check for an alert (pin is active-low)
  if (!digitalRead(TEMP_ALERT_PIN))
  {
    // Get the alert type
    TMP116_Alert alert = temp_sensor.getAlertType();

    switch(alert)
    {
      default:
      case TMP116_NoAlert:
        break;
      
      case TMP116_AlertLow:
        Serial.println("ALERT L");
        break;
        
      case TMP116_AlertHigh:
        Serial.println("ALERT H");
        break;

      case TMP116_AlertLowHigh:
        Serial.println("ALERT HL");
        break;
    }
  }
}
