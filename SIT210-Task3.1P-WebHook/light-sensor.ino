int led1 = A5;                                      //define variable for led1
int led2 = D7;                                      //define variable for led2
int photoresistor = A0;                             //define variable for photoresistor
int analogVal;                                      //define variable for ananlog

void setup() 
{

  pinMode(led1, OUTPUT);                            //set led as output
  pinMode(led2, OUTPUT);                            //set led as output
  pinMode(photoresistor, INPUT);                    //set photoresistor as input

}


void loop() 
{
    analogVal = analogRead(photoresistor);          //map analog reading to variable
    String light = String(analogVal);               //convert to sring
    Particle.publish("Light", light, PRIVATE);      //public string to web
    
    if (analogVal > 50)                             //if reading above 50, turn led off
    {
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
    }
    else                                            //if below, turn off
    {
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
    }
    delay(1000);                                    //wait 1 second (publish doesn't appear to work without a delay)
}

