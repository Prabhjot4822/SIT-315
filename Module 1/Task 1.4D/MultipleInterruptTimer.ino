const int sensor1 = A3;  
const int sensor2 = A2;
const int sensor3 = A1;
const int sensor4 = A0;
    
const int sensorLedPin1 = 8;
const int sensorLedPin2 = 9;
const int sensorLedPin3 = 10;

int celsius = 0;

volatile byte sensor1value = 0;
volatile byte sensor2value = 0;
volatile byte sensor3value = 0;
volatile byte sensor4value = 0;

void setup()
{
  Serial.begin(9600);
  
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  
  pinMode(sensorLedPin1, OUTPUT);
  pinMode(sensorLedPin2, OUTPUT);
  pinMode(sensorLedPin3, OUTPUT);
  
  // Enable Pin Change Interrupts for sensor pins
  PCMSK1 |= bit(PCINT8);  // Enable PCINT8 (A0)
  PCMSK1 |= bit(PCINT9);  // Enable PCINT9 (A1)
  PCMSK1 |= bit(PCINT10); // Enable PCINT10 (A2)
  PCMSK1 |= bit(PCINT11); // Enable PCINT11 (A3)
  
  // Enable Pin Change Interrupts on Port C
  PCICR |= bit(PCIE1);

  cli();  // Disable interrupts
  
  // Set up Timer1 for periodic interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  // Set the desired timer frequency (adjust the value based on your requirements)
  OCR1A = 55625;  // For 1-second interval with a 16MHz clock
  
  // Configure Timer1 for CTC mode with a prescaler of 256
  TCCR1B |= (1 << WGM12) | (1 << CS12);

  // Enable Timer1 Compare A interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();  // Enable interrupts
}

void loop()
{
  // NOTHING
}

void updateLED()
{
  digitalWrite(sensorLedPin1, sensor1value);
  digitalWrite(sensorLedPin2, sensor2value);
  digitalWrite(sensorLedPin3, sensor3value);
}

void updateSMonitor()
{
  celsius = map(((sensor4value - 20) * 3.04), 0, 1023, -40, 125);
  
  Serial.print("Room Temperature - ");
  Serial.print(celsius);
  Serial.println(" C' ");
}

ISR(PCINT1_vect)  
{
  sensor1value = analogRead(sensor1);
  sensor2value = analogRead(sensor2);
  sensor3value = analogRead(sensor3);
  sensor4value = analogRead(sensor4);

  updateLED(); // Update the LEDs
}

ISR(TIMER1_COMPA_vect) 
{
  updateSMonitor();
}
