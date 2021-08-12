// C++ code
//


int button = 8;
int led = 10 ; //which is a PWM
int val = 0 ;

void setup()
{
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop()
{
  if(digitalRead(button) == HIGH)
  {
    val += 51;
    
  }else if (val > 255){
    val = 0;
  
  }
  
  analogWrite(led, val);
  delay(1000);
}