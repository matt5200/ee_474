
// Struct containing all data relevant to warning alarm system
typedef struct void remoteData { 
  unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  float *transportDist;
  unsigned int* imageData;
} remoteData;

void remoteDataComputer(void* r) {

  remoteData* rdc = (warningAlarmData*) d;
  tft.setTextColor(BLUE); 
  tft.setCursor(0, 60);
  tft.print("Remote Data System");
  tft.setCursor(0, 60);
  tft.print("Statellite: Alfred");
  tft.setCursor(0, 60);
  // TO DO:
  tft.print("Date");
  tft.setCursor(0, 60);
  tft.print("Operator: Matt, Kiri");
  tft.setCursor(0, 60);
  tft.print("Fuel Low");
  tft.setCursor(0, 60);
  tft.print("Battery Low");
  tft.setCursor(0, 60);
  tft.print("Solar Panel State");
  tft.setCursor(0, 60);
  tft.print("Battery Level");
  tft.setCursor(0, 60);
  tft.print("Fuel Level");
  tft.setCursor(0, 60);
  tft.print("Power Consumption");
  tft.setCursor(0, 60);
  tft.print("Battery Temperature");
  tft.setCursor(0, 60);
  tft.print("Transport Distance");
  tft.setCursor(0, 60);
  tft.print("Image data");
}
