/*
   Author: Aviral Verma (107118021), EEE - Nitt.
   Domain: Spider Tronix
   Sub-Domain - IOT
   Project - TASK_2: IOT based Home Automation;
   Functions: callback(),setup(),loop()
   Global Variables:
   Servo myservo;
   int pos = 0;
   const char* mqttServer = "m24.cloudmqtt.com";
   const int mqttPort = 11177;
   byte operation = 0;
   const char* mqttUser = "tqelkjls";
   const char* mqttPassword = "WcHO_rsnBlKc";
   int Servopin = 2;
   int doorpin = 14;
   WiFiClient espClient; // Generating Client
   PubSubClient client(espClient); //Creating Client object
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

//Making a servo object
Servo myservo;

//pos for position of servo
int pos = 0;

//Variables for connecting to cloudMqtt
const char* mqttServer = "m24.cloudmqtt.com";
const int mqttPort = 11177;
byte operation = 0;
const char* mqttUser = "tqelkjls";
const char* mqttPassword = "WcHO_rsnBlKc";

//Define pins for bulb and servo
int doorpin = 2;
int bulbpin = 14;

WiFiClient espClient; // Generating Client
PubSubClient client(espClient); //Creating Client object


void setup() {
  //  Attaching Servo pin
  myservo.attach(doorpin);

  // Starts the serial communication
  Serial.begin(9600);                               

  // Starts connecting to wifi
  WiFi.begin("Aviral", "10092000");                 

  //Checking the status
  while (WiFi.status() != WL_CONNECTED) { 
  delay(500);
  Serial.print("Connecting to WiFi..");
  }
  
  //Making the doorpin as output
  pinMode(doorpin, OUTPUT);   
  

  //Connecting to the server
  client.setServer(mqttServer, mqttPort);
  
  //Callback is a function. Whenevr a message is arrived from the broker, it will be immediately called
  client.setCallback(callback);

  //Checking the connection of the client
  while (!client.connected()) 
  {
      Serial.println("Connecting to MQTT...");
      if (client.connect("ESP8266Client", mqttUser, mqttPassword ))   
      {
        Serial.println("connected");  
      }
      else
      {
        Serial.print("failed with state ");
        Serial.print(client.state());
      }
    }

  //Publish and subscribing to the door and bulb topics  
  //client.publish("bulb","0");
  //client.publish("door","0");
  client.subscribe("door");
  client.subscribe("bulb");
    
}

/*
 * Function Name: callback();
 * Input: topic,payload,length
 * Output: Operates the bulb and the Servo motor
 * Logic: When broker sends a message, this function is called automatically
 */
void callback(char* topic, byte* payload, unsigned int length) 
{
  
  //Data which will recieve will be 0 or 1 so index 0 is taken
  operation = payload[0];

  //Checking the topic. If door topic arrives, it eneters the following block
  if(strcmp(topic,"door")==0)
  {
      
    if(operation==48)    //Door will open, 48 is ASCII
      {
        for (pos = 0; pos <= 90; pos += 1) 
        { 
          myservo.write(pos);              
          delay(15);
        }
      }
    
    else if(operation==49) //Door will close, 49 is ASCII
    {
          for (pos = 90; pos >= 0; pos -= 1) 
          { 
            myservo.write(pos);
            delay(15);  
          }
    }
    
  }

  //Checking the topic. If bulb topic arrives, it eneters the following block
  else if(strcmp(topic,"bulb")==0)
  {
    if(operation==48)           //Turn on the bulb
    {
      digitalWrite(bulbpin, HIGH);   
      
    }
    else if(operation==49)      //Turn off the bulb
    {
      digitalWrite(bulbpin, LOW);     
      
    }
  }

  //Setting the operation to 0
  operation = 0;
  
}
void loop() {
  
  client.loop();
  
}
