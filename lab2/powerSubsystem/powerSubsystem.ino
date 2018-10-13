typedef struct powerSubsystemData {
  bool* solarPanelState;
  unsigned short* batteryLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
} powerSubsystemData;

void powerSubsystem(powerSubsystemData* power, int* cycle, bool* reverse);

void powerSubsystem(powerSubsystemData* power, int* cycle, bool* reverse) {
  // powerConsumption
  if (*power->powerConsumption > 10) {
    *reverse = 1;
  } else if (*power->powerConsumption < 5) {
    *reverse = 0;
  }
  if (*reverse == 0) {
    if (*cycle % 2 == 0) {
      *power->powerConsumption = *power->powerConsumption + 2;
    } else {
      *power->powerConsumption = *power->powerConsumption - 1;
    }
  } else {
    if (*cycle % 2 == 1) {
      *power->powerConsumption = *power->powerConsumption + 2;
    } else {
      *power->powerConsumption = *power->powerConsumption - 1;
    }
  }

  // powerGeneration
  if (*power->solarPanelState == true) {
    if (*power->batteryLevel > 95) {
      *power->solarPanelState = false;
    } else {
      if (*power->batteryLevel < 96) {
        if (*cycle % 2 == 0) {
          *power->powerGeneration = *power->powerGeneration + 2;
        } else {
          if (*power->batteryLevel < 51) {
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
    *power->batteryLevel = *power->batteryLevel - (3 * *power->powerConsumption); 
  } else {
    *power->batteryLevel = *power->batteryLevel - *power->powerConsumption + *power->powerGeneration; 
  }
}
