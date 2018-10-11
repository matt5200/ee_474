#include "boolean.ino"

typedef struct powerSubsystemData {
  bool* solarPanelState;
  unsigned short* batteryLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
} powerSubsystemData;

///// FIX POWER CONSUMPTION
void powerSubsystem(powerSubsystemData* power, int* cycle, bool* reverse) {
  // powerConsumption
  if (power->powerConsumption < 11 && reverse == 0) {
    if (cycle % 2 == 0) {
      power->powerConsumption = power->powerConsumption + 2;
    } else {
      power->powerConsumption = power->powerConsumption - 1;
    }
  } else if (power->powerConsumption 
    if (cycle % 2 == 1) {
      power->powerConsumption = power->powerConsumption + 2;
    } else {
      power->powerConsumption = power->powerConsumption - 1;
    }
  }

  // powerGeneration
  if (powerSubsystemData->SolarPanelState == TRUE) {
    if (powerSubsystemData->batteryLevel > 95) {
      powerSubsystemData->SolarPanelState = FALSE;
    } else {
      if (powerSubsystemData->batteryLevel < 96) {
        if (cycle % 2 == 0) {
          powerSubsystemData->powerGeneration = powerSubsystemData->powerGeneration + 2;
        } else {
          if (powerSubsystemData->batteryLevel < 51) {
            powerSubsystemData->powerGeneration = powerSubsystemData->powerGeneration + 1;
          }
        }
      }
    }
  } else {
    if (powerSubsystemData->batteryLevel <= 10) {
      powerSubsystemData->SolarPanelState = TRUE;
    }
  }

  // batteryLevel
  if (powerSubsystemData->SolarPanelState == FALSE) {
    powerSubsystemData->batteryLevel = powerSubsystemData->batteryLevel - (3 * powerSubsystemData->powerConsumption); 
  } else {
    powerSubsystemData->batteryLevel = powerSubsystemData->batteryLevel - powerSubsystemData->powerConsumption + powerSubsystemData->powerGeneration; 
  }
}
