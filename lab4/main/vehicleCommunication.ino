

char inByte;

typedef struct vehicleCommsData {
  char* command;
  char* response;
} vehicleCommsData;

void vehicleCommunicate(void* t );

void vehicleCommunicate(void* t ) {


while (Serial1.available()) {
    inByte = (char)Serial1.read();
  }
  
   Serial.println("FUNCTION 7");
   vehicleCommsData* vd = (vehicleCommsData*) t;
    Serial1.print(*vd->command);
    inByte = (char)Serial1.read();
    delay(2);

   if (Serial1.available()) {
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

delay(2);
  if (Serial1.available()) {
    inByte = (char)Serial1.read();
    }
  if((int)inByte > 64 ) {
  Serial.print((char)inByte); 
  Serial1.print('K');  
  inByte = (char)Serial1.read();
 }

delay(2);

  if (Serial1.available()) {
    inByte = (char)Serial1.read();
    }
  if((int)inByte > 64 ) {
  Serial.print((char)inByte); 
  Serial1.print('C');  
  inByte = (char)Serial1.read();
 }
}
