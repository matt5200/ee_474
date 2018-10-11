#include "boolean.ino"

typedef struct powerSubsystemData {
  bool* solarPanelState;
  unsigned short* batteryLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
} powerSubsystemData;

void powerSubsystem(powerSubsystemData* power) {
  // powerConsumption
  if (power->powerConsumption < 11) {
    if (power->powerConsumption % 2 == 0) {
      power->powerConsumption = power->powerConsumption + 2;
    } else {
      power->powerConsumption = power->powerConsumption - 1;
    }
  } else........ {
    
  }

  // powerGeneration
  if (powerSubsystemData->SolarPanelState == TRUE) {
    if (powerSubsystemData->batteryLevel > 95) {
      powerSubsystemData->SolarPanelState = FALSE;
    } else {
      // UM WAT 
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
