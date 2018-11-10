typedef struct solarPanelControlData {
  bool* solarPanelState;
  bool* solarPanelDeploy;
  bool* solarPanelRetract;
  bool* driveMotorSpeedInc;
  bool* driveMotorSpeedDec;
} solarPanelControlData;

bool motorComplete;
void solarPanelControl(void* c);

TCB g;
float rate; 

void solarPanelControl(void* c) {
  Serial.println("FUNCTION 6");
  solarPanelControlData* solarPanelControl = (solarPanelControlData*) c;
  unsigned short motorDrive = 0;
  unsigned short range = 0;
  unsigned short control = 0;

float curr = millis();
float totalTime = curr + 1000;
int count;
int percent;

  

long wait = 0;

 while (wait < 1000) {
 (g.myTask)(g.taskDataPtr);
  analogWrite(A11, floor(rate*255.0));
  if (rate*2 + wait > 1000) {
    Serial.print("MOTOR IS COMPLETE");
    motorComplete = true;
  }
  if (*solarPanelControl->driveMotorSpeedInc && rate < 1) {
    rate = rate + .05;
    *solarPanelControl->driveMotorSpeedInc = false;
  }
  else if(*solarPanelControl->driveMotorSpeedDec && rate > 0) {
    rate = rate - .05;
    *solarPanelControl->driveMotorSpeedDec = false;
  }
  wait = rate*2 + wait;
  if (wait == 1000) {
     motorComplete= true;
  }
  Serial.println(rate*2);
  Serial.println("RATE IS...");
  Serial.println(rate);
}

  if (*solarPanelControl->driveMotorSpeedInc == true) {
    *solarPanelControl->driveMotorSpeedInc = false;
  } else if (*solarPanelControl->driveMotorSpeedDec == true) {
    *solarPanelControl->driveMotorSpeedDec = false;
  }
  // TURN OFF PWM
  analogWrite(A11, 0);
 motorComplete= false;
 Serial.print("MOTOR IS ");
 Serial.println(motorComplete);
 *solarPanelControl->solarPanelDeploy = false;
 *solarPanelControl->solarPanelRetract = false;
}
