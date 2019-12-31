void setup() {
  pinMode(9,OUTPUT);
  
}
void loop() {
int count = 0;
long long unsigned int start = micros();
while(1) {
if (micros() - start >= 13) {
    start = micros();
    if(count==0)
    {
      digitalWrite(9,0);
      count = 1;
    }
    else
    {
      digitalWrite(9,1);
      count = 0;
    }
    
}
}
}
