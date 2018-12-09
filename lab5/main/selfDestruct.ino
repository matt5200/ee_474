// Struct containing all data for the selfDestruct data
typedef struct selfDestructData {
} selfDestructData;
// BMP-loading example specifically for the TFTLCD breakout board.
// If using the Arduino shield, use the tftbmp_shield.pde sketch instead!
// If using an Arduino Mega make sure to use its hardware SPI pins, OR make
// sure the SD library is configured for 'soft' SPI in the file Sd2Card.h.

#define SD_CS 10     // Set the chip select line to whatever you use (10 doesnt conflict with the library)

#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TFT.h>
#include <SD.h>
#include <SPI.h>

uint16_t read16(File f);
uint32_t read32(File f);
void bmpDraw(char *filename, int x, int y);

void selfDestruct(void* s) {
  selfDestructData* selfDestruct = (selfDestructData*) s;
  Serial.println("A wise University of Washington professor was so offended by your design....HES TAKEN IT OVER");
  delay(2000);
  while (1) {
    int dist  = (int) random(10);
    Serial.println(dist);
    if (dist < 0) {
      dist = 0;
    }
    if (dist > 10) {
      dist = 10;
    }

    if (dist == 0) {
      Serial.println("BEER TIME YOU MUST HAVE");
    } else if (dist == 1) {
      Serial.println("rEEjects");
    } else if (dist == 2) {
      Serial.println("AAAAAAAAAAGGGHHHHHHHHHHHH");
    }
    if (dist == 3) {
      Serial.println("BROKE AND BROKEN");
    }
    if (dist == 4) {
      Serial.println("GO HAVE A BEER YOU ARE GONNA NEED IT");
    }
    if (dist == 5) {
      Serial.println("I AM THE CAPTAIN NOW");
    }
    if (dist == 6) {
      Serial.println("WIRE");
    }
    if (dist == 7) {
      Serial.println("SHALL WE GET STARTED");
    }
    if (dist == 8) {
      Serial.println("GOOD MORNING");
    }
    if (dist == 9) {
      Serial.println("CAPACITY CONSTRAINED");
    }
    if (dist == 10) {
      Serial.println("BE BOUNDLESS");
    }


    // TFT Display
    if (dist < 3) {
      bmpDraw("pic.bmp", 0, 0);
      delay(1000);
    } else  if (dist < 5) {
      bmpDraw("pic1.bmp", 0, 0);
      delay(1000);
    } else {
     bmpDraw("pic2.bmp", 0, 0);
     delay(1000);
  }
}}
