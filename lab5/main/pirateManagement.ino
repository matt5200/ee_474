// Struct containing all pirate detection subsystems data
typedef struct pirateManagementData {
  int*alienDist;
} pirateManagementData;



void pirateManagement(void* p);

void pirateManagement(void* p) {
  Serial.println("\n***Pirate Management***");
  pirateManagementData* pirateManagement = (pirateManagementData*) p;
  while (detected) {
    if (*pirateManagement->alienDist <= 5) {
      Serial.println("Photons Fired: ENEMY DESTROYED");
      detected = false;
    } else if (*pirateManagement->alienDist <= 30) {
      while (Serial.available() > 0) {
        char val = (char)Serial.read();
        if (val == 'F') {
          Serial.println("Photons Fired: ENEMY DESTROYED");
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
    Serial.println("Pirate Management Arg");
    Serial.println("Dist");
    Serial.println(*pirateManagement->alienDist);
    Serial.println("Detected");
    Serial.println(detected);
    
    if (detected) {
      *pirateManagement->alienDist = dist;
    } else {
      *pirateManagement->alienDist = 1000;
    }
  } 
}
