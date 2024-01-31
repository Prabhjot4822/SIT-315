const int pirPin = 2;    // PIR sensor connected to digital pin 2
const int ledPin1 = 4;   // Red LED connected to digital pin 3
const int ledPin2 = 5;   // Blue LED connected to digital pin 4
int sensorValue = 0;

void setup() 
{
  Serial.begin(9600);
  
  pinMode(3, INPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Attach interrupt to sensor pin
  attachInterrupt(digitalPinToInterrupt(pirPin), PirTriggered, RISING); 
  attachInterrupt(digitalPinToInterrupt(3), PhotoTriggered, RISING);
  // CHANGE mode for both rising and falling edges
}

void loop() 
{
  // No need for constant sensor reading in loop, interrupt handles it
}

// Interrupt service routine (ISR) triggered when sensor value changes

void PirTriggered() 
{
  if (digitalRead(pirPin) == HIGH)  // Motion detected
  {
    digitalWrite(ledPin1, HIGH);   // Red LED on
    digitalWrite(ledPin2, LOW);    // Blue LED off
    Serial.println("Person At Door !!!");
  }
}

void PhotoTriggered()
{
  sensorValue = digitalRead(3);
  
  if(sensorValue)   // Sunlight Detected
  {
    Serial.println("Sunlight Detected");
    digitalWrite(ledPin1, LOW);    // Red LED off
    digitalWrite(ledPin2, HIGH);   // Blue LED on
  }
}
