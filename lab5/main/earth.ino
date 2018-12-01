

// Struct containing all data relevant to warning alarm system
typedef struct void earthData { 
  unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  float *transportDist;
  unsigned int* imageData;
} remoteData;

void earth(void* r) {

  remoteData* rdc = (warningAlarmData*) d;
  Serial.print(rdc->fuelLow);
  Serial.print(rdc->batteryLow);
  Serial.print(rdc->solarPanelState);
  Serial.print(rdc->fuelLevel);
  Serial.print(rdc->powerConsumption);
  Serial.print(rdc->powerGeneration);
  Serial.print(rdc->batteryLevel);
  Serial.print(rdc->batteryTemp);
  Serial.print(rdc->transportDistance);
  Serial.print(rdc->imageData);
}
