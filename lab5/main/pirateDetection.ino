// Struct containing all pirate detection subsystems data
typedef struct pirateDetectionData {
  int* alienDist;
} pirateDetectionData;

bool detected;

void pirateDetection(void* p);

void pirateDetection(void* p) {
  pirateDetectionData* pirateDetection = (pirateDetectionData*) p;

  // generate distance
  int dist  = (int) random(500);
  if (dist < 0) {
    dist = 0;
  }
  if (dist > 500) {
    dist = 500;
  }

  *pirateDetection->alienDist = dist;
  
  if (dist <= 100) {
    detected = true;
  } else {
    detected = false;
  }
}
