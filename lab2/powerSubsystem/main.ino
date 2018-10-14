 bool solarPanelState;
  unsigned short batteryLevel;
  unsigned short powerConsumption;
  unsigned short powerGeneration;

  powerSubsystemData psd;
  
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
  Serial.println("Status :");
  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
  psd.powerConsumption = &powerConsumption;
  psd.powerGeneration = &powerGeneration;
  Serial.println("CYCLE");
  Serial.println(cycle);
  Serial.println("LIST");
    Serial.println("SOLAR PANEL STATE :");
  Serial.println(*psd.solarPanelState);
    Serial.println("BATTERY LEVEL");
  Serial.println(*psd.batteryLevel);
  Serial.println("POWER CONSUMPTION");
  Serial.println(*psd.powerConsumption);
  Serial.println("POWER GENERATION");
  Serial.println(*psd.powerGeneration);

}

void loop() {
    Serial.println("Status :");
  // put your main code here, to run repeatedly:
   powerSubsystem( psd);
  Serial.println("CYCLE");
  Serial.println(cycle);
  Serial.println("LIST");
    Serial.println("SOLAR PANEL STATE :");
  Serial.println(*psd.solarPanelState);
    Serial.println("BATTERY LEVEL");
  Serial.println(*psd.batteryLevel);
  Serial.println("POWER CONSUMPTION");
  Serial.println(*psd.powerConsumption);
  Serial.println("POWER GENERATION");
  Serial.println(*psd.powerGeneration);
  Serial.println("\n\n");
  delay(100);
  cycle++;
}
