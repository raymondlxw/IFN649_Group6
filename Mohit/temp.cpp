// C++ code
//
int sensePin = A0;
int red  = 7 ;
int blue = 6 ;
int green = 5 ;
int Input;
double temp;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Input = analogRead(A0);
  temp = (double)Input / 1024;
  temp = temp * 5;
  temp = temp - 0.5;
  temp = temp * 100;
  
  if (temp > 30.00){
  digitalWrite(red,HIGH);
  }else if (temp >= 12.50 && temp <= 29.00){
  digitalWrite(blue, HIGH);
  }else if (temp < 12.50){
  digitalWrite(green, HIGH);
  }

  
  Serial.print("Current Temperarture= ");
  
  Serial.println(temp);
  delay(1000);
  digitalWrite(red, LOW);
  digitalWrite(blue, LOW);
  digitalWrite(green, LOW);

}