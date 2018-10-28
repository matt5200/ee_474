typedef struct solarPanelControlData {
  bool* solarPanelState;
  bool* solarPanelDeploy;
  bool* solarPanelRetract;
  bool* driveMotorSpeedInc;
  bool* driveMotorSpeedDec;
} solarPanelControlData;

void solarPanelControl(void* c);

void solarPanelControl(void* c) {
  solarPanelControlData* solarPanelControl = (solarPanelControlData*) c;
  unsigned short motorDrive = 0;
  unsigned short range = 0; // what is this
  unsigned short control = 0; // what is this

  if (driveMotorSpeedInc == true) {
    driveMotorSpeedInc = false;
    (increase speed)
  } else if (driveMotorSpeedDec == true) {
    driveMotorSpeedDec = false;
    (decrease speed)
  }

  
}

// duty cycle will reflect speed
