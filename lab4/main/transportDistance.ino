typedef struct transportDistanceData {
  unsigned short* distance;
} transportDistanceData;

int transportDistance[8]  = {0,0,0,0,0,0,0,0}; // newwww
int placeDist;

void transportDistance(void* s);

void transportDistance(void* s) {
  transportDistanceData* transportDistance = (transportDistanceData*) s;
  

  if (placeDist == 8) {
    placeDist = 0;
  } else {
    placeDist++;
  }
