

typedef struct commandData {
 char* earthCommand;
 char* satResponse;
 unsigned  short *batteryLevel;
 float *fuelLevel;
 unsigned short *powerConsumption;
 unsigned short *powerGeneration;
 unsigned short * batteryTemperature;
 bool *fuelLow;
 bool *batteryLow;
 bool *solarPanelState;
 float *transportDist;
 int* imageData;
} commandData;

commandData cnd;

// Struct containing all data for the satellite data 
typedef struct satelliteComsData {
  float *transportDist;
  char* earthCommand;
  bool* fuelLow;
  bool* batteryLow;
  bool* solarPanelState;
  unsigned short* batteryLevel;
  float* fuelLevel;;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
  unsigned int* thrusterCommand;
  unsigned short* batteryTemperature2;
  char* satResponse;
  int * imageData;
  unsigned short* batteryTemperature;
} satelliteComsData;
satelliteComsData sd;

void satelliteComs(void* s);

void satelliteComs(void* s) {
  Serial.println("\n***Satellite Comms Running***");
  satelliteComsData* satelliteComs = (satelliteComsData*) s;

  // Recieve earth command
  *satelliteComs->earthCommand = *ed.earthCommand1;
  
  // Send earth command to command task
  *cnd.earthCommand = *satelliteComs->earthCommand;


  // Add command task
  insert(&front, &back, &p);
  // Run command task
  (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
  // Remove command task
  deleteNode(&front, &back, currentLength - 1);
  
  // Send response
  *ed.satResponse1 = *satelliteComs->satResponse;
  Serial.print("Earth Command  = ");
  Serial.println(*satelliteComs->earthCommand);
  Serial.print("Satellite Response  = ");
  Serial.println(*ed.satResponse1 );
  
 if (*cnd.earthCommand == 'M') {
  *ed.batteryLevel1 = *satelliteComs->batteryLevel;
  *ed.fuelLow1 = *satelliteComs->fuelLow;
  *ed.fuelLevel1 = *satelliteComs->fuelLevel;
  *ed.powerConsumption1 = *satelliteComs->powerConsumption;
  *ed.powerGeneration1 = *satelliteComs->powerGeneration;
  *ed.batteryLow1 = *satelliteComs->batteryLow;
  *ed.solarPanelState1 = *satelliteComs->solarPanelState;
  *ed.transportDist1 = *satelliteComs->transportDist;
  *ed.imageData1 = *satelliteComs->imageData;
  *ed.batteryTemp1 = *satelliteComs->batteryTemperature;
  *ed.batteryTemp21 = *satelliteComs->batteryTemperature2;
  *cnd.satResponse = 'M';
 }
  
  if (*satelliteComs->earthCommand = 'T') {
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
