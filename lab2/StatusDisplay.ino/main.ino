
#include <TFT.h>
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




unsigned short batteryLevel;
unsigned short thrusterCommand;
unsigned short fuelLevel;
unsigned short powerConsumption;
unsigned short powerGeneration;
unsigned short motorDrive;
bool solarPanelState;
bool fuelLow;
bool batteryLow;


consoleDisplayData *cd;
warningAlarmData *wd;

void ConsoleDisplay(void *consoleDisplayData);
void initializeData(consoleDisplayData *ptr);
void initializeData2( warningAlarmData *ptr);
void WarningAlarm (void* warn);
void ClearLine(int y_coord);
void powerSubsystem(void* p, int* cycle, bool* reverse);

bool batt_flash;
bool fuel_flash;
bool fuel_flash_two;




void ClearLine(int y_coord) {
  for (int x = 0; x < 80; x++) {
    for (int y = y_coord; y < y_coord + 8; y++) {
     tft.drawPixel(x, y, BLACK); 
    }
  }
}


void powerSubsystem(void* p, int* cycle, bool* reverse) {

  powerSubsystemData* power = (powerSubsystemData*) p;

  // powerConsumption
  if (*power->powerConsumption > 10) {
    *reverse = 1;
  } else if (*power->powerConsumption < 5) {
    *reverse = 0;
  }
  if (*reverse == 0) {
    if (*cycle % 2 == 0) {
      if (*power->powerConsumption + 2 <= 100) {
        *power->powerConsumption = *power->powerConsumption + 2;
      } else if (*power->powerConsumption + 1 == 100) {
        *power->powerConsumption = 100;
      }
    } else {
      if (power->powerConsumption - 1 >= 0) {
        *power->powerConsumption = *power->powerConsumption - 1;
      }
    }
  } else {
    if (*cycle % 2 == 1) {
      if (*power->powerConsumption + 2 <= 100) {
        *power->powerConsumption = *power->powerConsumption + 2;
      } else if (*power->powerConsumption + 1 == 100) {
        *power->powerConsumption = 100;
      }
    } else {
      if (power->powerConsumption - 1 >= 0) {
        *power->powerConsumption = *power->powerConsumption - 1;
      }
    }
  }
  // powerGeneration

  if (*power->solarPanelState == true) {
    if (*power->batteryLevel > 95) {
      *power->solarPanelState = false;
    } else {
      if (*power->batteryLevel < 96) {
        if (*cycle % 2 == 0) {
          if (*power->powerConsumption + 2 <= 100) {
            *power->powerGeneration = *power->powerGeneration + 2;
          } else if (*power->powerConsumption + 1 == 100) {
            *power->powerConsumption = 100;
          }
        } else {
          if (*power->batteryLevel < 51) {
            if (*power->powerConsumption + 1 <= 100) {
              *power->powerGeneration = *power->powerGeneration + 1;
            }
          }
        }
      }
    }
  } else {
    if (*power->batteryLevel <= 10) {
      *power->solarPanelState = true;
    }
  }

  // batteryLevel
  if (*power->solarPanelState == false) {
    if (*power->batteryLevel - (3 * *power->powerConsumption) >= 0) {
      *power->batteryLevel = *power->batteryLevel - (3 * *power->powerConsumption);
    } else {
      *power->batteryLevel = 0;
    }
  } else {
    if (*power->batteryLevel - *power->powerConsumption + *power->powerGeneration < 0) {
      *power->batteryLevel = 0;
    } else if (*power->batteryLevel - *power->powerConsumption + *power->powerGeneration > 100) {
      *power->batteryLevel = 100;
    } else {
      *power->batteryLevel = *power->batteryLevel - *power->powerConsumption + *power->powerGeneration;
    } 
  }
}





void WarningAlarm (void *warn) {
  
  warningAlarmData *data = (warningAlarmData *) warn;
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE); 
  tft.print("Satelite Status");
    
   tft.setCursor(0, 15);
   if ( *data->fuelLevel > 50) {
    tft.setTextColor(GREEN); 
    tft.print("FUEL");
    }
   else if ( *data->fuelLevel <= 50 && *data->fuelLevel > 10) {
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
       tft.setCursor(0, 30);
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
  thrusterCommand = 0;
  batteryLevel =  2;
  fuelLevel = 3;
  powerConsumption = 40;
  powerGeneration = 60;
  motorDrive = 800;
  solarPanelState = false;
  fuelLow = false;
  fuelLow = false;
  batteryLow = false;
  batt_flash = true;
  fuel_flash = true;
  fuel_flash_two = true;

  wd->batteryLow = &batteryLow; 
  wd->fuelLevel = &fuelLevel;

  
  cd->fuelLow = &fuelLow;
  cd->batteryLow = &batteryLow;
  cd->solarPanelState = &solarPanelState;
  cd->batteryLevel = &batteryLevel;  
  cd->fuelLevel = &fuelLevel;
  cd->powerConsumption = &powerConsumption;
  cd->powerGeneration = &powerGeneration;

  wd->batteryLevel = &batteryLevel;
  cd->batteryLevel = &batteryLevel;
  wd->fuelLow = &fuelLow;
}
  

void loop()
{
  Serial.println("ORIG");
   Serial.println("batteryLevel");
    Serial.println((unsigned int)&batteryLevel, HEX);
  Serial.println("thrusterCommand");
  Serial.println(thrusterCommand);
 
  Serial.println("fuelLevel");
  Serial.println(fuelLevel);
  Serial.println("powerConsumption");
  Serial.println(powerConsumption);
    Serial.println("powerGeneration");
  Serial.println(powerGeneration);
  Serial.println("motorDrive");
  Serial.println(motorDrive);
  Serial.println("solarPanelState");
  Serial.println(solarPanelState);
  Serial.println("fuelLow");
  Serial.println(fuelLow);
  Serial.println("batteryLow");
  Serial.println(batteryLow);
  
 batteryLevel++;
  Serial.println("WD VALS");
      Serial.println("batteryLevel");
  Serial.println((unsigned int)wd->batteryLevel, HEX);
  Serial.println("fuelLow");
  Serial.println(*wd->fuelLow);
  Serial.println("batteryLow");
  Serial.println(*wd->batteryLow);

  Serial.println("fuelLevel");
  Serial.println(*wd->fuelLevel);
  
 
  Serial.println("CD VALS");
    Serial.println("batteryLevel");
  Serial.println((unsigned int)cd->batteryLevel, HEX);
  Serial.println("fuelLow");
  Serial.println(*cd->fuelLow);
  Serial.println("batteryLow");
  Serial.println(*cd->batteryLow);
  Serial.println("solarPanelState");
  Serial.println(*cd->solarPanelState);
   Serial.println("fuelLevel");
  Serial.println(*cd->fuelLevel);
   Serial.println("powerConsumption");
  Serial.println(*cd->powerConsumption);
   Serial.println("powerGeneration");
  Serial.println(*cd->powerGeneration);

  delay(1000);
}
