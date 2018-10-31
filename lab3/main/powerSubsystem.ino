// Struct containing all power subsystems data
typedef struct powerSubsystemData {
  bool* solarPanelState;
  bool* solarPanelDeploy;
  bool* solarPanelRetract;
  unsigned int* batteryLevelPtr;
  unsigned short* batteryLevel; //make inital level 36 rather than 100 (use power supply or battery and potentiometer 20 turn)
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
} powerSubsystemData;

int cycle;
int reverse;
bool endOfTravel;

// put this in main
int buff[16]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};;
int place;

void powerSubsystem(void* p);

void powerSubsystem(void* p) {
  Serial.println("FUNCTION 1");
  powerSubsystemData* power = (powerSubsystemData*) p;

    // put pinMode(A13, OUTPUT)
  // in setup in main
  delayMicroseconds(600);
  float voltage = analogRead(A13); // pin might be wrong, try 58 if its wrong
  float converted = voltage * 6.5 / 1023.0; // 0-5V range
  if (converted > 5) {
    converted = 5;
  }
  *power->batteryLevelPtr = floor(converted * 7.2); // 0-36V range
  buff[place] = *power->batteryLevelPtr;
  Serial.println("CONVERTED");
  Serial.println(converted);
  Serial.println("POWER");
  Serial.println(*power->batteryLevelPtr);
  Serial.println("PLACE");
  Serial.println(place);
  if (place == 15) {
    place = 0;
  } else {
    place++;
  }
  
  *power->batteryLevel = *power->batteryLevelPtr * 100 / 36;
  
  // Logic for calculating the power consumption
  if (*power->powerConsumption > 10) {
    reverse = 1;
  } else if (*power->powerConsumption < 5) {
    reverse = 0;
  }
  if (reverse == 0) {
    if (cycle % 2 == 0) {
      *power->powerConsumption = *power->powerConsumption + 2;
    } else {
      if (*power->powerConsumption > 0) {
        *power->powerConsumption = *power->powerConsumption - 1;
      }
    }
  } else {
    if (cycle % 2 == 0) {
        *power->powerConsumption = *power->powerConsumption + 1;
    } else {
      if (*power->powerConsumption > 1) {
        *power->powerConsumption = *power->powerConsumption - 2;
      }
    }
  }

  // Logic for updating the Power Generation
  if (*power->solarPanelState == true) {
    if (*power->batteryLevel > 95) {
      endOfTravel = true;
      *power->solarPanelState = false;
      *power->powerGeneration = 0;
      *power->solarPanelRetract= true;
    } else {
        if (cycle % 2 == 0) {
          if (*power->powerGeneration + 2 <= 100) {
            *power->powerGeneration = *power->powerGeneration + 2;
          } 
          else { 
            *power->powerGeneration = 100; 
          }
        } else {
          if (*power->batteryLevel < 51) {
            if (*power->powerGeneration + 1 <= 100) {
              *power->powerGeneration = *power->powerGeneration + 1;
            }
          }
        }
    }
  } else {
    if (*power->batteryLevel <= 10) {
      endOfTravel = true;
      *power->solarPanelState = true;
      *power->solarPanelDeploy = true;
    }
  }

}
