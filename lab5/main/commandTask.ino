// Command Task

typedef struct commandTaskData {
 char* validTasks;
 char earthCommand;
 char satResponse;
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
        if (ctd->task == "S" || ctd->task == "P" || ctd->task == "D" || ctd->task == "M" || ctd->task == "T" || ctd->task == "A") {
          validCommand = true;
        }
 
/*
Transmit
When a message is to be transmitted, the Command task must build the message
body. The message body is then sent to the SatelliteComms task for transmission.
After the message has been interpreted and verified as correct or an outgoing message has
been built and forwarded to the SatelliteComms task, the Command task shall be deleted
*/
 
 // if invalid, an error response must be sent to the SatelliteComms task.
 if (!validCommand) {
   ctd->satResponse = 'E';
 }
 else {
  ctd->satResponse = 'A';
 }
 if (ctd->task == 'M') {
  earthData->batteryLevel = batteryLevel;
  earthData->fuelLow = fuelLow;
  earthData->powerConsumption = powerConsumption;
  earthData->batteryLow = batteryLow;
  earthData->solarPanelState = solarPanelState;
  earthData->transportDist = transportDist;
  earthData->imageData = imageData
  ctd->response = 'M';
 }
  if (ctd->task == 'S') {
   runTasks = true;
   (a.myTask)(a.taskDataPtr);
   (b.myTask)(b.taskDataPtr);
   (c.myTask)(c.taskDataPtr);
   (d.myTask)(d.taskDataPtr);
   (e.myTask)(e.taskDataPtr);
   (f.myTask)(f.taskDataPtr);
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
 // Remove all information from TFT display
  if(ctd->task == 'D') {
   displayOff = true;
   tft.clear();
  }
  else {
   displayOff = false;
  }

satelliteComs.satResponse = ctd->satResponse;

// Format Data
remoteData.fuelLevel = fuelLevel;
remoteData.powerConsumption = powerConsumption;
remoteData.fuelLow = fuelLow;
remoteData.batteryLow = batteryLow;
remoteData.solarPanelState = solarPanelState;
remoteData.transportDist = transportDist;
remoteData.imageData = imageData;
}
  

/*
