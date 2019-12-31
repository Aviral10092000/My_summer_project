#include <DHT.h>

dht DHT;

#define DHT11_PIN 7

void setup(){
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  delay(1000);
}
