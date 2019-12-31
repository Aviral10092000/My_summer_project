class nutrient_tank_parameters
{
  private:
  float electrical_conductivity_tank;
  float pH_tank;
  float temperature_tank;
  public:
  void set_parmeters(float EC, float pH, float temperature)
  {
    electrical_conductivity_tank = EC;
    pH_tank = pH;
    temperature_tank = temperature;
  }
  float check_electrical_conductivity()
  {
    if(electrical_conductivity_tank>=5.8 && electrical_conductivity_tank<=6.3)
    {
      return 0.0;
    }
    else if((electrical_conductivity_tank<=5.5 && electrical_conductivity_tank>=6.5))
    {
      //stop_and_indicate()
      return 0.0;
    }
    else
    {
      //add_nutrients(electrical_conductivity_tank);
      return 0.0;
    }
  }
  
};


void setup() 
{
    
}

void loop() 
{
  
}
