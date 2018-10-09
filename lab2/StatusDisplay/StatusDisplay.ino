void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 Status and Annunciation Subsystem Requirements
The status, annunciation, and warning management portion of the system must
monitor and annunciate the following signals:
Status
Solar Panel State
Battery Level
Power Consumption and Generation
Fuel Level
Warning and Alarm
Fuel Low
Battery Low
Displayed information comprises three major categories: status, annunciation, and
alarm. Such information is to be presented on a Display Console.
 
 */

int status () {

}

enum myBool { 
  FALSE = 0, TRUE = 1 
  };
 typedef enum _myBool Bool;

typedef struct consoleDisplayData{ 
  bool fuel_low;
  bool battery_low;
  bool solar_panel_state;
  int battery_level;
  int fuel_level;
  int power_consumptionl
  int power_generationl
} consoleDisplayData;

typedef struct warningAlarmData{ 
  bool fuel_low;
  bool battery_low;
  int battery_level;
  int fuel_level;
} warningAlarmData;
