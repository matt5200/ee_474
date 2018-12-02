
// Struct containing all data relevant to warning alarm system
typedef struct earthData { 
  unsigned  short* batteryLevel1;
  
  float* fuelLevel1;
  unsigned short* powerConsumption1;
  unsigned short* powerGeneration1;
  unsigned short* batteryTemp1;
  bool* fuelLow1;
  bool* batteryLow1;
  bool* solarPanelState1;
  float* transportDist1;
  char* earthCommand1;
  char* satResponse1;
  int* imageData1;
} earthData;


earthData ed;

void goodDelay() {
 while (!Serial1.available()) {
 }
  if((int) Serial1.peek() < 64) {
  Serial1.read();
   goodDelay();
 }
}
void earth(void* d) {

  earthData* EarthData = (earthData*) d;
  Serial.println("What is earth command??");

  while(Serial.available() > 0) {
     Serial.read();
  }
  goodDelay();
  command = Serial.read();
  Serial.print("Fuel Low: ");
  Serial.println(*EarthData->fuelLow1);
  Serial.print("Battery Low :");
  Serial.println(*EarthData->batteryLow1);
  Serial.print("Solar Panel State :");
  Serial.println(*EarthData->solarPanelState1);
  Serial.print("Fuel Level");
  Serial.println(*EarthData->fuelLevel1);
  Serial.print("Power Consumption");
  Serial.println(*EarthData->powerConsumption1);
  Serial.print("Power Generation");
  Serial.println(*EarthData->powerGeneration1);
  Serial.print("Battery Level");
  Serial.println(*EarthData->batteryLevel1);
  Serial.print("Battery Temp");
  Serial.println(*EarthData->batteryTemp1);
  Serial.print("Transport Distance");
  Serial.println(*EarthData->transportDist1);
  Serial.print("Image Data");
  Serial.println(*EarthData->imageData1);
}