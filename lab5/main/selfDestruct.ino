// Struct containing all data for the selfDestruct data
typedef struct selfDestructData {
} selfDestructData;

destruct;
// set up sd card in setup

void selfDestruct(void* s);

void selfDestruct(void* s) {
  selfDestructData* selfDestruct = (selfDestructData*) s;
  Serial.println("Welcome to TrollBot");
  while (1) {
    int dist  = (int) random(10);
    if (dist < 0) {
      dist = 0;
    }
    if (dist > 10) {
      dist = 10;
    }

    if (dist = 0) {
      Serial.println("BEER TIME YOU MUST HAVE");
    }
    if (dist = 1) {
      Serial.println("ASDFGHJKL");
    }
    if (dist = 2) {
      Serial.println("AAAAAAAAAAGGGHHHHHHHHHHHH");
    }
    if (dist = 3) {
      Serial.println("BROKE AND BROKEN");
    }
    if (dist = 4) {
      Serial.println("GO HAVE A BEER YOU ARE GONNA NEED IT");
    }
    if (dist = 5) {
      Serial.println("I AM THE CAPTAIN NOW");
    }
    if (dist = 6) {
      Serial.println("WIRE");
    }
    if (dist = 7) {
      Serial.println("SHALL WE GET STARTED");
    }
    if (dist = 8) {
      Serial.println("GOOD MORNING");
    }
    if (dist = 9) {
      Serial.println("CAPACITY CONSTRAINED");
    }
    if (dist = 10) {
      Serial.println("BE BOUNDLESS");
    }

    // TFT Display
    if (dist < 3) {
      tft.fillScreen(BLACK);
      im = tft.loadImage(pic.bmp);
      tft.image(im, 0, 0);
    } else  if (dist < 5) {
      tft.fillScreen(BLACK);
      im = tft.loadImage(pic1.bmp);
      tft.image(im, 0, 0);
    } else {
      tft.fillScreen(BLACK);
      im = tft.loadImage(pic2.bmp);
      tft.image(im, 0, 0);
  }
}
