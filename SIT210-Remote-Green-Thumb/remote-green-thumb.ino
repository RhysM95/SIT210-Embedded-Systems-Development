// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>
#include <MQTT.h>
#include <Adafruit_DHT.h>                                                       //Library for DHT sensor

#define DHTPIN 2                                                                //define pin of sensor
#define DHTTYPE DHT22                                                           //define model of sensor

int moisture;                                                                   //variable for moisture sensor
int lightLoSP = 1000;                                                           //setpoint for alarm trigger
int humidityLoSP = 50;                                                          //^^
int tempHiSP = 50;                                                              //^^
int moistureLoSP = 300;                                                         //^^
float light;                                                                    //variable for light sensor
float temperature;                                                              //variable for temp sensor
float humidity;                                                                 //variabe for humidity sensor

MQTT client("test.mosquitto.org", 1883, callback);                              //MQTT connection info

DHT dht(DHTPIN, DHTTYPE);                                                       //create an instance
BH1750 lightMeter(0x23, Wire);                                                  //Lightmeter config

void callback(char* topic, byte* payload, unsigned int length)                  //MQTT recieve data *future use*
{
}

void setup() 
{
    dht.begin();                                                                //start instance
    lightMeter.begin();                                                         //^^
    lightMeter.set_sensor_mode(BH1750::forced_mode_high_res2);                  //setup light sensor
    pinMode(moisture, INPUT);                                                   //set moisture as input
    client.connect("ArgonDev");                                                 //MQTT client
}


void lightSensor(int lightLoSP)                                                 //routine for light data
{   
    lightMeter.make_forced_measurement();                                       //start collecting light data
    light = lightMeter.get_light_level();                                       //map to variable
    
    String lightString = String::format ("%.1f", light);                        //convert to string and format
    String lightSPString = String(lightLoSP);                                   //map setpoint to string
    client.publish("Argon_1 Light Level", lightString);                         //MQTT publish data
    client.publish("Argon_1 Light SP", lightSPString);                          //MQTT publish Setpoint

    if (light < lightLoSP)                                                      //if less than alarm SP
    {
        client.publish("Argon_1 Light Alarm", "Dark");                          //MQTT publish alarm
        Particle.publish("Argon_1 Light Alarm", "Dark");                        //publish IFTTT trigger
    }
    else
    {
        client.publish("Argon_1 Light Alarm", "Light");                         //MQTT publish alarm
    }
        //Light intensity range: 0-65535Lx
        //200 - 500 LUX: Low light intensity, deep-shade. Not Ideal for most plants
        //500 - 1,000 LUX: Still low light intensity, natural light of an ordinary room, appropriate for shade-loving plants.
        //1,000 - 2,000 LUX: Indirect sunlight, appropriate for plants that require indirect sunlight.
        //2,000 – 4,000 LUX: 40% of midday sun, bright light, ideal for many plants.
        //4,000 – 5,000 LUX: 50% of midday sun, strong direct sunlight, appropriate for plants that require a lot of strong light.
        //5,000 and up LUX: Very bright indoor light but still not as strong as sunlight outdoors.
        //10,000 - 20,000 LUX: Full sun outdoors, can burn plants
}


void tempSensor(int tempHiSP)                                                   //routine for temp data
{
    temperature = dht.getTempCelcius();                                         //map analog reading to variable
    String tempString = String::format ("%.1f", temperature);                   //convert to string and format
    String tempSPString = String(tempHiSP);                                     //map setpoint to string

    client.publish("Argon_1 Temperature", tempString);                          //MQTT publish data
    client.publish("Argon_1 Temperature SP", tempSPString);                     //MQTT publish setpoint

    if (temperature > tempHiSP)                                                 //if more than alarm SP
    {
        client.publish("Argon_1 Temperature Alarm", "High");                    //MQTT publish alarm
        Particle.publish("Argon_1 Temperature Alarm", "High");                  //publish IFTTT trigger
        //Temperature Range:-40-80℃
        //25 - 28 ideal
    }
    else
    {
        client.publish("Argon_1 Temperature Alarm", "Normal");                  //MQTT publish alarm
    }
}

void moistureSensor(int moistureLoSP)                                           //routine for moisture data
{
    moisture = analogRead(A0);                                                  //map analog reading to variable
    String moistureString = String(moisture);                                   //convert to string
    String moistureSPString = String(moistureLoSP);

    client.publish("Argon_1 Moisture", moistureString);                         //MQTT publish data
    client.publish("Argon_1 Moisture SP", moistureSPString);                    //MQTT publish setpoint

    if (moisture < moistureLoSP)                                                //if less than alarm SP
    {
        client.publish("Argon_1 Moisture Alarm", "Low");                        //MQTT publish alarm
        Particle.publish("Argon_1 Moisture Alarm", "Low");                      //publish IFTTT trigger
        //Moisture range:
        //0 - 300 : dry soil
        //300 - 700 : humid soil
        //700 - 950 : in water
    } 
    else
    {
        client.publish("Argon_1 Moisture Alarm", "Normal");                     //MQTT publish alarm
    }
}

void humiditySensor(int humidityLoSP)                                           //routine for humidity data
{
    humidity = dht.getHumidity();                                               //map analog reading to variable
    String humidityString = String::format ("%.1f", humidity);                  //convert to string and format
    String humiditySPString = String(humidityLoSP);                             //map setpoint to string

    client.publish("Argon_1 Humidity", humidityString);                         //MQTT publish data
    client.publish("Argon_1 Humidity SP", humiditySPString);                    //MQTT publish setpoint

    if (humidity < humidityLoSP)                                                //if less than alarm SP
    {
        client.publish("Argon_1 Humidity Alarm", "Low");                        //MQTT publish alarm
        Particle.publish("Argon_1 Humidity Alarm", "Low");                      //publish IFTTT trigger
        //Humidity Range: 0-100%RH
        //40 needs more water
        //50 - 70 ideal
        //>90 too moist
    }
    else
    {
        client.publish("Argon_1 Humidity Alarm", "Normal");                     //MQTT publish alarm
    }
}

void loop()                                                                     //call routines
{
    
    if (client.isConnected())
    {
        lightSensor(lightLoSP); 
        delay(2000);
        humiditySensor(humidityLoSP);    
        delay(2000);
        tempSensor(tempHiSP);
        delay(2000);
        moistureSensor(moistureLoSP);
        delay(5000);
    }
    client.loop();
};