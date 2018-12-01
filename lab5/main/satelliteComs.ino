// Struct containing all data for the satellite data
typedef struct satelliteComsData {
  char earthCommand;
  bool* fuelLow;
  bool* batteryLow;
  bool* solarPanelState;
  unsigned short* batteryLevel;
  float* fuelLevel;;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
  unsigned int* thrusterCommand;
} satelliteComsData;

void satelliteComs(void* s);

void satelliteComs(void* s) {
  Serial.println("FUNCTION 3");
  satelliteComsData* satelliteComs = (satelliteComsData*) s;
  
  // Send earth command to command task
  commandTaskData->earthCommand = s->earthCommand;
  if (satelliteComs->earthCommand = 'T') {
  // initialize the thruster direction commands
  unsigned short left = 0;
  unsigned short right = 0;
  unsigned short up = 0;
  unsigned short down = 0;
  randomSeed(analogRead(0));
  int i  = (int) random(65535);
  if (i < 0) {
    i = 0;
  }
  if (i > 65535) {
    i = 65535;
  }
  
  *satelliteComs->thrusterCommand = i;
  // array to hold binary encoding of thruster command
  int binary[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int count = 15;
  // convert decimal to binary
  while (i != 0) {
    int rem = i % 2;
    if (rem == 1) {
      i = i - 1;
      binary[count] = 1;
    }
    count = count - 1;
    i = i / 2;
  }

  // interpret thrust command
  left = binary[15];
  right = binary[14];
  up = binary[13];
  down = binary[12];
  // Generate thruster control commands
  int magnitude[4] = {binary[8], binary[9], binary[10], binary[11]};
  int duration[8] = {binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]};
    }
 }
