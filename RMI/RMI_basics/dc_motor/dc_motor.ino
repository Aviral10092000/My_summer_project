const int signalPin = 7;
const int triggerPin = 8;
const int signalOutPin = A1;
long signal_1, inches,centimeters;
const int p1 = 12;
const int p2 = 13;
void setup()
{
  pinMode(signalPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  Serial.begin(9600);
}
void loop() 
{
  digitalWrite(13, 1);
  digitalWrite(triggerPin,0);
  delayMicroseconds(2);
  digitalWrite(triggerPin,1);
  delayMicroseconds(10);
  digitalWrite(triggerPin,0);
  signal_1 = pulseIn(signalPin,1);
  Serial.println(signal_1);
  inches = signal_1/148;//calibration
  centimeters = inches*2.54;//calibration
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(centimeters);
  Serial.print("cm");
  Serial.println();
  if(centimeters>200)
  centimeters = 200;
  int volt = map(centimeters,0,200,255,0);
  Serial.println(volt);
  digitalWrite(p1, 1);
  digitalWrite(p2, 0);
  analogWrite(9,volt);
  delay(500);
}
