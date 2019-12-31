/*
 * Author: Aviral Verma (107118021), EEE - Nitt.
   Domain: Spider Tronix
   Sub-Domain - IOT
   Functions: callback(),setup(),loop()
   Global Variable:
   long unsigned int duration;
   float distance;
   const char* mqttServer = "m24.cloudmqtt.com";
   const int mqttPort = 11206;
   int flag = 1;
   const char* mqttUser = "yykncekw";
   const char* mqttPassword = "bWUv102S7mRG";
   WiFiClient espClient;
   PubSubClient client(espClient);
   IOT server - CloudMQTT
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
// defines pins numbers
const int trigPin = 12;  //D2
const int echoPin = 5;  //D1

// defines variables
long unsigned int duration;
float distance;
const char* mqttServer = "m24.cloudmqtt.com";
const int mqttPort = 11206;
int flag = 1;
const char* mqttUser = "yykncekw";
const char* mqttPassword = "bWUv102S7mRG";
WiFiClient espClient; // Generating Client
PubSubClient client(espClient); //Creating Client object
/*
 * Function Name: callback();
 * Input: topic,payload,length
 * Output: Print messages
 * Logic: When broker sends a message, this function is called automatically
 */
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
  Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
WiFi.begin("Redmi", "Arvind123");
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print("Connecting to WiFi..");
}
 
Serial.println("Connected to the WiFi network");

//Connecting to the server
client.setServer(mqttServer, mqttPort);

//Callback is a function. Whenevr a message is arrived from the broker, it will be immediately called
client.setCallback(callback);
while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
 
    }
}

//Publishing the message via "esp/test" channel (or topic)
client.publish("esp/test", "Hello from ESP8266");

//Subscribing the channel
client.subscribe("esp/test");


}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(1000);

//Wave have been generated
digitalWrite(trigPin, LOW);
delayMicroseconds(50);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
Serial.println(duration);

//Calculating the distance
distance= (duration*0.034);
distance = distance/2;

// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);


if(distance>32)
{
  client.publish("esp/test1","empty");
  flag = 1;
}
else if(distance<15)
{
  client.publish("esp/test1","full");
  flag = 1;
}
else if(flag)
{
  client.publish("esp/test1","not Filled");
  flag = 0;
}

char dist[20];

//itoa is a function which is used for converting an integer to an array
itoa(distance, dist,10);
client.publish("esp/test", dist);
delay(1000);

client.loop();
}
