

void goodDelay();

void goodDelay() {
 while (!Serial.available()) {
 }
if((int) Serial.peek() < 64) {
  Serial.read();
   goodDelay();
 }
}


void setup() {
  char inChar;
  Serial.begin(9600);
}

 char inByte;


void loop()
{
  delay(.1);
  // wait for command
  goodDelay();
  // print back command
  inByte = (char)Serial.read();
  Serial.print((char)inByte);  
  // get rid of that previous char
  inByte = (char)Serial.read();
  delay(.1);
  // send d Command
  Serial.print('T');
  // get rid of that previous char
  inByte = (char)Serial.read();
  // wait for response
  goodDelay();
  // should recieve a K
  inByte = (char)Serial.read();
  Serial.print((char)inByte);  
  // get rid of that char you just printed
  inByte = (char)Serial.read();
  // send D command
  Serial.print('D');
  // get rid of that char
  inByte = (char)Serial.read();
  // wait for C response
  goodDelay();
  inByte = (char)Serial.read();
  // print that C
  Serial.print((char)inByte);  
  // get rid of dat C
  inByte = (char)Serial.read();
}
