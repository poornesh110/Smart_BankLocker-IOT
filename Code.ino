
#include<Adafruit_MQTT_Client.h>
#include<ESP8266WiFi.h>

#define wifi_name "Poornesh"
#define pwd "123456789"
#define server "io.adafruit.com"
#define port 1883
#define username "CodeBlue619"
#define aiokey "aio_IHHY39GeprI8M9XjQc4IhTX9jzOw"

WiFiClient IoT;

Adafruit_MQTT_Client mqtt(&IoT, server,port,username,aiokey);
Adafruit_MQTT_Publish feed= Adafruit_MQTT_Publish(&mqtt, username"/feeds/Home_Security");
Adafruit_MQTT_Publish feed2= Adafruit_MQTT_Publish(&mqtt, username"/feeds/LDR_Sensor_Data");

const int ledpin = D3;
const int trigPin = D5;
const int echoPin = D6;
const int ldrpin = A0;
const int pirpin = D1;

long duration;
int distance;
int Security_flag = 0;   //variable to publish data once when the door is opened
int LDR_flag = 0;       //variable to publish light status once


void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output to send the ultrasonic signals
  pinMode(echoPin, INPUT);  // Sets the echo pin as input to recieve back signals
  pinMode(ledpin,OUTPUT);   // Sets the led pin as output to make on/off
  pinMode(ldrpin,INPUT);    // Sets the ldr pin as input to get the light intensity
  pinMode(pirpin,INPUT);    // Sets the pir pin as input to get motion status
  Serial.begin(9600);     // Starts the serial communication
  WiFi.begin(wifi_name,pwd);  // Begin Wifi connection to the local network

// while wifi is not connected it will print ...   
  while(WiFi.status () != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
// if connected to wifi then print ip address
  Serial.println(WiFi.localIP());
// while not connected to adafruit mqtt server then print ..   
  while(mqtt.connect())
  {
    Serial.print(".");
  }
}

void loop() {
// if connected to adafruit server
  if (mqtt.connected()){
    digitalWrite(trigPin, LOW);  //set the trigger pin to low that means don't send the signal 
    delayMicroseconds(2);        //waits for 2 microseconds

    digitalWrite(trigPin, HIGH);  //set the trigger pin to high to send the ultrasonic signals
    delayMicroseconds(10);         //for 10 microseconds
    digitalWrite(trigPin, LOW);   //make the trigger pin to low after 10 microseconds

// listen to that signal with echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

// Calculating the distance
    distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

  //if the distance is within the range of 26 and 32    
    if(distance > 20 && distance < 28){
      if (Security_flag == 0){
      feed.publish(distance); // publish data to adafruit homesecurity feed
      Security_flag = 1;         // set security_flag to 1 and publish once
      }                   
      Serial.println("Door is Opened");    
      delay(10);
    }
    else{
      Serial.println("Door is Closed");
      delay(10);
    }

    int ldrvalue = analogRead(ldrpin);    //Read the data from ldr sensor from analog (A0) pin
    int pirvalue = digitalRead(pirpin);   //Read the data from pir sensor
    int state = 0;
    Serial.println(ldrvalue);
    Serial.println(pirvalue);

    if (ldrvalue <= 350 && pirvalue == HIGH){    // if the ldr sensitivity is low and also if pir sensor detects motion
      state = 1;                                // Set led bulb state as 1
      digitalWrite(ledpin,HIGH);                // set the led pin to high to turn on the light
      if (LDR_flag == 0){                          
        feed2.publish(state);              // publish the data to adafruit ldr_sensor_data feed once
        LDR_flag = 1;
      }      
      delay(10000);
    }
    else{
      state = 0;                      //Set the state as 0 if ldr sensitivity is high
      digitalWrite(ledpin,LOW);       // set the lep pin to low to turn off the light
      if (LDR_flag == 1){
        feed2.publish(state);    //publish the data to adafruit ldr_sensor_data feed once
        LDR_flag = 0;
      }     
      delay(10);
    }
  delay(2000);
  }
}
