#include <avr/io.h>
#include <stdint.h>
/*
 * Author Name = Aviral Verma
 * Domain = Tronix
 * Task = 0
 * const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
   int Flag1 = 0;
   int Flag2 = 0;
   float Voltage;
   float Resistance;
 */
void delay(int);
void cmd (char);
void display (char);
void custom (void);
void init (void);
unsigned char custom_char[16]= {" AVIRAL VERMA "};
unsigned char custom_char_1[16] = {"     Spider    "};
unsigned char cap[10] = {"Capictance"};
unsigned char ohm[8] = {"Resistor"};
unsigned char volt[7] = {"Voltage"};
unsigned char amphere[7] = {"Amphere"};
const int rs = 12, en = 11, d0 = 7, d1 = 6, d2 = 5, d3 = 4, d4 = 3, d5 = 2, d6 = 1, d7 = 0;//For reference // rs is register pin, en is enable pin, d0-d7 data input pins.
int Flag1 = 0;
int Flag2 = 0;
float Voltage = 0;
float Resistance = 1;
void delay (int d)
{
  unsigned char i;
  // delay is define here
  for(;d>0;d--)
  {
    for(i=250;i>0;i--)
    for(i=248;i>0;i--);
  }// Setting delay
}
void init (void)
{
 
  // look in data sheet before referring here,
  cmd(0x0f);//Switching on LCD
  cmd(0x01);//Clearing the screen;
  cmd(0x38);//Use two lines and 5x7 matrix
  cmd(0x0c);//Force cursor to beginning of second line
  cmd(0x01);//Clearing the screen;
  cmd(0x80);//Force cursor to beginning of the first line
}
void cmd (char c)
{
  //For Commanding, the rs pin should be low, en pin first high then low 
  PORTD=c;
  PORTB = B00001000;
  delay(5);
  PORTB = B00000000;
}
void display (char c)
{
  //For Displaying, the rs pin should be High, en pin first high then low
  PORTD = c;
  PORTB = B00011000;
  delay(5);
  PORTB = B00010000;
}
void custom (void)
{
  int k;
  cmd(0x80);
  for(k=0;k<16;k++)
  display(custom_char[k]);
  cmd(0xC0);
  for(k=0;k<16;k++)
  display(custom_char_1[k]);
  cmd(0x80);
}
void capictance (void)
{
  int k;
  cmd(0x80);
  for(k=0;k<10;k++)
  display(cap[k]);
  cmd(0xC0);
}
int capacitor_analog(int A0)
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
int resistance_analog(int A1)
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
int voltage_analog(int A3)
{
  //For logic look up
  int z;
  ADMUX = A3;
  ADMUX |= (1<<REFS0);
  ADMUX &= ~(1<<ADLAR);
  ADCSRA |= (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
  ADCSRA |= (1<<ADEN);
  ADCSRA |= (1<<ADSC);
  while(ADCSRA & (1<<ADSC));
  z = ADCL;
  z = (ADCH<<8) + z;
  return z;
}
void Resistor(void)
{
  int k;
  cmd(0x80);
  for(k=0;k<7;k++)
  display(ohm[k]);
  cmd(0xC0);
}
void amp (void)
{
  int k;
  cmd(0x80);
  for(k=0;k<7;k++)
  display(ohm[k]);
  cmd(0xC0);
}
int main()
{
  DDRD = B00000000;//This is done for OR operation
  DDRB = B00000000;//This is done for OR operation
  DDRC = B00000000;//This is done for OR operation
  DDRD = DDRD | B11111111;// Set all pins as output
  DDRB = DDRB | B00011001;//12,11 and 8 are set as output;
  init();// Beginning the LCD
  custom();// Initial Values
  PORTB = B00000100;
  int x = capacitor_analog(0);
  int y = resistance_analog(1);
  int z = voltage_analog(3);
  //(10000000);
  if(x>100)// On beginning x = 1023 so x>100 is a good option
  {
    /*
   * Logic of RC circuit
   * Time constant = R*C;
   * Voltage across capictor will be about .63*(Applied Voltage) during charging
   * So i measured this
   * Three resistance of 30000ohm is used, so as to increase time constant and measure can be shown on Serial Monitor
   * For proper logic, See folder 
   */
    float estimated_time = 0;
    while(x>648)
    {
      estimated_time = estimated_time + .000011;
      x = capacitor_analog(0);
    }
    estimated_time = estimated_time*5032;// 5032 is a callibration
    int h = estimated_time * 100;
    int count = 0;
    for(;h>0;)
    {
      if(count==2)
      {
        display('.');
        count++;
        continue;
      }
      int o = h%10;//Display individual digit
      h = (h-o)/10;
      display(o+'0');
      count++;
    }
    delay(10000);
    init();// Restting it
  }
  if(z>7)
  {
    /*
   * Voltage Divider Technique
   * So Logic could be understand by code below
   * Resistance = ((5-Volt_measured)*470)/Volt_measured
   * 4.12 for calibration
   * For proper logic see folder
   */
    float Volt_measured = z/1023.0;// mapping it
    Volt_measured = Volt_measured*4.12;// 4.12 is done for calibration
    Resistance = 1.0;
    Resistance = Resistance*(4.12-Volt_measured)*470; 
    Resistance = Resistance/Volt_measured;
    Resistance = Resistance/6.65;//Calibration
    Resistor();
    int r = Resistance*100;
    int count = 0;
    // For displaying
    for(;r>0;)
    {
      if(count==2)
      {
        count++;
        display('.');
      }
      int y = r%10;
      r = (r-y)/10;
      display(y);
      count++;
    }
    delay(10000);
    init();
    Flag1 = 1;
  }
  if(y>7)
  {
    /*
   * So in this voltage is measured by simple concept of analog pin and ground
   * But for measuring voltages more than five volt, four resistances are applied which are equal
   * If cell of 20 volt is applied, each resistance can hold 5, which can be measured by arduino
   * For proper logic see folder
   */
    Voltage = y/1023.0;
    Voltage = Voltage*5;
    Voltage = Voltage*4;
    Voltage = Voltage+.38;// Calibration
    int v = Voltage*100;
    int count = 0;
    // For displaying
    for(;v>0;)
    {
      if(count==2)
      {
        count++;
        display('.');
      }
      int y = v%10;
      v = (v-y)/10;
      display(y);
      count++;
    }
  delay(10000);
  init();
  Flag2 = 1;
  }
  if(Flag1&&Flag2)
  {
   /*
   * Current = Voltage/Resistance
   * For proper logic see folder
   */
    float Current = Voltage/Resistance;
    int c = Current * 100;
    int count = 0;
    // For displaying
    for(;c>0;)
    {
      if(count==2)
      {
        count++;
        display('.');
      }
      int y = c%10;
      c = (c-y)/10;
      display(y);
      count++;
    }
    Flag1 = 0;
    Flag2 = 0;
    delay(10000);
    init();
  }
}
