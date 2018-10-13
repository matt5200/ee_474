typedef struct satelliteComsData {
  bool* fuelLow;
  bool* batteryLow;
  bool* solarPanelState;
  unsigned short* batteryLevel;
  unsigned short* fuelLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
  unsigned int* thrusterCommand;
} satelliteComsData;

void satelliteComs(void* s) {
  satelliteComsData* satelliteComs = (satelliteComsData*) s;

  unsigned short left = 0;
  unsigned short right = 0;
  unsigned short up = 0;
  unsigned short down = 0;

  int r = randomInteger(0, 65535);
  *thrusterCommand = r;
  // need to convert random number to bits
  dir = r % 10;
  if (dir == 1) {
    left = 1;
  } else {
    left = 0;
  }
  r = r / 10;
  dir = r % 10;
  if (dir == 1) {
    right = 1;
  } else {
    right = 0;
  }
  r = r / 10;
  dir = r % 10;
  if (dir == 1) {
    up = 1;
  } else {
    up = 0;
  }
  r = r / 10;
  dir = r % 10;
  if (dir == 1) {
    down = 1;
  } else {
    down = 0;
  }
  r = r / 10;
  magnitude = r % 10000;
  r = r / 10000;
  duration = r;
}
