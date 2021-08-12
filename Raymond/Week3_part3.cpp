// C++ code
//
int but = 8;
int led = 9;
int val = 0;

void setup()
{
  pinMode(but, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop()
{
  if(digitalRead(but) == HIGH)
  {
    val += 51; // pin9 is 490Hz, the value can only be 0 - 255
               // 5 level of brightness 
  }
  
  else if(val > 256) // the sixth click will make the brightness go back to 0
  {
    val = 0;
  }
  
  analogWrite(led,val);
  delay(100);
}