


boolean displayOff;
boolean stopTasks;

// Command earthCommand



void commandTask(void* c);

/*
The earthCommand shall be scheduled whenever a command has been received by the system or
when an outgoing message must be formatted in preparation for transmission to the
remote computer.
*/

void commandTask(void* c) {
  Serial.println("FUNCTION Command earthCommand");
  commandData* ctd = (commandData*) c;
  bool validCommand = false;
  
 /*
    Receive
    When a command has been received by the system, the earthCommand must verify that the
    received message is valid. If valid, it is acted upon;
  */

 if (*ctd->earthCommand == 'S' || *ctd->earthCommand == 'P' || *ctd->earthCommand == 'D' || *ctd->earthCommand == 'M' || *ctd->earthCommand == 'T' || *ctd->earthCommand == 'A') {
          validCommand = true;
        }
    
 
/*
Transmit
When a message is to be transmitted, the Command earthCommand must build the message
body. The message body is then sent to the SatelliteComms earthCommand for transmission.
After the message has been interpreted and verified as correct or an outgoing message has
been built and forwarded to the SatelliteComms earthCommand, the Command earthCommand shall be deleted
*/
 
 // if invalid, an error response must be sent to the SatelliteComms earthCommand.
 if (!validCommand) {
   *ctd->satResponse = 'E';
 }
 else {
  *ctd->satResponse = 'A';
 }

  if (*ctd->earthCommand == 'S') {
   (a.myTask)(a.taskDataPtr);
   (b.myTask)(b.taskDataPtr);
   //(c.myTask)(c.taskDataPtr);
   (d.myTask)(d.taskDataPtr);
   (e.myTask)(e.taskDataPtr);
   (f.myTask)(f.taskDataPtr);
  }
  
 if (*ctd->earthCommand == 'P') {
   stopTasks = true;
 }
 else {
  stopTasks = false;
 }
  
 // Remove all information from tft display
 if(*ctd->earthCommand == 'D') {
   displayOff = true;
   tft.fillScreen(BLACK);
  }
  else {
   displayOff = false;
  }

  *sd.satResponse = *ctd->satResponse;

}
