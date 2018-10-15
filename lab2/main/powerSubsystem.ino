typedef struct powerSubsystemData {
  bool* solarPanelState;
  unsigned short* batteryLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
} powerSubsystemData;

 int cycle;
 int reverse;

void powerSubsystem(void* p);

void powerSubsystem(void* p) {
  powerSubsystemData* power = (powerSubsystemData*) p;
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

  // powerGeneration
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

  // batteryLevel
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
      }
}
