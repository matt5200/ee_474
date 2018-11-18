

char inByte;

typedef struct vehicleCommsData {
  char* command;
  char* response;
} vehicleCommsData;

void vehicleCommunicate(void* t );
void goodDelay();

void goodDelay() {
 while (!Serial1.available()) {
 }
if((int) Serial1.peek() < 64) {
  Serial1.read();
   goodDelay();
 }
}

void vehicleCommunicate(void* t ) {


while (Serial1.available()) {
    inByte = (char)Serial1.read();
  }
  
   Serial.println("FUNCTION 7");
   vehicleCommsData* vd = (vehicleCommsData*) t;
   Serial.print("Printed command was ->>> ");
   Serial.println(*vd->command);
   Serial1.println(*vd->command);
   
   // wait for response of previous char
   goodDelay();
   // get response
   inByte = (char)Serial1.read();
    *vd->response = inByte;
   // print response
   Serial.print("RECIEVED A ->>>  ");
   Serial.println(*vd->response);

   Serial.println("Waiting for T command... ");
    // Should be waiting for a T
    goodDelay();
    // Get T
    inByte = (char)Serial1.read();
    Serial.print("Command received was ->>> ");
    Serial.println((char)inByte);

    // Send a K command
    Serial.println("Sending K command");
    Serial1.print('K');
    Serial1.read();
    Serial.println("Waiting for confirmation of K....");
    // Get rid of K in buffer
    
    // wait for confirmation of K being sent
    goodDelay();
    
    // read in the K from vehicle
    inByte = (char)Serial1.read();
    // print if we recieved a K from mining
    Serial.print("Command received was ->>> ");
    Serial.println(inByte);
   
    // Now there should be a D too
    inByte = (char)Serial1.read();
    // print the D
    Serial.print("SHOULD RECIEVE A D ->>>> ");
    Serial.println(inByte);

     Serial.println("Sending C command");
     Serial.println("Waiting for confirmation..");
     // Send a C command
     Serial1.print('C');
     // Get rid of that last C command 
     // wait for other board to confirm response
     goodDelay();
     // Now there should be a D too
     inByte = (char)Serial1.read();
     // print the C command
     Serial.print("Command recieved was ->>> ");
     Serial.println(inByte);
}
