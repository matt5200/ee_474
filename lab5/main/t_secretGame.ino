#include <SD.h>
#include <SPI.h>
#define SD_CHIP_SELECT  53  // SD chip select pin(Arduino Mega)

void secretGame();
// Play a fun challenging game for 60 seconds
// then return to work!
void secretGame() {
  
  while(Serial.available() > 0) {
    Serial.read();
  }
  
  Serial.println("\n***Feel up to a game engineers??\n");
  goodDelay1();
  
  char resp = Serial.read();
  // Look for a yes response
  if (resp == 'y') {
  tft.setTextColor(RED);
  tft.setCursor(0,0);
  tft.print("Eat all the food!");
  tft.setTextColor(WHITE);
  tft.setCursor(0,15);
  int x = 80;
  int y = 100;
  bmpDraw("mcD.bmp", 0, 40);
  bmpDraw("chip.bmp", 0, 150);
  bmpDraw("teeth.bmp", x, y);
  bmpDraw("subway.bmp", 150, 40);
  bool chipAte = false;
  bool subAte = false;
  bool mcAte = false;
  bool breakbreak = true;
  while ( 1==1 && breakbreak ) {
     while(Serial.available() > 0) {
    Serial.read();
    }
    goodDelay1();
    char resp = Serial.read();
    // Serial.println("test");
    tft.fillScreen(BLACK);
      tft.setCursor(0,0);
    tft.print("Eat all the food!");
    if ((x + 10 >= 150 && x <= 237) && (y - 10 <= 40 ) ) {
      subAte = true;
    }
    if ((x - 10 <= 10 ) && (y - 10 <= 40  )) {
      mcAte = true;
    }
    if ((x - 10 <= 10) && (y - 10 <= 150 && y >  120)) {
      chipAte = true;
    }
    if(!chipAte) {
     bmpDraw("chip.bmp", 0, 150); 
    }
    if(!mcAte){ 
      bmpDraw("mcD.bmp", 0, 40);
    }
    if(!subAte) {
        bmpDraw("subway.bmp", 150, 40);
    }
    if (resp == 'a') {
      x=x+30;
    }
    if (resp == 'd') {
      x=x-30;
    }
    if (resp == 's') {
      y=y-30;
    }
    if (resp == 'w') {
      y=y+30;
    }
    if (x < 0) {
      x = 0;
    }
    if (y < 0) {
      y = 0;
    }
    bmpDraw("teeth.bmp", x, y);
    if (mcAte && subAte && chipAte) {
    tft.fillScreen(BLACK);
    tft.setCursor(60,120);
    tft.print("Congrats");
    delay(400);
    breakbreak = false;
      }
    }
    tft.fillScreen(BLACK);
  Serial.println("Okay you had enough fun, now go explore the galaxy!");
  }
}
