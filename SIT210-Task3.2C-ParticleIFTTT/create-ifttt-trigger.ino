int led = A5;                                                           //define variable for led1
int photoresistor = A0;                                                 //define variable for photoresistor
int analogVal;                                                          //define variable for ananlog
bool sunlightOn = false;                                                //define variable for sunlight state

void setup() 
{

  pinMode(led, OUTPUT);                                                 //set led as output
  pinMode(photoresistor, INPUT);                                        //set photoresistor as input

}


void loop() 
{
    analogVal = analogRead(photoresistor);                              //map analog reading to variable
    String light = String(analogVal);                                   //convert to sring

    if (analogVal > 50)                                                 //if reading above 50, turn led off
    {
        if(sunlightOn == false)                                         //if state changed
        {
            Particle.publish("Sunlight level changed", "Light");        //publish IFTTT trigger
        }
        digitalWrite(led, HIGH);                                        //set led to on
        Particle.publish("Sunlight is on @ value:", light, PRIVATE);    //publish event of sunlight value
        sunlightOn = true;                                              //set bool to true
    }
    else                                                                //if below, turn off
    {
        if(sunlightOn == true)                                          //if state changed
        {
            Particle.publish("Sunlight level changed", "Dark");         //publish IFTTT trigger
        }
        digitalWrite(led, LOW);                                         //set led to off
        Particle.publish("Sunlight is off @ value:", light, PRIVATE);   //publish event of sunlight value
        sunlightOn = false;                                             //set bool to false
        
    }
    delay(1000);                                                        //wait 1 second (publish doesn't appear to work without a delay)
}

