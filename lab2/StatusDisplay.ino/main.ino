
//#include <TFT.h>
#include <SPI.h>
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFFA5
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


typedef struct consoleDisplayData{ 
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  int  *batteryLevel;
  int *fuelLevel;
  unsigned short *powerConsumption;
  unsigned short *powerGeneration;
} consoleDisplayData;

unsigned int thrusterCommand = 0;
int batteryLevel =  100;
int fuelLevel = 100;
short unsigned powerConsumption = 0;
short unsigned powerGeneration = 0;
short unsigned motorDrive = 0;
bool solarPanelState = false;
bool fuelLow = false;
bool batteryLow = false;


typedef struct warningAlarmData{ 
  bool *fuelLow;
  bool *batteryLow;
  int *batteryLevel;
  int *fuelLevel;
} warningAlarmData;

consoleDisplayData *cd;
warningAlarmData *wd;

void ConsoleDisplay(void *consoleDisplayData);
void initializeData(consoleDisplayData *ptr);
void initializeData2( warningAlarmData *ptr);
void WarningAlarm (void* warn);
void ClearLine(int y_coord);

bool batt_flash = true;
bool fuel_flash = true;
bool fuel_flash_two = true;

void ClearLine(int y_coord) {
  for (int x = 0; x < 80; x++) {
    for (int y = y_coord; y < y_coord + 8; y++) {
     tft.drawPixel(x, y, BLACK); 
    }
  }
}

void WarningAlarm (void *warn) {
  
  warningAlarmData *data = (warningAlarmData *) warn;
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE); 
  tft.print("ALOHA");
 
    tft.setCursor(0, 30);
    tft.print("FUEL");

    Serial.println("HEARAETHAETHAETHAERH");
      
   tft.setCursor(0, 15);
   if ( *data->fuelLevel > 50) {
    tft.setTextColor(GREEN); 
    tft.print("FUEL");
    }
   else if (*data->fuelLevel <= 50 && *data->fuelLevel > 10) {
    if (fuel_flash == true) {
      if (fuel_flash_two == true) {
      ClearLine(15);
      fuel_flash = false;
      fuel_flash_two = false;
      }
    else {
      fuel_flash_two = true;
      }
    }
    else {
      fuel_flash = true;
      tft.setTextColor(ORANGE);
      tft.print("FUEL\n");
    }
   }
   else {
      if (fuel_flash == true) {
      if (fuel_flash_two == true) {
      ClearLine(15);
      fuel_flash = false;
      fuel_flash_two = false;
      }
    else {
      fuel_flash_two = true;
      }
   }
    else {
      fuel_flash = true;
      tft.setTextColor(RED);
      tft.print("FUEL\n");
    }
   }
    
    if (*data->batteryLevel > 50) {
    tft.setTextColor(GREEN);
    tft.print("BATTERY\n");
    }
   else if (*data->batteryLevel <= 50 && *data->batteryLevel > 10) {
    if (batt_flash == true) {
      ClearLine(30);
      batt_flash = false; 
    }
    else {
    batt_flash = true; 
    tft.setTextColor(ORANGE); ;
    tft.print("BATTERY\n");
    }
  }
  else {
   if (batt_flash == true) {
      ClearLine(30);
      batt_flash = false;
    }
    else {
    batt_flash = true;
    tft.setTextColor(RED); 
    tft.print("BATTERY\n");
    }
 }
  delay(1000);
}

void ConsoleDisplay(void *ptr) 
{
    consoleDisplayData *data= (consoleDisplayData *) ptr;
    Serial.println("Panel State :");
    Serial.println(*(data->solarPanelState));
    Serial.println("\n");
    Serial.println("Battery Level :");
    Serial.println(*(data->batteryLow));
    Serial.println("\n");
    Serial.println("Fuel Low Status :");
    Serial.println("\n");
    Serial.println("Power Consumption :");
    Serial.println(*(data->powerConsumption));
    Serial.println("\n");
    Serial.println("Battery Level :");
    Serial.println(*(data->batteryLevel));
    Serial.println("\n");
    Serial.println("Fuel Level :");
    Serial.println(*(data->fuelLevel));
    Serial.println("\n");
    Serial.println("Power Consumption :");
    Serial.println(*(data->powerConsumption));
    Serial.println("\n");
    Serial.println("Power Generation :");
    Serial.println(*(data->powerGeneration));
    Serial.println("\n");
}

void setup() {
  
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));


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

  wd->fuelLow = &fuelLow;
  wd->batteryLow = &batteryLow; 
  wd->batteryLevel = &batteryLevel;
  wd->fuelLevel = &fuelLevel;

  cd->fuelLow = &fuelLow;
  cd->batteryLow = &batteryLow;
  cd->solarPanelState = &solarPanelState;
  cd->batteryLevel = &batteryLevel;  
  cd->fuelLevel = &fuelLevel;
  cd->powerConsumption = &powerConsumption;
  cd->powerGeneration = &powerGeneration;
}

void loop()
{
   WarningAlarm(wd);
   Serial.println(*wd->fuelLevel);
   Serial.println(*wd->batteryLevel);
   //Serial.println(&cd);
  // ConsoleDisplay(cd);
    delay(100);
}
