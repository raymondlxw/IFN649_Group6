// C++ code
//
int red = 7;
int blue = 6;
int green = 5;
int button = 9;
int count = 0;
boolean lastButton;
boolean currentButton = false;
boolean ledOn = false;

void setup() {

  pinMode(button, INPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  count = 0;
}
//debounce function to stabilise the button
boolean debounce(boolean last)
{
  boolean current = digitalRead(button);
  if (last != current)
  {
    delay(5);
    current = digitalRead(button);
  }
  return current;  
}
void loop() {
  lastButton = currentButton;
  currentButton = debounce(lastButton);
  if (lastButton == false && currentButton == true)
  {
    if (count == 1) 
    { 
      count++;
      digitalWrite(red, HIGH);
      digitalWrite(blue, LOW);
      digitalWrite(green, LOW); 
    }

    else if (count == 2)
    { 
      count++;
      digitalWrite(red, LOW); 
      digitalWrite(blue, HIGH);
      digitalWrite(green, LOW);
    }

    else if (count == 3)
    { 
      count = 0;
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(green, HIGH); 
    }
    else if(count == 0)
    {
      count++;
      digitalWrite(red, LOW);
      digitalWrite(blue, LOW);
      digitalWrite(green, LOW); 
      
   } 
  }
}