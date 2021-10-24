#include "DHT.h"

//const int dlt = ;           // input the delay time here to control how often it measure data
#define rxPin 7             //receiving serial data
#define txPin 8             //transmitting serial data
#define DHTPIN 21           // define DHT sensor pin
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);

int period = 50;
int fanSampleRate = 10;
int fanPin = A0;
const int photoResistor = A0;  // input the pin that the photoresistor connect to here
int highest = 0;
int light1 =0;
int h1 = 0.0;
int t1 = 0.0;
int seconds = 0;
int promAddr = 0;



void timer1_init() {
  // TIMER 1 for interrupt frequency 1 Hz:
  cli(); // stop interrupts
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR1A = 62499; // = 16000000 / (256 * 1) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts 
}


ISR(TIMER1_COMPA_vect) {         // timer compare interrupt service routine

  // This section increments the seconds counter each time the interrupt handler is called.
  // Once the number of seconds reaches the period length, we run this block of code and reset.
  seconds++;
  if (seconds >= period) {
    seconds = 0;
    Serial.print("Humidity: ");
    Serial.print(h1);
    Serial.print("Temperature: ");
    Serial.print(t1);
    Serial.print("Light: ");
    Serial.print(h1);
    Serial.print("Wind: ");
    Serial.println(highest);
    //Serial Bluetooth Print
    Serial1.print("Humidity: ");
    Serial1.print(h1);
    Serial1.print("Temperature: ");
    Serial1.print(t1);
    Serial1.print("Light: ");
    Serial1.print(h1);
    Serial1.print("Wind: ");
    Serial1.println(highest);
    //EEPROM.write(promAddr++, highest); // Write the highest windspeed of the period to EEPROM
    highest = 0;
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(photoResistor, INPUT);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  timer1_init();
  Serial1.begin(9600);
}


void loop() {
  int light = analogRead(photoResistor);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  int newReading = analogRead(fanPin);
  light1 = light;
  h1 = h;
  t1 = t;
  if (newReading > highest)
    highest = newReading;

  delay(fanSampleRate); // Time in between taking readings from anemometer (fan)
}

