
int led = D6;                               // define LED pin

int ledToggle(String command);              // define manual write function

void blinkFast()                            // funtion to make LED blink quick
{
  digitalWrite(led, HIGH);                  // turn the LED on
  delay(300);                               // wait for 300ms
  digitalWrite(led, LOW);                   // turn the LED off
  delay(700);                               // wait for 700ms
}

void blinkSlow()                            // funtion to make LED blink slow
{
  digitalWrite(led, HIGH);                  // turn the LED on
  delay(700);                               // wait for 700ms
  digitalWrite(led, LOW);                   // turn the LED off
  delay(700);                               // wait for 700ms
}

void setup()
{
   pinMode(led, OUTPUT);                    // define pin as output

   Particle.function("led",ledToggle);      // function to control over internet

   digitalWrite(led, LOW);                  // set led to off

}

void r()                                    // function for letter r
{
    blinkFast();
    blinkSlow();
    blinkFast();
}

void h()                                    // function for letter h
{
    blinkFast();
    blinkFast();
    blinkFast();
    blinkFast();
}

void y()                                    // function for letter y
{
    blinkSlow();
    blinkFast();
    blinkSlow();
    blinkSlow();
}

void s()                                    // function for letter s
{
    blinkFast();
    blinkFast();
    blinkFast();
}

void loop()                                 // loop blinking functions
{
    r();
    h();
    y();
    s();
    delay(1000);                            // wait for 1 second
}


int ledToggle(String command)               // internet toggle function
{             

    if (command=="on")                      // turn on led branch
    {
        digitalWrite(led,HIGH);
        return 1;
    }   
    else if (command=="off")                // turn off led branch
    {
        digitalWrite(led,LOW);
        return 0;
    }
    else 
    {
        return -1;
    }
}