typedef struct transportDistanceData {
} transportDistanceData;

int transportDistance[8]  = {0,0,0,0,0,0,0,0}; // newwww
float timeInt[8] = {0,0,0,0,0,0,0,0};
int placeTime;
int placeDist;
int placeholder;  // initialize to 7 in main
bool distanceDone;

void transportDistance(void* s);

void transportDistance(void* s) {
  distanceDone = false;
  transportDistanceData* transportDistance = (transportDistanceData*) s;
  int wave[17] = {};
  int inc = 0;
  
  for (int i = 0; i <= 2*pi; i++) {
    wave[inc] = sin(i);
    inc++;
  }

  for (int i = 0; i <= 2*pi; i+2) {
    wave[inc] = sin(i);
    inc++;
  }

  for (int i = 0; i <= 2*pi; i+3) {
    wave[inc] = sin(i);
    inc++;
  }

  for (int i = 0; i <= 2*pi; i+4) {
    wave[inc] = sin(i);
    inc++;
  }

  wave[inc] = 0;
  unsigned long timeNow = milis();
  unsigned long timeEnd;
  unsigned long freq;
  unsigned long period;
  float dist = 2000.0;

  for (int j = 1; j < 17; j++) {
      delay(1);
      if (wave[j] == 0)  {
        timeEnd = milis();
        period = timeEnd - timeNow;
        freq = 1 / period;
        dist = dist - (frequency * 2); 250, 143, 333,333
        if (dist < 101) {
          dist = 100;
        }
        // store distance in buffer if 10% different from last distance
        if (dist > transportDistance[placeholder] * 1.1 || dist < transportDistance[placeholder] * 0.9) {
          transportDistance[placeDist] = dist;
          placeholder = placeDist;
          if (placeDist == 7) {
            placeDist = 0;
          } else {
            placeDist++;
          }
        }
        Serial.print("Distance: ");
        Serial.println(dist);
        timeNow = timeEnd;
      }
      timeInt[placeTime] = period;
      if (placeTime == 7) {
        placeTime = 0;
      } else {
        placeTime++;
      }
  }
  distanceDone = true;
}
