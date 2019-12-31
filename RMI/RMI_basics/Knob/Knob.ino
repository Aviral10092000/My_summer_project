
#include <Servo.h>

Servo servo1;

int pin = A0;
int val;    
void setup()
{
 servo1.attach(9);
}
void loop() 
{
  val = analogRead(pin);            
  val = map(val, 0, 1023, 0, 180);   
  servo1.write(val);
  delay(15);
}
