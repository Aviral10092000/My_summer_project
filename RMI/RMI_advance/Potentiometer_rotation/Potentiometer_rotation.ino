#include <avr/io.h>
#include <stdint.h>
int Potentiometer_1(int A0)
{
  int x;
  ADMUX = A0;//Beginnig A0;
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
int Potentiometer_2(int A1)
{
  //For logic look up
  int y;
  ADMUX = A1;
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<ADLAR);
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  y = ADCL;
  y = (ADCH<<8) + y;
  return y;
}
int main()
{
  Serial.begin(9600);
  while(1)
  {
    float voltage;
    Serial.println("potentiometer 1");
    voltage = ((Potentiometer_1(0))*5.0)/1023.0;
    Serial.println(voltage);
    Serial.println("potentiometer 2");
    voltage = ((Potentiometer_2(1))*5.0)/1023.0;
    Serial.println(voltage);
    _delay_ms(1000);
  }
}
