// Initialize all global variables
bool solarPanelState;
unsigned short batteryLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
bool fuelLow;
bool batteryLow;
float fuelLevel;
unsigned int thrusterCommand;

// Initialize struct for TCB
typedef struct TCB {
void (*myTask)(void*);
 void* taskDataPtr;
} TCB; 

// Initialize global variable for TCB array
TCB fn[6];

// Initialize all global structs
powerSubsystemData psd;
satelliteComsData sd;
thrusterSubsystemData td;
consoleDisplayData cd;
warningAlarmData wd;

  
void setup() {

  // Begin communication between board and computer
  Serial.begin(9600);
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

  // Set all of the global variables and structs
  solarPanelState = false;
  batteryLevel = 15;
  powerConsumption = 0;
  powerGeneration = 0;
  cycle = 1;
  reverse = 0;
  fuelLow = false;
  batteryLow = false;
  fuelLevel = 7;
  thrusterCommand = 0;
  // Set the struct pointers for the power subsystem
  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
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
  randomSeed(analogRead(0));
  // Set the task queue array' pointers to the correct functions
  // and data for each task
   fn[0].myTask = &powerSubsystem;
   fn[0].taskDataPtr = &psd;
   fn[1].myTask = &thrusterSubsystem;
   fn[1].taskDataPtr = &td;
   fn[2].myTask = &satelliteComs;
   fn[2].taskDataPtr = &sd;
   fn[3].myTask = &ConsoleDisplay;
   fn[3].taskDataPtr = &cd;
   fn[4].myTask = &WarningAlarm;
   fn[4].taskDataPtr = &wd;
}



void communicate() {
  char inChar;
  char inputString[10];
  bool stringComplete = false;
  // represent start bit found
  bool start = false;
  // Looking for start

  
  while (Serial.available()) {
    delay(100);
    inChar = (char)Serial.read();
    // Find Start
    if(inChar == '$') {
      break;
    }
  }

  Serial.println("Start");
  start = false;
  int bitCount = 0;
  // Okay have the start
  int index = 0;
 while (Serial.available()) {
    delay(300);
    // get the new byte:
    inChar = (char)Serial.read();
    bitCount++;
    // add it to the inputString:
    inputString[index] = inChar;
    index++;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if(inChar == '$') {
      break;
    }
  }
  
 // Begin Response
 Serial.write("$");
 // Send detected count of bits
 //Serial.write(bitCount);
 // Send what you received
 Serial.write(inputString, index + 1);
 // End Response
 Serial.write("$");
 // Don't know
 String string;
 for (int i = 0; i < 3; i++) {
  string+=inputString[i];
 }
 Serial.println(string);
 Serial.println("End");
}

void loop() {
  
  delay(1000);
  communicate();
  
}
