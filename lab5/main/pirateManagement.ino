// Struct containing all pirate detection subsystems data
typedef struct pirateManagementData {
  int*alienDist;
} pirateManagementData;

bool detected;

void pirateManagement(void* p);

void pirateManagement(void* p) {
  pirateManagementData* pirateManagement = (pirateManagementData*) p;
  while (detected) {
    if (*pirateManagement->alienDist <= 5) {
      Serial.print("Photons Fired: ENEMY DESTROYED");
      detected = false;
    } else if (*pirateManagement->alienDist <= 30) {
      while (Serial.available() > 0) {
        char val = (char)Serial.read();
        if (val == 'F') {
          Serial.print("Photons Fired: ENEMY DESTROYED");
          detected = false;
        }
      }
    } else if (*pirateManagement->alienDist > 100) {
      detected = false;
    }
    
    // generate distance
    int dist  = (int) random(200);
    if (dist < 0) {
      dist = 0;
    }
    if (dist > 200) {
      dist = 200;
    }

    if (detected) {
      *pirateManagement->alienDist = dist;
    } else {
      *pirateManagement->alienDist = 1000;
    }
  } 
}
