
// Struct containing all data relevant to warning alarm system
typedef struct earthData { 
  bool* fuelLow1;
  bool* batteryLow1;
  float* fuelLevel1;
  bool* solarPanelState1;
  unsigned short* powerConsumption1;
  unsigned short* powerGeneration1;
  unsigned  short* batteryLevel1;
  unsigned short* batteryTemp1;
  unsigned short* batteryTemp21;
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

void goodDelay1() {
 while (!Serial.available()) {
 }
  if((int) Serial.peek() < 64) {
  Serial.read();
   goodDelay();
 }
}
void earth(void* d) {

  Serial.println("\n***Running Earth Function***");
  earthData* EarthData = (earthData*) d;
  Serial.println("Earth station what is your command?");

  while(Serial.available() > 0) {
     Serial.read();
  }
  goodDelay1();
  *EarthData->earthCommand1 = Serial.read();
  Serial.print("Fuel Low: ");
  Serial.println(*EarthData->fuelLow1);
  Serial.print("Battery Low: ");
  Serial.println(*EarthData->batteryLow1);
  Serial.print("Solar Panel State: ");
  Serial.println(*EarthData->solarPanelState1);
  Serial.print("Fuel Level: ");
  Serial.println(*EarthData->fuelLevel1);
  Serial.print("Power Consumption: ");
  Serial.println(*EarthData->powerConsumption1);
  Serial.print("Power Generation: ");
  Serial.println(*EarthData->powerGeneration1);
  Serial.print("Battery Level: ");
  Serial.println(*EarthData->batteryLevel1);
  Serial.print("Battery Temp: ");
  Serial.print(*EarthData->batteryTemp1);
  Serial.print(", ");
  Serial.println(*EarthData->batteryTemp21);
  Serial.print("Transport Distance: ");
  Serial.println(*EarthData->transportDist1);
  Serial.print("Image Data: ");
  Serial.println(*EarthData->imageData1);
}
