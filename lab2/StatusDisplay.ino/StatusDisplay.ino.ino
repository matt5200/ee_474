#include <TFT.h>

typedef struct consoleDisplayData{ 
  unsigned  short *nothing;
  unsigned  short *batteryLevel;
  unsigned short *fuelLevel;
 // unsigned  short *batteryLevel;
  unsigned short *powerConsumption;
  unsigned short *powerGeneration;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
} consoleDisplayData;

typedef struct warningAlarmData{ 
  unsigned short *nothing;
  unsigned short *fuelLevel;
  unsigned  short *batteryLevel;
  bool *fuelLow;
  bool *batteryLow;
} warningAlarmData;



typedef struct powerSubsystemData {
  unsigned  short *nothing;
  bool* solarPanelState;

  unsigned short* batteryLevel;

  unsigned short* powerConsumption;

  unsigned short* powerGeneration;

} powerSubsystemData;
