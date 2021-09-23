// C++ code
//
int ledPin1 = 8;
int ledPin2 = 7;
int ledPin3 = 6;
int switchPin = 9;
int count = 0;
boolean lastButton;
boolean currentButton = false;
boolean ledOn = false;

void setup()
{

    pinMode(switchPin, INPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    count = 0;
}
//debounce function to stabilise the button
boolean debounce(boolean last)
{
    boolean current = digitalRead(switchPin);
    if (last != current)
    {
        delay(5);
        current = digitalRead(switchPin);
    }
    return current;
}
void loop()
{
    lastButton = currentButton;
    currentButton = debounce(lastButton);
    if (lastButton == false && currentButton == true)
    {
        if (count == 1)
        {
            count++;
            digitalWrite(ledPin1, HIGH);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
        }

        else if (count == 2)
        {
            count++;
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, LOW);
        }

        else if (count == 3)
        {
            count = 0;
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, HIGH);
        }
        else if (count == 0)
        {
            count++;
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
        }
    }
}