

// Struct containing all data relevant to warning alarm system
typedef struct earthData { 
  unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  float *transportDist;
  unsigned int* imageData;
  char earthCommand;
  char satResponse;
} earthData;

void earth(void* r) {
  earthData*  = (earthData*) d;
  Serial.println("What is earth command??");
  while(Serial.availible() > 0) {
     Serial.read();
  }
  goodDelay();
  command = Serial.read();
  Serial.print("Fuel Low: ");
  Serial.println(rdc->fuelLow);
  Serial.print("Battery Low :");
  Serial.print(rdc->batteryLow);
  Serial.print("Solar Panel State :");
  Serial.print(rdc->solarPanelState);
  Serial.print();
  Serial.print(rdc->fuelLevel);
  Serial.print();
  Serial.print(rdc->powerConsumption);
  Serial.print();
  Serial.print(rdc->powerGeneration);
  Serial.print();
  Serial.print(rdc->batteryLevel);
  Serial.print();
  Serial.print(rdc->batteryTemp);
  Serial.print();
  Serial.print(rdc->transportDistance);
  Serial.print();
  Serial.print(rdc->imageData);
}
