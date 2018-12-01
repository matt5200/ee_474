// Command Task

typedef struct commandTaskData {
 char* validTasks;
 char task;
 unsigned  short *batteryLevel;
 float *fuelLevel;
 unsigned short *powerConsumption;
 bool *fuelLow;
 bool *batteryLow;
 bool *solarPanelState;
 float *transportDist;
 unsigned int* imageData;
} commandTaskData;

void commandTask(void* c);

char* validTasks = {'S','P','D','T','M','A','E'};

/*
The task shall be scheduled whenever a command has been received by the system or
when an outgoing message must be formatted in preparation for transmission to the
remote computer.
*/

void commandTask(void* c) {
  Serial.println("FUNCTION Command Task");
  commandTaskData* ctd = (commandTaskData*) c;
  bool validCommand = false;
  /*
    Receive
    When a command has been received by the system, the task must verify that the
    received message is valid. If valid, it is acted upon;
  */
      for (int i = 0; i < ctd.validTasks.length; i++) {
        if (ctd.task == c[i]) {
          validCommand = true;
        }
      }
  
  // if invalid, an error response must be sent to the SatelliteComms task.
  if (!validCommand) {
  }
  if (ctd->task == 'S') {
   runTasks = true;
  }
 else {
 runTasks = false;
 }
 if (ctd->task == 'P') {
   stopTasks = true;
  }
 else {
   stopTasks = false;
 }
  if(ctd->task == 'D') {
   displayOff = true;
  }
  else {
   displayOff = false;
  }
 
  // It will format any requested data to be sent by the Satellite Comms task over the
  // network to the remote system. 
  /*unsigned  short *batteryLevel;
  float *fuelLevel;
  unsigned short *powerConsumption;
  bool *fuelLow;
  bool *batteryLow;
  bool *solarPanelState;
  float *transportDist;
  unsigned int* imageData;*/
 
}
/*
Transmit
When a message is to be transmitted, the Command task must build the message
body. The message body is then sent to the SatelliteComms task for transmission.
After the message has been interpreted and verified as correct or an outgoing message has
been built and forwarded to the SatelliteComms task, the Command task shall be deleted
*/
  

/*

The Commands and Responses for the embedded application task from earth are given as
follows.
S
The S command indicates START mode. The command shall start the embedded
tasks by directing the hardware to initiate all the measurement tasks. In doing so, the
command shall enable all the interrupts.
P
The P command indicates STOP mode. This command shall stop the embedded tasks
by terminating any running measurement tasks. Such an action shall disable any data
collecting interrupts.
D
The D command enables or disables the display.
T<payload>
The T command transmits the thrust command to the satellite.
M<payload>
The M command. The M command requests the return of the most recent value(s) of
the specified data.
The M response. The M response returns of the most recent value(s) of the specified
data.
A <sp command>
The A response acknowledges the receipt of the identified command.
E
The E error response is given for incorrect commands or non-existent commands. 

*/
