 bool solarPanelState;
  unsigned short batteryLevel;
  unsigned short powerConsumption;
  unsigned short powerGeneration;
  bool fuelLow;
  bool batteryLow;
  unsigned short fuelLevel;
  unsigned int thrusterCommand;

  powerSubsystemData psd;
  satelliteComsData sd;
  
void setup() {
  Serial.println("Status :");
  Serial.begin(9600);
  // put your setup code here, to run once:
  solarPanelState = false;
  batteryLevel = 100;
  powerConsumption = 0;
  powerGeneration = 0;
  cycle = 1;
  reverse = 0;
  fuelLow = false;
  batteryLow = false;
  fuelLevel = 100;
  thrusterCommand = 0;

  Serial.println("Status :");
  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
  psd.powerConsumption = &powerConsumption;
  psd.powerGeneration = &powerGeneration;
  sd.fuelLow = &fuelLow;
  sd.batteryLow = &batteryLow;
  sd.solarPanelState = &solarPanelState;
  sd.batteryLevel = &batteryLevel;
  sd.fuelLevel = &fuelLevel;
  sd.powerConsumption = &powerConsumption;
  sd.powerGeneration = &powerGeneration;
  sd.thrusterCommand = &thrusterCommand;
  
/*  Serial.println("CYCLE");
  Serial.println(cycle);
  Serial.println("LIST");
    Serial.println("SOLAR PANEL STATE :");
  Serial.println(*psd.solarPanelState);
    Serial.println("BATTERY LEVEL");
  Serial.println(*psd.batteryLevel);
  Serial.println("POWER CONSUMPTION");
  Serial.println(*psd.powerConsumption);
  Serial.println("POWER GENERATION");
  Serial.println(*psd.powerGeneration);*/

}

void loop() {
   // Serial.println("Status :");
  // put your main code here, to run repeatedly:
 //  powerSubsystem( psd);
 /* Serial.println("CYCLE");
  Serial.println(cycle);
  Serial.println("LIST");
    Serial.println("SOLAR PANEL STATE :");
  Serial.println(*psd.solarPanelState);
    Serial.println("BATTERY LEVEL");
  Serial.println(*psd.batteryLevel);
  Serial.println("POWER CONSUMPTION");
  Serial.println(*psd.powerConsumption);
  Serial.println("POWER GENERATION");
  Serial.println(*psd.powerGeneration);*/
  delay(100);
  satelliteComs(sd);
  cycle++;
}
