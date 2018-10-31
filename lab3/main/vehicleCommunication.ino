

char inByte;

typedef struct vehicleCommsData {
  char* command;
  char* response;
} vehicleCommsData;

void vehicleCommunicate(void* t );

void vehicleCommunicate(void* t ) {
   Serial.println("FUNCTION 7");
   vehicleCommsData* vd = (vehicleCommsData*) t;
    Serial1.print(*vd->command);
    delay(10);

    while (Serial1.available()) {
    inByte = (char)Serial1.read();
    *vd->response = inByte;
  }
  
  if (*vd->response == *vd->command) {
    Serial.println("I sucessfully recieved the following message");
    Serial.println(*vd->response);
  }
  else {
    Serial.println("Incorrect Message Recieved");
     Serial.println(*vd->response);
  }
}
