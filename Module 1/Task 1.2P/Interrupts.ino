const int pirPin = 2;    // PIR sensor connected to digital pin 2
const int ledPin1 = 3;   // Red LED connected to digital pin 3
const int ledPin2 = 4;   // Blue LED connected to digital pin 4

void setup() 
{
  Serial.begin(9600);
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  
  // Attach interrupt to sensor pin
  attachInterrupt(digitalPinToInterrupt(pirPin), sensorTriggered, CHANGE); 
  // CHANGE mode for both rising and falling edges

}

void loop() 
{
  // No need for constant sensor reading in loop, interrupt handles it
}

// Interrupt service routine (ISR) triggered when sensor value changes
void sensorTriggered() 
{
  if (digitalRead(pirPin) == HIGH)  // Motion detected
  {
    digitalWrite(ledPin1, HIGH);   // Red LED on
    digitalWrite(ledPin2, LOW);    // Blue LED off
    Serial.println("Person At Door !!!");
    delay(800);
  }
  else  // No motion
  {
    digitalWrite(ledPin1, LOW);    // Red LED off
    digitalWrite(ledPin2, HIGH);   // Blue LED on
    Serial.println("NOBODY");
    delay(800);
  }
}
