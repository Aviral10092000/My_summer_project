#include<avr/io.h>
#include<avr/interrupt.h>
int count = 0;
int flag = 0;

ISR(INT0_vect)
{
  count++;
  Serial.println(count);
}

int main() 
{
  Serial.begin(9600);
  //Serial.println(1);
  DDRD=0x00;
  PORTD=B11111100;         // Enabling internal pullups
  EICRA = (1<<ISC01); // Falling edge
  EIMSK = (1<<INT0);  //Enabling Ext INT0
  sei();
  while(1)
  {
   
          
  }
  return 0;
}
