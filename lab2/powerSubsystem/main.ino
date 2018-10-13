  bool solarPanelState;
  unsigned short batteryLevel;
  unsigned short powerConsumption;
  unsigned short powerGeneration;
  int* cycle;
  int* reverse;
  powerSubsystemData* psd;
  
void setup() {
  // put your setup code here, to run once:
  solarPanelState = false;
  batteryLevel = 100;
  powerConsumption = 0;
  powerGeneration = 0;
  *cycle = 1;
  *reverse = 0;

  psd->solarPanelState = &solarPanelState;
  psd->batteryLevel = &batteryLevel;
  psd->powerConsumption = &powerConsumption;
  psd->powerGeneration = &powerGeneration;

}

void loop() {
  // put your main code here, to run repeatedly:
  powerSubsystem(psd, cycle, reverse);
  Serial.println("Status :");
  Serial.println(*psd->solarPanelState);
  Serial.println(solarPanelState);
  *cycle++;
}
