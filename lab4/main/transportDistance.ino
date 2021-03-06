typedef struct transportDistanceData {
  float *transportDist;
} transportDistanceData;

int transport[8]  = {0,0,0,0,0,0,0,0}; // newwww
float timeInt[8] = {0,0,0,0,0,0,0,0};
int placeTime;
int placeDist;
int placeholder;  // initialize to 7 in main
bool distanceDone;
#define pi 3.141592
void transportDistance(void* s);

void transportDistance(void* s) {
  Serial.println("RUNNING TRANSPORT");
  distanceDone = false;
  transportDistanceData* transportDistance = (transportDistanceData*) s;
  double wave[100] = {};
  int inc = 0;
  
  Serial.println("RUNNING TRANSPORT 1"); 
  for (double i = 0; i <= 2*pi; i+=.25) {
    wave[inc] = sin(i);
    inc++;
  }
 Serial.println("RUNNING TRANSPORT 2");
  for (double i = 0; i <= 2*pi; i+=.5) {
    wave[inc] = sin(i);
    inc++;
  }

  for (double i = 0; i <= 2*pi; i+=1) {
    wave[inc] = sin(i);
    inc++;
  }

  for (double i = 0; i <= 2*pi; i+=1.5) {
    wave[inc] = sin(i);
    inc++;
  }
 Serial.println("RUNNING TRANSPORT 3");
  wave[inc] = 0;

  unsigned long timeEnd;
  double freq;
  double period;
  *transportDistance->transportDist = 2000.0;
  for (int i = 0; i < inc + 1; i++) {
    Serial.print("[");
    Serial.print(wave[i]);
    Serial.print("]->");
    if (i % 10 == 0) {
      Serial.println();
    }
  }
  Serial.println();
 Serial.println("RUNNING TRANSPORT 4");
  unsigned long timeNow = millis();
  for (int j = 1; j < inc + 1; j++) {
      delay(10);
      if (wave[j] == 0.0)  {
        timeEnd = millis();
        period = timeEnd - timeNow;
         Serial.print("TRANSPORT DIST PERIOD WAS ->>>> ");
         Serial.println(period);
        freq = 1 / period;
        Serial.print("TRANSPORT DIST FREQ WAS ->>>> ");
        Serial.println(freq*10000);
        *transportDistance->transportDist = *transportDistance->transportDist - (freq * 66225); 
        if (*transportDistance->transportDist < 101) {
           distanceDone = true;
            *transportDistance->transportDist = 100;
            Serial.print("Distance: ");
            Serial.println(*transportDistance->transportDist);
           break;
        }
        // store distance in buffer if 10% different from last distance
        if (*transportDistance->transportDist > transport[placeholder] * 1.1 || *transportDistance->transportDist < transport[placeholder] * 0.9) {
          transport[placeDist] = *transportDistance->transportDist;
          placeholder = placeDist;
          if (placeDist == 7) {
            placeDist = 0;
          } else {
            placeDist++;
          }
        }
        Serial.print("Distance: ");
        Serial.println(*transportDistance->transportDist);
        timeNow = timeEnd;
      }
      timeInt[placeTime] = period;
      if (placeTime == 7) {
        placeTime = 0;
      } else {
        placeTime++;
      }
  }
   Serial.println("RUNNING TRANSPORT END");
}
