

char* vehicleCommunicate(char command[] ) {
  // Begin Communication
  Serial1.write(36);
  // Send command
  Serial1.write(command, 3);

  Serial1.write(36);

  char inChar;
  char inputString[10];
  bool start = false;

  // Looking for start
  while (Serial1.available()) {
    delay(300);
    inChar = (char)Serial1.read();
    // Find Start
    if(inChar == '$') {
      break;
    }
  }
  Serial.println("ALOHA");
  // Recieve Response
  int index = 0;
 while (Serial1.available()) {
    delay(300);
    // get the new byte:
    inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString[index] = inChar;
    index++;
    // check for end
    if(inChar == '$') {
        break;
    }
  }
  int count = inputString[0];
  // Ensure reciever had the same amount of bytes
  //if (count != command.length()) {
  //  return '0';
 // }
 String a;
  for (int i = 0; i < index; i++) {
    a+= inputString[i];
  }
  Serial.println(a);
  Serial.println("ALOHA2");

  return command;
}
