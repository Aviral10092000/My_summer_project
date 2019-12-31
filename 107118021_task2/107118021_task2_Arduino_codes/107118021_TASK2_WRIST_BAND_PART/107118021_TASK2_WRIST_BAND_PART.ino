/*
 * Author: Aviral Verma (107118021), EEE - Nitt.
   Domain: Spider Tronix
   Sub-Domain - IOT
   Functions: setup(),loop()
   Global Variable:
   String state_bulb = "ON";
   String state_mobile = "DETECTED";
   String state_door = "OPEN";
   const int bulb = 14;
   const int door = 12;  
   const char* mqttServer = "m24.cloudmqtt.com";
   const int mqttPort = 11177;
   const char* mqttUser = "tqelkjls";
   const char* mqttPassword = "WcHO_rsnBlKc";
   int flag_bulb = 0;
   int flag_door = 0;
   IOT server - CloudMQTT
*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

//Creating object of Adafruit_SSID1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Certain strings
String state_bulb = "ON";
String state_mobile = "DETECTED";
String state_door = "OPEN";

//Defining Pins for bulb and door
const int bulb = 14;
const int door = 12;  

//Variables for connecting to cloudMqtt
const char* mqttServer = "m24.cloudmqtt.com";
const int mqttPort = 11177;
const char* mqttUser = "tqelkjls";
const char* mqttPassword = "WcHO_rsnBlKc";

//Some flag variables
int flag_bulb = 0;
int flag_door = 0;

WiFiClient espClient1; // Generating Client
PubSubClient client(espClient1); //Creating Client object

void setup() {
  //Making the bulb and door as input pins
  pinMode(bulb,INPUT);
  pinMode(door,INPUT);
  
  Serial.begin(9600); // Starts the serial communication

  //Begin connection to wifi
  WiFi.begin("Aviral", "10092000");

  //Initial Display on oled screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);      //Connect to the screen
  display.clearDisplay();                         //Clear the display
  display.display();                              //Shows the display
  display.setTextSize(2);                         //Setting text size
  display.setTextColor(WHITE);                    //Setting color
  display.setCursor(20,10);                       //Set Cursor to the coordinates
  display.println(F("Spider!"));                  //Printing statements
  display.display();                              //Showing the display
  delay(2000);                                    
  display.clearDisplay();                         //Clear the display
  display.setTextSize(1.5);                       //Setting text size
  display.setTextColor(WHITE);                    //Setting color
  display.setCursor(20,10);                       //Set Cursor to the coordinates
  display.println(F("James Bond"));               //Printing statements
  display.display();                              //Showing the display
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(F("Current Status:"));          //Print Current Status
  display.println(("Bulb: " + state_bulb));       //Print bulb status
  display.println(("Door: "+state_door));         //Print door status
  display.println(("Mobile: "+state_mobile));     //Print mobile status
  display.display();


//Checking the wifi status
while (WiFi.status() != WL_CONNECTED) {
  Serial.println("Connecting");
delay(500);

}
 


//Connecting to the server
client.setServer(mqttServer, mqttPort);

//Checking the client connection
while (!client.connected()) {
    
 
    if (client.connect("ESP8266Client1", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
 
    }
}
}

void loop()
{
  //Read the state logic(0 or 1) bulb
  digitalRead(bulb);
  delay(10);

  //Any change of state will allow the following loop to execute
  if(digitalRead(bulb)^flag_bulb)
  {
    flag_bulb = !flag_bulb;

      if(flag_bulb)
      {
      display.clearDisplay();
      state_bulb = "ON";
      Serial.println("bulb on");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      client.publish("bulb","1");
      }
      else
      {
      display.clearDisplay();
      state_bulb = "OFF";
      Serial.println("bulb off");
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      client.publish("bulb","0");
    }
  }

  //Read the state logic(0 or 1) door
  digitalRead(door);
  delay(10);

  //Any change of state will allow the following loop to execute
  if(digitalRead(door)^flag_door)
  {
      flag_door = !flag_door;
      if(flag_door)
      {
      display.clearDisplay();
      state_door = "OPEN";
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      Serial.println("door on");
      client.publish("door","1");
    }
    else
    {
      display.clearDisplay();
      state_door = "CLOSED";
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      Serial.println("bulb off");
      client.publish("door","0");
    }
  }

  //Scan number of Wifi networks
  int numberOfNetworks = WiFi.scanNetworks();

  
  for(int i =0; i<numberOfNetworks; i++)
  {
    //If connected to my own wifi
    if(WiFi.SSID(i)=="Redmi")
    {

      long rssi = WiFi.RSSI(i);
      Serial.println(rssi);

      //For my redmi phone, RSSI value if greater than -54, shows detected and is around 1m
      if(rssi>-40)
      {  
      display.clearDisplay();
      state_mobile = "DETECTED";
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      break;
      }
      else  
      {
      display.clearDisplay();
      state_mobile = "NOT DETECTED";
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println(F("Current Status:"));
      display.println(("Bulb: " + state_bulb));
      display.println(("Door: "+state_door));
      display.println(("Mobile: "+state_mobile));
      display.display();
      }
    }
  }
  client.loop();
}
