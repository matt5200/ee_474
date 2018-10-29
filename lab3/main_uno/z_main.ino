
  
void setup() {
  char inChar;
  Serial.begin(9600);
  
}



void communicate() {
  char inChar;
  char inputString[10];
  bool stringComplete = false;
  // represent start bit found
  bool start = false;
  // Looking for start
  delay(100);
  Serial.println("Start");
  
  while (Serial.available()) {
    delay(300);
    inChar = (char)Serial.read();
    // Find Start
    if(inChar == '$') {
      break;
    }
  }

  Serial.println("END");
  start = false;
  int bitCount = 0;
  // Okay have the start
  int index = 0;
 while (Serial.available()) {
    // get the new byte:
    inChar = (char)Serial.read();
   //     if(inChar == '$') {
   //   break;
   // }
    bitCount++;
    // add it to the inputString:
    inputString[index] = inChar;
    index++;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:

  }
 
 // Begin Response
 Serial.println('$');
 // Send detected count of bits
 //Serial.write(bitCount);
  Serial.println(inputString);
 // Send what you received
 // End Response
 Serial.println('$');
 // Don't know

}


/*
void loop() {
  
  
  int index = 0;
  char inChar;
  
  char inputString [10];

  
  delay(1000);
  while (Serial.available()) {
    delay(300);
    inChar = (char)Serial.read();
    // Find Start
    if(inChar == '$') {
      break;
    }
  }

  Serial.println("Start");
  
  while (Serial.available()) {
    delay(1000);
    // get the new byte:
    inChar = (char)Serial.read();
        if(inChar == '$') {
      break;
    }
    // add it to the inputString:
    inputString[index] = inChar;
    index++;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:

  }

  Serial.println(inputString);
  Serial.println("END");
}

*/

 char inByte;


void loop()
{
  
//char inByte2;

 // delay(2000);
 /* while (Serial.available()) {
    inByte = Serial.read();
    if(inByte == '$') {
      break;
    }
  }*/
  delay(1000);

  while (Serial.available()) {
   // inByte2 = inByte;
    inByte = (char)Serial.read();
    }

   /* while (Serial.available()) {
    delay(200);
    inByte2 = inByte;
    inByte = (char)Serial.read();
    if(inByte == '$') {
      break;
    }
  }*/

//  Serial.print("$");
 // delay(200);
 // Serial.print((char)inByte2);
 if((int)inByte > 64 ) {
 Serial.print((char)inByte);  
 inByte = (char)Serial.read();
 }
 // delay(200);
//  Serial.println("$");
 // delay(200);
}
