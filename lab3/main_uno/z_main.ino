void setup() {
  char inChar;
  Serial.begin(9600);
}


 char inByte;


void loop()
{
  
  delay(1);
  while (Serial.available()) {
    inByte = (char)Serial.read();
    }
  if((int)inByte > 64 ) {
  Serial.print((char)inByte);  
  inByte = (char)Serial.read();
 }
 
}
