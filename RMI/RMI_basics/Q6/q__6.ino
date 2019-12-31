String a;
int x = 0;
int m = 0;
void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(6000);

}

void loop() 
{
  a = Serial.readString();
  int b = a.length();
  for(int i=1;i<=b;i++)
  {
    if(b%i==0)
    {
      for(int j=0;j<b-i;j = j + i)
      {
        for(int k=0;k<i;k++)
        {
          if(a[j+k]!=a[j+i+k])
          {
            m = 1;
            break;
          }
        }
        if(m==1)
        {
          m = 0;
          break;
        }
        else
        {
          int o = x;
          x = i;
          if(x==2*o)
          {
            for(int j=0;j<o;j++)
            {
              if(a[j]==a[o+j]&&j==o-1)
              {
                x = o;
              }
            }
          }
        }
      }
    }
  }
  for(int i=0;i<x;i++)
  Serial.print(a[i]);
  Serial.println();
}
