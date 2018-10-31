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
  digitalWrite(25, HIGH);
  if (rate*500 + wait > 1000) {
    Serial.print("MOTOR MOTOR MOTOR MOTOR !!!!!!!!!!!!");
    Serial.print("MOTOR IS ");
    Serial.println(motorComplete);
    delay(1000 - wait);
     motorComplete= true;
  }
  else {
  delay(rate*500);
  }
  if ((500.0 - rate*500.0) > 0.0) {
    digitalWrite(25, LOW);
    delay(500 - rate*500);
  }
  
  if (*solarPanelControl->driveMotorSpeedInc && rate < 1) {
    rate = rate + .05;
    *solarPanelControl->driveMotorSpeedInc = false;
  }
  else if(*solarPanelControl->driveMotorSpeedDec && rate > 0) {
    rate = rate - .05;
    *solarPanelControl->driveMotorSpeedDec = false;
  }
  wait = rate*500 + wait;
  if (wait == 1000) {
     motorComplete= true;
  }
  Serial.println(rate*500);
  Serial.println("RATE IS...");
  Serial.println(rate);
}

  if (*solarPanelControl->driveMotorSpeedInc == true) {
    *solarPanelControl->driveMotorSpeedInc = false;
  } else if (*solarPanelControl->driveMotorSpeedDec == true) {
    *solarPanelControl->driveMotorSpeedDec = false;
  }
  // TURN OFF PWM
 digitalWrite(25, LOW);
 motorComplete= false;
 Serial.print("MOTOR IS ");
 Serial.println(motorComplete);
 *solarPanelControl->solarPanelDeploy = false;
 *solarPanelControl->solarPanelRetract = false;
}
