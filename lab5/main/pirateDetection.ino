// Struct containing all pirate detection subsystems data
typedef struct pirateDetectionData {
  int* alienDist;
} pirateDetectionData;

bool detected;

void pirateDetection(void* p);

void pirateDetection(void* p) {
  Serial.println("\n**** Pirate Detection ***");
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
  Serial.println("Pirate Detection Running Arg");
  Serial.println("Dist");
  Serial.println(dist);
  Serial.println("Detected: ");
  Serial.print(detected);
  if (detected) {
   insert(&front, &back, &o);
   (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
   deleteNode(&front, &back, currentLength - 1);
  }
}
