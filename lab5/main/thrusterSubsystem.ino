// Struct for all data relevant to thruster system
typedef struct thrusterSubsystemData {
  float* fuelLevel;
  unsigned int* thrusterCommand;
} thrusterSubsystemData;

void thrusterSubsystem (void* t);

void thrusterSubsystem (void* t) {
  Serial.println("\n*** Thruster Subsystem ***");
  thrusterSubsystemData* thrusterSubsystem = (thrusterSubsystemData*) t;
  // convert decimal to binary
  int binary[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int count = 15;
  while (*thrusterSubsystem->thrusterCommand != 0) {
    int rem = *thrusterSubsystem->thrusterCommand % 2;
    if (rem == 1) {
      *thrusterSubsystem->thrusterCommand = *thrusterSubsystem->thrusterCommand - 1;
      binary[count] = 1;
    }
    count = count - 1;
    *thrusterSubsystem->thrusterCommand = *thrusterSubsystem->thrusterCommand / 2;
  }

  // Generating control commands for thrusters
  int thruster[4] = {binary[12], binary[13], binary[14], binary[15]};
  int magnitude[4] = {binary[8], binary[9], binary[10], binary[11]};
  int duration[8] = {binary[0], binary[1], binary[2], binary[3], binary[4], binary[5], binary[6], binary[7]};
  
  // convert duration binary to decimal
  int durationTime = 0;
  int k;
  for (k = 0; k < 8; k++) {
    durationTime = 2 * durationTime + duration[k];
  }
  // Get magnitude
  float mag;
  if (magnitude[0] == 1 && magnitude[1] == 1 && magnitude[2] == 1 && magnitude[3] == 1) {
    mag = 1.0;
  } else if (magnitude[0] == 0 && magnitude[1] == 0 && magnitude[2] == 0 && magnitude[3] == 0) {
    mag = 0.0;
  } else {
    mag = .50;
  }
  // .0076 is the fuel burn per hour
   *thrusterSubsystem->fuelLevel = *thrusterSubsystem->fuelLevel - mag*.0076*durationTime;
   if (*thrusterSubsystem->fuelLevel < 0) {
    *thrusterSubsystem->fuelLevel = 0;
   }
}
