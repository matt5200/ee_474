bool solarPanelState;
unsigned short batteryLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
bool fuelLow;
bool batteryLow;
float fuelLevel;
unsigned int thrusterCommand;
unsigned int batteryLevelPtr;
bool solarPanelDeploy;
bool solarPanelRetract;
bool driveMotorSpeedDec ;
bool driveMotorSpeedInc; 
char response;
char command;
int currCommand;
long globalCount;

bool batteryIsValid;
bool travelFlag;
bool stable;

powerSubsystemData psd;
satelliteComsData sd;
thrusterSubsystemData td;
consoleDisplayData cd;
warningAlarmData wd;
solarPanelControlData spd;
consoleKeypadData  ckd;
vehicleCommsData vcd;

TCB a;
TCB b;
TCB c;
TCB d;
TCB e;
// Solar Panel Control
TCB f;
// Console Key Pad
TCB h;

NodeTCB* front = NULL; 
NodeTCB* back = NULL;
char arrCommands [7] = {'F','B','L','R','D','H'};

void setup() {


  // Begin communication between board and computer
  Serial.begin(9600);
  pinMode(A13, INPUT);
  pinMode(A12, INPUT);
  pinMode(A11, OUTPUT);
  // Set booleans for battery and fuel flash to true
  batt_flash = true;
  fuel_flash = true;
  fuel_flash_two = true;
  endOfTravel = false;
  stable = true;
// Begin communication between board and computer
  Serial1.begin(9600);
  // Set booleans for battery and fuel flash to true
  batt_flash = true;
  fuel_flash = true;
  fuel_flash_two = true;

  // The following code is for the TFT display
  #ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
  #else
  Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
  #endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

   uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }
  tft.begin(identifier);
  tft.fillScreen(BLACK);


  motorComplete = false;
  solarPanelState = false;
  batteryLevel = 100;
  powerConsumption = 0;
  powerGeneration = 0;
  cycle = 1;
  reverse = 0;
  fuelLow = false;
  batteryLow = false;
  fuelLevel = 100;
  thrusterCommand = 0;
  currentLength = 0;
  solarPanelDeploy = false;
  solarPanelRetract = false;
  batteryLevelPtr= buff[0];
  place = 0;
  driveMotorSpeedInc = false;
  driveMotorSpeedDec = false;
  rate = .5;
  currCommand = 0;
  command = arrCommands[currCommand];
  // Set the struct pointers for the power subsystem
  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
  psd.batteryLevelPtr = &batteryLevelPtr;
  psd.powerConsumption = &powerConsumption;
  psd.powerGeneration = &powerGeneration;
  
  // Set the struct pointers for the satellite comms
  sd.fuelLow = &fuelLow;
  sd.batteryLow = &batteryLow;
  sd.solarPanelState = &solarPanelState;
  sd.batteryLevel = &batteryLevel;
  sd.fuelLevel = &fuelLevel;
  sd.powerConsumption = &powerConsumption;
  sd.powerGeneration = &powerGeneration;
  sd.thrusterCommand = &thrusterCommand;

  // Set the struct pointers for the thruster system
  td.fuelLevel = &fuelLevel;
  td.thrusterCommand = &thrusterCommand;
   
  // Set the struct pointers for the warning data
  wd.batteryLow = &batteryLow; 
  wd.fuelLevel = &fuelLevel;
  wd.fuelLow = &batteryLow; 
  wd.batteryLevel = &batteryLevel;
 
  // Set the struct pointers for the console display data.
  cd.fuelLow = &fuelLow;
  cd.batteryLow = &batteryLow;
  cd.solarPanelState = &solarPanelState;
  cd.fuelLevel = &fuelLevel;
  cd.batteryLevel = &batteryLevel;
  cd.powerConsumption = &powerConsumption;
  cd.powerGeneration = &powerGeneration;

  // Initialize all console keypad data
  ckd.driveMotorSpeedInc = &driveMotorSpeedInc;
  ckd.driveMotorSpeedDec = &driveMotorSpeedDec;

  // Initialize solar panel state datae
  spd.solarPanelState = &solarPanelState;
  spd.solarPanelDeploy = &solarPanelDeploy;
  spd.solarPanelRetract = &solarPanelRetract;
  spd.driveMotorSpeedInc = &driveMotorSpeedInc;
  spd.driveMotorSpeedDec = &driveMotorSpeedDec;

  vcd.command = &command;
  vcd.response = &response;
  
  randomSeed(analogRead(0));
  
  // Initialize all TCBs
  a.myTask = &powerSubsystem;
  a.taskDataPtr = &psd; 
  b.myTask = &thrusterSubsystem;
  b.taskDataPtr = &td;
  c.myTask = &satelliteComs;
  c.taskDataPtr = &sd;
  d.myTask = &ConsoleDisplay;
  d.taskDataPtr = &cd;
  e.myTask = &WarningAlarm;
  e.taskDataPtr = &wd;
  f.myTask = &solarPanelControl;
  f.taskDataPtr = &spd;
  g.myTask = &consoleKeypadTask;
  g.taskDataPtr = &ckd;
  h.myTask = &vehicleCommunicate;
  h.taskDataPtr= &vcd;

  Serial.println("STARTUP PROCEDURE RUNNING");
  Serial.println("ALL SYSTEM TASKS SHALL BE RUN...");
  delay(100);

   // Run All TCBS
   (a.myTask)(a.taskDataPtr);
   (b.myTask)(b.taskDataPtr);
   (c.myTask)(c.taskDataPtr);
   (d.myTask)(d.taskDataPtr);
   (e.myTask)(e.taskDataPtr);
   (f.myTask)(f.taskDataPtr);
   (g.myTask)(g.taskDataPtr);
   (h.myTask)(h.taskDataPtr);

   insert(&front, &back, &b); 
   insert(&front, &back, &c);
   insert(&front, &back, &d);
   insert(&front, &back, &e);
//   insert(&front, &back, &f);
   insert(&front, &back, &h);
   insert(&front, &back, &a);
   // Delete From Beginning Test
   /*deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
   deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
   deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
    deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
    deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
    deleteNode( &front, &back, 0);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);*/

    // Delete From End
   /*deleteNode( &front, &back, 6);
   (getN(&front, &back, 5)->myTask)(getN(&front, &back, 5)->taskDataPtr);
   deleteNode( &front, &back, 5);
   (getN(&front, &back, 4)->myTask)(getN(&front, &back, 4)->taskDataPtr);
   deleteNode( &front, &back, 4);
   (getN(&front, &back, 3)->myTask)(getN(&front, &back, 3)->taskDataPtr);
    deleteNode( &front, &back, 3);
   (getN(&front, &back, 2)->myTask)(getN(&front, &back, 2)->taskDataPtr);
    deleteNode( &front, &back, 2);
   (getN(&front, &back, 1)->myTask)(getN(&front, &back, 1)->taskDataPtr);
    deleteNode( &front, &back, 1);
   (getN(&front, &back, 0)->myTask)(getN(&front, &back, 0)->taskDataPtr);
   deleteNode( &front, &back, 0);
   if (front == NULL && back == NULL) {
      Serial.println("Linked list is gone");
   }*/

    // Delete From elsewhere
   /*deleteNode( &front, &back, 2);
   (getN(&front, &back, 2)->myTask)(getN(&front, &back, 2)->taskDataPtr);
   deleteNode( &front, &back, 4);
   (getN(&front, &back, 4)->myTask)(getN(&front, &back, 4)->taskDataPtr);
    deleteNode( &front, &back, 4);
    */

  delay(1000);
  Serial.println("END OF STARTUP...");

 int initial = 0;
}

void loop() {
   globalCount = millis();
  delay(100);
 // Serial.println(arrCommands[currCommand]);
  command = arrCommands[currCommand];
  currCommand++;
   (h.myTask)(h.taskDataPtr);

  if (currCommand == 6) {
    currCommand = 0;
  }
/*  for (int i = 0; i < currentLength; i++) {
       delay(800);
       if (analogRead(A12)*5/1023 > .1) {
        stable = true;
       }
       else {
        stable = false;
       }
       Serial.println("EXECUTING NEXT FUNCTION");
       Serial.print("STABLE: ");
       Serial.println(stable);
       (getN(&front, &back, i)->myTask)(getN(&front, &back, i)->taskDataPtr);
        if (i!=3) {
       (getN(&front, &back, 3)->myTask)(getN(&front, &back, 3)->taskDataPtr); 
        }
       Serial.print("END OF TRAVEL: ");
       Serial.println(endOfTravel);
       if (endOfTravel) {
        insert(&front, &back, &f);
        endOfTravel = false;
        (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
         deleteNode(&front, &back, currentLength - 1);
    }
  }
  cycle++;*/
}
