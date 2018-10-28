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

// put this in main
int buff[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int place = 0;

void powerSubsystem(void* p);

void powerSubsystem(void* p) {
  powerSubsystemData* power = (powerSubsystemData*) p;
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
      *power->solarPanelState = false;
      *power->powerGeneration = 0;
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
      *power->solarPanelState = true;
    }
  }

  // put pinMode(13, OUTPUT)
  // in setup in main
  delayMicroseconds(600);
  float voltage = analogRead(A13); // pin might be wrong, try 58 if its wrong
  float converted = voltage * 5.0 / 1023.0; // 0-5V range
  *batteryLevelPtr = floor(converted * 7.2); // 0-36V range
  buff[place] = *batteryLevelPtr;
  if (place == 15) {
    place = 0;
  } else {
    place++;
  }
  
  *batteryLevel = *batteryLevelPtr * 100 / 36;


  /*
  // Logic for updating the solar panel state
  if (*power->solarPanelState == false) {
    if (*power->batteryLevel >= (3 * *power->powerConsumption) ) {
      *power->batteryLevel = *power->batteryLevel - (3 * (*power->powerConsumption));
    } else {
      *power->batteryLevel = 0;
    }
  } else {
    if (*power->batteryLevel + *power->powerGeneration <= *power->powerConsumption) {
      *power->batteryLevel = 0;
    } else if (*power->batteryLevel + *power->powerGeneration > 100 +  *power->powerConsumption ) {
      *power->batteryLevel = 100;
    } else {
      *power->batteryLevel = *power->batteryLevel - *power->powerConsumption + *power->powerGeneration;
      if (*power->batteryLevel > 100) {
        *power->batteryLevel = 100;
      }
    } 
  }
    if (*power->batteryLevel > 100) {
        *power->batteryLevel = 100;
      } */
}
