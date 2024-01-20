#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Wire.h>
#include <BH1750.h>

BH1750 lightSensor;

const int ledPin1 = 18;
const int ledPin2 = 19;

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  lightSensor.begin();

  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  delay(1500); 

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() 
{
  ArduinoCloud.update();
  
  float lux = lightSensor.readLightLevel();

  while (lux < 30)
  {
    digitalWrite(ledPin1, HIGH);
    rED = 1;
    digitalWrite(ledPin2, LOW);
    bLUE = 0;
    ArduinoCloud.update();
    Serial.println("Person At Door !!!");
    delay(800);

    lux = lightSensor.readLightLevel();
  }
  
  digitalWrite(ledPin1, LOW);
  rED = 0;
  digitalWrite(ledPin2, HIGH);
  bLUE = 1;
  ArduinoCloud.update();
}
