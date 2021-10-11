int period = 300;
int fanSampleRate = 10;
int fanPin = A0;

int highest = 0;
int seconds = 0;
int promAddr = 0;



void timer4_init() {
  // Used the Arduino Timer Calculator at http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html to generate this code
  
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
    Serial.print("Highest: ");
    Serial.println(highest);
    //EEPROM.write(promAddr++, highest); // Write the highest windspeed of the period to EEPROM
    highest = 0;
  }
}

void setup(){
  Serial.begin(9600);
  timer4_init();
}


void loop() {
  int newReading = analogRead(fanPin);
  
  if (newReading > highest)
    highest = newReading;

  delay(fanSampleRate); // Time in between taking readings from anemometer (fan)
}







