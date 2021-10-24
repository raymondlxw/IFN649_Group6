
#include "DHT.h"
#define rxPin 7   //receiving serial data
#define txPin 8   //transmitting serial data
#define DHTPIN 21 // define DHT sensor pin
#define DHTTYPE 11
DHT dht(DHTPIN, DHTTYPE);

// *** Customizable Parameters ***
int period = 300;       // (300 seconds = 5 minutes)
int fanSampleRate = 10; // How many milliseconds between taking windspeed readings (Needs to be small enough to capture the peak of the analog waveform)
int fanPin = 20;

// *** Globals ***
int highest = 0; // Keeps track of the highest windspeed over a period
int seconds = 0; // Keeps track of how many seconds have passed within a period
//int promAddr = 0;    // Current index in EEPROM memory

int light1 = 0;
int h1 = 0.0;
int t1 = 0.0;
const int photoResistor = 19; // input the pin that the photoresistor connect to here

/********************************************************
 * timer1_init()
 *
 * Sets up the registers to use TIMER 1 which will be
 * used to call an interrupt handler once every second
 * (Assumes Arduino Uno is based off ATMEGA328)
 ********************************************************/
void timer1_init()
{
    // Used the Arduino Timer Calculator at http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html to generate this code

    // TIMER 1 for interrupt frequency 1000 Hz:
    cli();      // stop interrupts
    TCCR1A = 0; // set entire TCCR1A register to 0
    TCCR1B = 0; // same for TCCR1B
    TCNT1 = 0;  // initialize counter value to 0
    // set compare match register for 1000 Hz increments
    OCR1A = 1999; // = 2000000 / (1 * 1000) - 1 (must be <65536)
    // turn on CTC mode
    TCCR1B |= (1 << WGM12);
    // Set CS12, CS11 and CS10 bits for 1 prescaler
    TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10);
    // enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    sei(); // allow interrupts
}

/********************************************************
 * Interrupt Service Routine (Timer 1)
 *
 * This is called by Timer 1 once a second.
 ********************************************************/
ISR(TIMER1_COMPA_vect)
{ // timer compare interrupt service routine

    // This section increments the seconds counter each time the interrupt handler is called.
    // Once the number of seconds reaches the period length, we run this block of code and reset.
    seconds++;
    if (seconds >= period)
    {
        delay(100000);
        seconds = 0;
        int mph = 0.109 * highest;
        Serial.print("Highest mph: ");
        Serial.print(mph);
        Serial1.print("Highest mph: ");
        Serial1.print(mph);
        highest = 0;

        Serial.print(" Humidity: ");
        Serial.print(h1);
        Serial.print(" Temperature: ");
        Serial.print(t1);
        Serial.print(" Light: ");
        Serial.print(light1);
        Serial.println(" ");
        // Serial Bluetooth Print
        Serial1.print(" Humidity: ");
        Serial1.print(h1);
        Serial1.print(" Temperature: ");
        Serial1.print(t1);
        Serial1.print(" Light: ");
        Serial1.print(light1);
        Serial1.println(" ");
    }
}

/********************************************************
 * setup()
 * 
 * Start-up initializations.
 ********************************************************/
void setup()
{
    Serial.begin(9600);
    pinMode(photoResistor, INPUT);
    pinMode(DHTPIN, INPUT);
    dht.begin();
    Serial1.begin(9600);
    timer1_init();
}

/********************************************************
 * loop()
 *
 * Main program loop.
 ********************************************************/
void loop()
{
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
    if (newReading > 151)
        highest = 0;
}