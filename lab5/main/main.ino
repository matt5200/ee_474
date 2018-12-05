boolean displayOff;
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
bool batteryOverTemperature; 
unsigned short batteryTemperature;
unsigned short batteryTemperature2;
unsigned short batteryTemp21;
bool batteryIsValid;
bool travelFlag;
bool stable;
float transportDist;
int alienDist;
int imageData;
char satResponse;
char earthCommand;

unsigned  short batteryLevel1;
float fuelLevel1;
unsigned short powerConsumption1;
unsigned short powerGeneration1;
bool fuelLow1;
bool batteryLow1;
bool solarPanelState1;
float transportDist1;
int imageData1;
char earthCommand1;
char satResponse1;
unsigned short batteryTemp1;

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TFT.h>
#include <SD.h>
#include <SPI.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).

// For Arduino Uno/Duemilanove, etc
//  connect the SD card with DI going to pin 11, DO going to pin 12 and SCK going to pin 13 (standard)
//  Then pin 10 goes to CS (or whatever you have set up)
#define SD_CS 10     // Set the chip select line to whatever you use (10 doesnt conflict with the library)

// In the SD card, place 24 bit color BMP files (be sure they are 24-bit!)
// There are examples in the sketch folder


#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define ORANGE  0xFFA5

// our TFT wiring
Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, A4);

// Struct containing all data relevant to console displau
typedef struct consoleDisplayData{ 
  unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  unsigned short *powerGeneration;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  float *transportDist;
} consoleDisplayData;

// Struct containing all data relevant to warning alarm system
typedef struct warningAlarmData{ 
  float *fuelLevel;
  unsigned  short *batteryLevel;
  bool *fuelLow;
  bool *batteryLow;
  bool *batteryOverTemperature;
} warningAlarmData;

void ConsoleDisplay(void* cdd);
void WarningAlarm (void* d);
void ClearLine(int y_coord);

bool batt_flash;
bool batt_flash_two;
bool fuel_flash;
bool fuel_flash_two;
int timer;
int timer2;
int timer3;
bool flashTemp;
bool flashing;
bool ack;

 //Function to clear a line of the tft display
void ClearLine(int y_coord) {
  for (int x = 0; x < 80; x++) {
    for (int y = y_coord; y < y_coord + 8; y++) {
     tft.drawPixel(x, y, BLACK); 
    }
  }
}

 //Warning alarm function
void WarningAlarm (void* d) {
  Serial.println("\n***Warning Alarm***");
if (!displayOff) {
for (int i = 0; i < 50; i++) {
  delay(100);
  warningAlarmData* data = (warningAlarmData*) d;
  // Set cursor to top right to print satellite status
  tft.setCursor(0, 0);
  tft.setTextColor(WHITE); 
  tft.print("Satellite Status");
   tft.setCursor(0, 15);
  while(Serial.available () > 0 ) {
    if(Serial.read() == 'a'){
      ack = true;
    }
  }

 if (*data->batteryOverTemperature == false || ack) {
     timer3 = 0;
     tft.setCursor(0, 45);
        tft.setTextColor(BLACK);
        tft.print("TEMPERATURE");
   }
   else if(*data->batteryOverTemperature && timer3 < 150) {
   timer3++;
   tft.setCursor(0, 45);
   tft.setTextColor(RED); 
   tft.print("TEMPERATURE");
   }
   else  {
     if (timer3 % 50 == 0)  {
      if (flashTemp){
        flashTemp = false;
      }
      else {
         flashTemp = true;
      }
      }
      timer3++;
   if (flashTemp) {
   if(flashing) {
   ClearLine(45);
   flashing = false;
   }
   else {
   tft.setCursor(0, 45);
   tft.setTextColor(RED); 
   tft.print("TEMPERATURE");
   flashing = true;
    }
  }
   else {
    tft.setCursor(0, 45);
   tft.setTextColor(RED); 
   tft.print("TEMPERATURE");
   flashing = false;
  }
 }


    tft.setCursor(0, 15);
  //  Following is logic for determing fuel print state
   if ( *data->fuelLevel > 50) {
    *data->fuelLow = false;
    timer = 0;
    tft.setTextColor(GREEN); 
    tft.print("FUEL");
    }
   else if ( *data->fuelLevel <= 50 && *data->fuelLevel > 10) {
    *data->fuelLow = false;
    if(timer % 20 == 0 ) {
      if (batt_flash) {
        tft.setTextColor(BLACK);
        tft.print("FUEL");
        batt_flash = false;
    }
    else {
       tft.setCursor(0, 15);
      tft.setTextColor(ORANGE);
      tft.print("FUEL\n");
      batt_flash = true;
    }
   }
    timer++;
   }
   else {
    *data->fuelLow = true;
      if(timer % 20 == 0 ) {
      if (batt_flash) {
        tft.setTextColor(BLACK);
        tft.print("FUEL");
        batt_flash = false;
    }
    else {
      tft.setCursor(0, 15);
      tft.setTextColor(RED);
      tft.print("FUEL\n");
      batt_flash = true;
    }
   }
   timer++;
   }


   tft.setCursor(0, 30);
  //  Following is logic for determing fuel print state
   if ( *data->batteryLevel > 50) {
    *data->batteryLow =false;
    timer2 = 0;
    tft.setTextColor(GREEN); 
    tft.print("BATTERY");
    }
   else if ( *data->batteryLevel <= 50 && *data->batteryLevel > 10) {
    *data->batteryLow = false;
    if(timer2 % 10 == 0 ) {
      if (batt_flash_two) {
        tft.setTextColor(BLACK); 
         tft.print("BATTERY");
        batt_flash_two = false;
    }
    else {
       tft.setCursor(0, 30);
      tft.setTextColor(ORANGE);
      tft.print("BATTERY\n");
      batt_flash_two = true;
    }
   }
   timer2++;
   }
   else {
    *data->batteryLow = true;
      if(timer2 % 10 == 0 ) {
      if (batt_flash_two) {
         tft.setTextColor(BLACK); 
         tft.print("BATTERY");
        batt_flash_two = false;
    }
    else {
      tft.setCursor(0, 30);
      tft.setTextColor(RED);
      tft.print("BATTERY\n");
      batt_flash_two = true;
    }
      }
   timer2++;
      }
    }
  }
}

void ConsoleDisplay( void* cdd) {
  Serial.println("FUNCTION 4");
   consoleDisplayData* data = (consoleDisplayData*) cdd;
    if (*data->fuelLow || *data->batteryLow) {
       Serial.println("Battery Low :");
    Serial.println(*data->batteryLow);
    Serial.println("\n");
    Serial.println("Fuel Level :");
    Serial.println(*data->fuelLevel);
    }
    else {
    Serial.println("Panel State :");
    Serial.println(*data->solarPanelState);
    Serial.println("\n");
    Serial.println("Battery Level :");
    Serial.println(*data->batteryLevel);
    Serial.println("\n");
    Serial.println("Fuel Level:");
    Serial.println(*data->fuelLevel);
    Serial.println("\n");
    Serial.println("Power Consumption :");
    Serial.println(*data->powerConsumption);
    Serial.println("\n");
    }
}
