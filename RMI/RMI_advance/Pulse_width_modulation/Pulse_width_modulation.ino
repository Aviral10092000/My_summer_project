#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
int start = 0;
int count = 0;
int factor_for_duty_cycle = 0;
ISR(INT0_vect)
{
  if(count==0)
  {
    factor_for_duty_cycle = micros() - start;
    count = 1;
  }
  else
  {
    int time_period = (micros()-start);
    float frequency = (1/time_period)*(.000001);
    count = 0;
    float percentage = (factor_for_duty_cycle)/time_period;
    start = micros();
    //Serial.println(frequency);
    //Serial.println(percentage);
  }
}
int Potentiometer(int Ax)
{
  int x;
  ADMUX = Ax;//Beginnig A0;
  ADMUX |= (1<<REFS0);// used to determine what reference voltage source to be used for AD conversion
  ADMUX &= ~(1<<ADLAR);//Right justified
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//Prescalar so as data can be detected
  ADCSRA |= (1<<ADEN);//ADC is turned on by setting this bit to logic 1 and turned off by writing logic 0.
  ADCSRA |= (1<<ADSC);//Start conversion
  while(ADCSRA & (1<<ADSC));//Conversion
  x = ADCL;// Reading values
  x = (ADCH<<8) + x;
  return x;
}
int main()
{
  Serial.begin(9600);
  EICRA = (1<<ISC01);
  EIMSK = (1<<INT0);
  sei();
  DDRD = 0b00001000;
  PORTD = 0b00001100;
  TCCR2A = _BV(COM2A0)|_BV(COM2B1)|_BV(WGM21)|_BV(WGM20);
  TCCR2B = _BV(WGM22)|_BV(CS22);
  while(1)
  {
    int A0 = Potentiometer(0);
    int A1 = Potentiometer(1);
    //Serial.println(A0);
    float number_1 = (A0)*255;
    Serial.println(A0);
    number_1 = number_1/1023;
    OCR2A = number_1;
    //Serial.println(number_1);
    number_1 = (A1)*255;
    number_1 = number_1/1023;
    OCR2B = number_1;
    //Serial.println(OCR2A);
    //Serial.println(OCR2B);
    //Serial.println(number_1);
    //number_2 = number_2/1023;
    //OCR2A = number_1;
    //OCR2B = number_2;
    //Serial.println(number_1);
    //Serial.println(number_2);
    //start = micros();
    //delayMicroseconds(1000);
  }
}
