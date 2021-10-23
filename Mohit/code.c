#include "DHT.h"
const int photoResistor = ; // input the pin that the photoresistor connect to here
const int dlt = ;           // input the delay time here to control how often it measure data
#define rxPin 7             //receiving serial data
#define txPin 8             //transmitting serial data
#define DHTPIN 21           // define DHT sensor pin
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);

int period = 300;
int fanSampleRate = 10;
int fanPin = A0;

int highest = 0;
int seconds = 0;
int promAddr = 0;



void timer4_init() {
  
  // TIMER 1 for interrupt frequency 1 Hz:
  cli(); // stop interrupts
  TCCR4A = 0; // set entire TCCR1A register to 0
  TCCR4B = 0; // same for TCCR1B
  TCNT4  = 0; // initialize counter value to 0
  // set compare match register for 1 Hz increments
  OCR4A = 15624/1; // = (16*10^6) /(1*1024) -1
  // turn on CTC mode
  TCCR4B |= (1 << WGM12);
  // Set CS12, CS11 and CS10 bits for 256 prescaler
  TCCR4B |= (1 << CS12) | (0 << CS10);
  // enable timer compare interrupt
  TIMSK4 |= (1 << OCIE4A);
  sei(); // allow interrupts 
}


ISR(TIMER4_COMPA_vect) {         // timer compare interrupt service routine

  // This section increments the seconds counter each time the interrupt handler is called.
  // Once the number of seconds reaches the period length, we run this block of code and reset.
  seconds++;

  if (seconds >= period) {
    seconds = 0;
    int sped = highest * 0.115;
    Serial.print("Highest: ");
    Serial.println(sped);
    Serial1.print(sped);
    //EEPROM.write(promAddr++, highest); // Write the highest windspeed of the period to EEPROM
    highest = 0;
  }
}


void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(photoResistor, INPUT);
    pinMode(DHTPIN, INPUT);
    dht.begin();
    timer4_init();
    Serial1.begin(9600);
    delay(1000);
}

void loop()
{
    // put your main code here, to run repeatedly:
    delay(dlt);
    dataRead();
    Serial.println("");
    Serial1.println("");
}


void dataRead()
{

    // Measure humidity and temperature, print in terminal and send via bluetooth
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);

    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print(F(" Humidity: "));
    Serial.print(h);
    Serial.print(F("%  Temperature: "));
    Serial.print(t);
    Serial.print(F("C "));
    Serial.print(f);
    Serial.print(F("F  Heat index: "));
    Serial.print(hic);
    Serial.print(F("C "));
    Serial.print(hif);
    Serial.print(F("F "));

    Serial1.print(F(" Humidity: "));
    Serial1.print(h);
    Serial1.print(F("%  Temperature: "));
    Serial1.print(t);
    Serial1.print(F("C "));
    Serial1.print(f);
    Serial1.print(F("F  Heat index: "));
    Serial1.print(hic);
    Serial1.print(F("C "));
    Serial1.print(hif);
    Serial1.print(F("F "));

    // Measure light intensity, print in terminal and send via bluetooth
    int light = analogRead(photoResistor);
    Serial.print(" Current brightness is ");
    Serial.print(light);
    Serial1.print(" Current brightness is ");
    Serial1.print(light);
    
    int newReading = analogRead(fanPin);
    if (newReading > highest)
    highest = newReading;
    delay(fanSampleRate); // Time in between taking readings from anemometer (fan)

}