


boolean stopTasks;

// Command earthCommand


void commandTask(void* c);

/*
The earthCommand shall be scheduled whenever a command has been received by the system or
when an outgoing message must be formatted in preparation for transmission to the
remote computer.
*/

void commandTask(void* c) {
  Serial.println("Running Command Task");
  commandData* ctd = (commandData*) c;
  
 /*
    Receive
    When a command has been received by the system, the earthCommand must verify that the
    received message is valid. If valid, it is acted upon;
  */

 if (*ctd->earthCommand == 'S' || *ctd->earthCommand == 'P' || *ctd->earthCommand == 'D' || *ctd->earthCommand == 'M' || *ctd->earthCommand == 'T') {
          *ctd->satResponse = 'A';
        }
  else {
          *ctd->satResponse = 'E';
  }
    
 
/*
Transmit
When a message is to be transmitted, the Command earthCommand must build the message
body. The message body is then sent to the SatelliteComms earthCommand for transmission.
After the message has been interpreted and verified as correct or an outgoing message has
been built and forwarded to the SatelliteComms earthCommand, the Command earthCommand shall be deleted
*/
 

  if (*ctd->earthCommand == 'S') {
    Serial.println("Running START mode");
   (a.myTask)(a.taskDataPtr);
   (b.myTask)(b.taskDataPtr);
   Serial.println("Ending START mode");
  }
  
 if (*ctd->earthCommand == 'P') {
  Serial.println("STOP mode");
   stopTasks = true;
 }
 else {
  stopTasks = false;
 }
  
 // Remove all information from tft display
 if(*ctd->earthCommand == 'D') {
   if (displayOff) {
    displayOff = false;
   }
   else {
    displayOff = true;
    tft.fillScreen(BLACK);
   }
  }
  
 if (*ctd->earthCommand == 'M') {
  *ctd->satResponse= 'M'; 
 }
  *sd.satResponse = *ctd->satResponse;
}
