
// Struct containing all data relevant to remote data computer

typedef struct remoteData { 

  unsigned short* batteryTemperature;
  unsigned short* batteryTemperature2;
  unsigned  short* batteryLevel;
  float* fuelLevel;
  unsigned short* powerConsumption;
  bool* fuelLow;
  bool* batteryLow;
  bool* solarPanelState;
  float* transportDist;
  int* imageData;
} remoteData;

remoteData rd;


void remoteDataComputer(void* d) {
  
  Serial.println("\n***Remote Data Computer***");
  remoteData* rdc = ( remoteData* ) d;
  if (!displayOff) {
  tft.setTextColor(BLUE); 
  tft.setCursor(0, 60 + 30);
  tft.print("Remote Data System");
  tft.setCursor(0, 75 + 30);
  tft.print("Satellite: Alfred");
  tft.setCursor(0, 90 + 30);
  tft.print("Date: ");
  tft.println(__DATE__);
  
  tft.setCursor(0, 105 + 30);
  tft.print("Operators: Matt, Kiri");
  tft.fillRect(0, 120 + 30,200,150, BLACK);
  tft.setCursor(0, 120 + 30);
  tft.print("Fuel Low: ");
  tft.println(*rdc->fuelLow);
  
  tft.setCursor(0, 135 + 30);
  tft.print("Battery Low: ");
  tft.println(*rdc->batteryLow);
  
  tft.setCursor(0, 150 + 30);
  tft.print("Solar Panel State: ");
  tft.println(*rdc->solarPanelState);
  
  tft.setCursor(0, 165 + 30);
  tft.print("Battery Level: ");
  tft.println(*rdc->batteryLevel);
  
  tft.setCursor(0, 180 + 30);
  tft.print("Fuel Level: ");
  tft.println(*rdc->fuelLevel);
  
  tft.setCursor(0, 195 + 30);
  tft.print("Power Consumption: ");
  tft.println(*rdc->powerConsumption);
  
  tft.setCursor(0, 210 + 30);
  tft.print("Battery Temperature: ");
  tft.print(*rdc->batteryTemperature);
  tft.print(", ");
  tft.println(*rdc->batteryTemperature2);
  
  tft.setCursor(0, 225 + 30);
  tft.print("Transport Distance: ");
  tft.println(*rdc->transportDist);
  
  tft.setCursor(0, 240 + 30);
  tft.print("Image data: ");
  tft.println(*rdc->imageData);
  }
}
