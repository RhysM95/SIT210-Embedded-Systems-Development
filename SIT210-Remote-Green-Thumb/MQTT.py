import paho.mqtt.client as mqtt                     #import libraries
import time as t                                        
from tkinter import *
data_dict =  {}
         
def messageFunction (client, userdata, message):    #recieve MQTT data
    topic = str(message.topic)
    message = str(message.payload.decode("utf-8"))
    print(topic + " " + message)
                                                    #light data
    if topic == "Argon_1 Light Level":
        light = float(message)
        light_data = str('Light level = ' + message)
        data_dict['Light'] = light_data
                                                    #light alarm
    elif topic == "Argon_1 Light Alarm":
        light_Al = str(message)
        data_dict['LightAl'] = light_Al
                                                    #temp data
    elif topic == "Argon_1 Temperature":
        temp = float(message)
        temp_data = str('Temperature = ' + message)
        data_dict['Temp'] = temp_data
                                                    #temp alarm        
    elif topic == "Argon_1 Temperature Alarm":
        temp_Al = str(message)
        data_dict['TemperatureAl'] = temp_Al
                                                    #moisture data
    elif topic == "Argon_1 Moisture":
        moisture = float(message)
        moisture_data = str('Moisture Level = ' + message)
        data_dict['Moisture'] = moisture_data       
                                                    #moisture alarm
    elif topic == "Argon_1 Moisture Alarm":
        moisture_Al = str(message)
        data_dict['MoistureAl'] = moisture_Al
                                                    #humidity data
    elif topic == "Argon_1 Humidity":
        humidity = float(message)
        humidity_data = str('Humidity Level = ' + message)
        data_dict['Humidity'] = humidity_data                                             
                                                    #humidity alarm
    elif topic == "Argon_1 Humidity Alarm":
        humidity_Al = str(message)
        data_dict['HumidityAl'] = humidity_Al
                                                    #light setpoint
    elif topic == "Argon_1 Light SP":
        light_SP = str(message)
        data_dict['LightSP'] = light_SP
                                                    #temp setpoint
    elif topic == "Argon_1 Temperature SP":
        temp_SP = str(message)
        data_dict['TempSP'] = temp_SP
                                                    #moisture setpoint
    elif topic == "Argon_1 Moisture SP":
        moisture_SP = str(message)
        data_dict['MoistureSP'] = moisture_SP
                                                    #humidity setpoint
    elif topic == "Argon_1 Humidity SP":
        humidity_SP = str(message)
        data_dict['HumiditySP'] = humidity_SP
    
Client = mqtt.Client("Rhysm_mqtt")                  #create a MQTT client object
Client.connect("test.mosquitto.org", 1883)          #connect to the test MQTT broker
                                                    #subscribe to events
Client.subscribe("Argon_1 Light Level")             
Client.subscribe("Argon_1 Temperature")            
Client.subscribe("Argon_1 Moisture")               
Client.subscribe("Argon_1 Humidity")               
Client.subscribe("Argon_1 Light Alarm")  
Client.subscribe("Argon_1 Temperature Alarm")             
Client.subscribe("Argon_1 Moisture Alarm")         
Client.subscribe("Argon_1 Humidity Alarm")
Client.subscribe("Argon_1 Light SP")  
Client.subscribe("Argon_1 Temperature SP")             
Client.subscribe("Argon_1 Moisture SP")         
Client.subscribe("Argon_1 Humidity SP") 

Client.on_message = messageFunction                 
Client.loop_start()                                 #start the MQTT client

def update_data():                                  #update data
    updated_light = str(data_dict.get('Light'))
    light.configure(text = updated_light + " LUX")
    updated_temp = str(data_dict.get('Temp'))
    temp.configure(text = updated_temp + " ℃")
    updated_humidity = str(data_dict.get('Humidity'))
    humidity.configure(text = updated_humidity + " %RH")
    updated_moisture = str(data_dict.get('Moisture'))
    moisture.configure(text = updated_moisture + " mg/L")
    updated_time = t.strftime("Time: %H:%M:%S.", t.localtime())
    time.configure(text = updated_time)
    
    if data_dict.get('LightAl') == "Dark":
        light.configure(bg="red")
        updated_light2 = str(data_dict.get('LightSP'))
        light2.configure(text = "Light Level < " + updated_light2)
    elif data_dict.get('LightAl') == "Light":
        light.configure(bg="green")
        light2.configure(text = "Light Level is Normal")
        
    if data_dict.get('TemperatureAl') == "High":
        temp.configure(bg="red")
        updated_temp2 = str(data_dict.get('TempSP'))
        temp2.configure(text = "Temperature Level > " + updated_temp2)
    elif data_dict.get('TemperatureAl') == "Normal":
        temp.configure(bg="green")
        temp2.configure(text = "Temperature Level is Normal")
        
    if data_dict.get('MoistureAl') == "Low":
        moisture.configure(bg="red")
        updated_moisture2 = str(data_dict.get('MoistureSP'))
        moisture2.configure(text = "Moisture Level < " + updated_moisture2)
    elif data_dict.get('MoistureAl') == "Normal":
        moisture.configure(bg="green")
        moisture2.configure(text = "Moisture Level is Normal")

    if data_dict.get('HumidityAl') == "Low":
        humidity.configure(bg="red")
        updated_humidity2 = str(data_dict.get('HumiditySP'))
        humidity2.configure(text = "Humidity Level < " + updated_humidity2)
    elif data_dict.get('HumidityAl') == "Normal":
        humidity.configure(bg="green")
        humidity2.configure(text = "Humidity Level is Normal")

    window.after(1000, update_data)

                                                        #draw window
window = Tk()
window.geometry("480x300")
window.title("Argon Data Logger")
light = Label(window, text=str(data_dict.get('Light')),fg="white",bg="black",width=25,height=1)
light.place(relx=0.05, rely=0.20)
temp = Label(window, text=str(data_dict.get('Temp')),fg="white",bg="black",width=25,height=1)
temp.place(relx=0.05, rely=0.40)
humidity = Label(window, text=str(data_dict.get('Moisture')),fg="white",bg="black",width=25,height=1)
humidity.place(relx=0.05, rely=0.60)
moisture = Label(window, text=str(data_dict.get('Humidity')),fg="white",bg="black",width=25,height=1)
moisture.place(relx=0.05, rely=0.80)
time = Label(window, text=t.strftime("Time: %H:%M:%S.", t.localtime()),fg="white",bg="black",width=13,height=1)
time.place(relx=0.78, rely=0.93)
light2 = Label(window, text=("Gathering Data"),fg="white",bg="black",width=25,height=1)
light2.place(relx=0.55, rely=0.20)
temp2 = Label(window, text=("Gathering Data"),fg="white",bg="black",width=25,height=1)
temp2.place(relx=0.55, rely=0.40)
humidity2 = Label(window, text=("Gathering Data"),fg="white",bg="black",width=25,height=1)
humidity2.place(relx=0.55, rely=0.60)
moisture2 = Label(window, text=("Gathering Data"),fg="white",bg="black",width=25,height=1)
moisture2.place(relx=0.55, rely=0.80)
window.after(1000, update_data)

window.mainloop()