

  bool solarPanelState;
  unsigned short batteryLevel;
  unsigned short powerConsumption;
  unsigned short powerGeneration;
  bool fuelLow;
  bool batteryLow;
  float fuelLevel;
  unsigned int thrusterCommand;
  void * fn[6];
  
typedef struct pwrTask
{
void (*powerSubsystemsData)(void*);
void* power;
} pwrTask;

typedef struct satelliteTask
{
void (*satelliteComsData)(void*);
void* sattelite;
} satelliteTask;


typedef struct thrusterTask
{
void (*thrusterSubsystem)(void*);
void* thruster;
} thrusterTask;

typedef struct consoleTask
{
void (*ConsoleDisplay)(void*);
void* console;
} console;


typedef struct warningTask
{
void (*WarningAlarm)(void*);
void* warningAlarmData;
} pwrTask;

typedef struct pwrTask
{
void (*powerSubsystemsData)(void*);
void* power;
} pwrTask;


  powerSubsystemData psd;
  satelliteComsData sd;
  thrusterSubsystemData td;
  consoleDisplayData cd;
  warningAlarmData wd;
  
void setup() {
  Serial.println("Status :");
  Serial.begin(9600);
  batt_flash = true;
  fuel_flash = true;
  fuel_flash_two = true;

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

  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
  psd.powerConsumption = &powerConsumption;
  psd.powerGeneration = &powerGeneration;
  
  sd.fuelLow = &fuelLow;
  sd.batteryLow = &batteryLow;
  sd.solarPanelState = &solarPanelState;
  sd.batteryLevel = &batteryLevel;
  sd.fuelLevel = &fuelLevel;
  sd.powerConsumption = &powerConsumption;
  sd.powerGeneration = &powerGeneration;
  sd.thrusterCommand = &thrusterCommand;
  
  td.fuelLevel = &fuelLevel;
  td.thrusterCommand = &thrusterCommand;
  
  wd.batteryLow = &batteryLow; 
  wd.fuelLevel = &fuelLevel;
  
  cd.fuelLow = &fuelLow;
  cd.batteryLow = &batteryLow;
  cd.solarPanelState = &solarPanelState;
  cd.fuelLevel = &fuelLevel;
  cd.batteryLevel = &batteryLevel;
  cd.powerConsumption = &powerConsumption;
  cd.powerGeneration = &powerGeneration;
  randomSeed(analogRead(0));
}

void loop() {

  delay(100);
  powerSubsystem(psd);
  satelliteComs(sd);
  thrusterSubsystem(td);
  WarningAlarm (wd);
  ConsoleDisplay(cd);
  cycle++;
}
