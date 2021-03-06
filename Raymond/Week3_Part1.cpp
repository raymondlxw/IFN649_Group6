//Ray 

int sensePin = A0;
int sensorInput;
double temp;
int yellow = 7;
int green = 6;
int red = 5;


void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  sensorInput = analogRead(A0);
  temp = (double)sensorInput / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;
  
  if (temp > 30.00)
  {
    digitalWrite(red, HIGH);
  }
  else if ( temp >= 10 && temp <=29)
  {
    digitalWrite(green, HIGH);
  }
  else if ( temp < 10)
  {
    digitalWrite(yellow, HIGH);
  }

  Serial.print("Current Temperature = ");
  Serial.print(temp);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);
}	