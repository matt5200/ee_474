
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


typedef struct consoleDisplayData{ 
  unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  unsigned short *powerGeneration;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
} consoleDisplayData;

typedef struct warningAlarmData{ 
  unsigned short *nothing;
  float *fuelLevel;
  unsigned  short *batteryLevel;
  bool *fuelLow;
  bool *batteryLow;
} warningAlarmData;


void ConsoleDisplay(void* cdd);
void WarningAlarm (void* d);
void ClearLine(int y_coord);

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


void WarningAlarm (void* d) {
   
  warningAlarmData* data = (warningAlarmData*) d;
 
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
}

void ConsoleDisplay( void* cdd) {
    consoleDisplayData* data = (consoleDisplayData*) cdd;
    Serial.println("Panel State :");
    Serial.println(*data->solarPanelState);
    Serial.println("\n");
    Serial.println("Battery Level :");
    Serial.println(*data->batteryLevel);
    Serial.println("\n");
    Serial.println("Fuel Low Status :");
    Serial.println("\n");
    Serial.println("Power Consumption :");
    Serial.println(*data->powerConsumption);
    Serial.println("\n");
    Serial.println("Battery Low :");
    Serial.println(*data->batteryLow);
    Serial.println("\n");
    Serial.println("Fuel Level :");
    Serial.println(*data->fuelLevel);
    Serial.println("\n");
    Serial.println("Power Consumption :");
    Serial.println(*data->powerConsumption);
    Serial.println("\n");
    Serial.println("Power Generation :");
    Serial.println(*data->powerGeneration);
    Serial.println("\n");
}
