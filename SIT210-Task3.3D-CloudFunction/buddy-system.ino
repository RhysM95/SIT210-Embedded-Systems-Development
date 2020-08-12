int led = A5;                                                               //define variable for led1


void setup()            
{

    pinMode(led, OUTPUT);                                                   //set led as output
    Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", myHandler);       //Listen for event name and call myHnadler function when recieved
}

void loop()                                                                 //no loop required
{
}

void fast_flash()                                                           //blink LED fast
{
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
        
    delay(300);
}

void slow_flash()                                                           //blink LED slow
{
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
        
    delay(500);
}

void myHandler(const char *event, const char *data)                         //return from the buddy particle device
{

    if (strcmp(data,"wave")==0)                                             //check if buddy sent wave
    {
        Particle.publish("Buddy Signal", "Wave event recieved", PRIVATE);   //diagnostics to confirm event
        slow_flash();
        slow_flash();
        slow_flash();
    }
    else if (strcmp(data,"pat")==0)                                         //check if buddy sen pat
    {
        Particle.publish("Buddy Signal", "Pat event recieved", PRIVATE);    //diagnostics to confirm event
        fast_flash();
        fast_flash();
        fast_flash();
        fast_flash();
        fast_flash();
    }
    else                                                                    //do nothing
    {
    }
}


