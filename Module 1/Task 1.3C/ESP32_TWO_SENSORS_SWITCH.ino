#include <Wire.h>
#include <BH1750.h>

BH1750 lightSensor;

#define TRIGGER_PIN 17
#define ECHO_PIN 5
#define LED_PIN 18
#define BUTTON_PIN 13

#define MEASUREMENT_INTERVAL 1000
unsigned long previousMillis = 0;

const int ledPin1 = LED_PIN;
volatile bool buttonPressed = false;
volatile bool isBh1750Active = true;

void IRAM_ATTR handleButtonInterrupt() 
{
  buttonPressed = true;
}

void setup() 
{
  Serial.begin(115200);
  Wire.begin();
  lightSensor.begin();

  pinMode(ledPin1, OUTPUT);

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);
}

void loop() 
{
  if (isBh1750Active) 
  {
    float lux = lightSensor.readLightLevel();

    while (lux < 30) 
    {
      digitalWrite(ledPin1, HIGH);
      Serial.println(" Detection ");

      delay(800);

      lux = lightSensor.readLightLevel();
    }

    digitalWrite(ledPin1, LOW);
  } 
  
  else 
  {
    long duration, distance;
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= MEASUREMENT_INTERVAL) 
    {
      previousMillis = currentMillis;

      digitalWrite(TRIGGER_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIGGER_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIGGER_PIN, LOW);

      duration = pulseIn(ECHO_PIN, HIGH);
      distance = duration * 0.034 / 2;

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      if (distance < 10) 
      {
        digitalWrite(LED_PIN, HIGH);
      }

      else 
      {
        digitalWrite(LED_PIN, LOW);
      }
    }
  }

  if (buttonPressed) 
  {
    buttonPressed = false;  // Reset the button state

    // Toggle between sensors
    isBh1750Active = !isBh1750Active;

    Serial.println(" INTERRUPTION !!! SENSOR SWITCH !!!");

    // Add a delay to debounce the button
    delay(500);
  }
}
