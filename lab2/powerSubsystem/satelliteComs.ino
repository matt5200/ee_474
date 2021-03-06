typedef struct satelliteComsData {
  bool* fuelLow;
  bool* batteryLow;
  bool* solarPanelState;
  unsigned short* batteryLevel;
  float* fuelLevel;;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
  unsigned int* thrusterCommand;
} satelliteComsData;
void satelliteComs(satelliteComsData satelliteComs);

void satelliteComs(satelliteComsData satelliteComs) {

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
  
  Serial.println("***RANDOM NUMBER***");
  Serial.println(i);
  Serial.println("*********\n");
  *satelliteComs.thrusterCommand = i;
  
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
  int magnitude[4] = {binary[8], binary[9], binary[10], binary[11]};
  int duration[8] = {binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]};
 
 }
