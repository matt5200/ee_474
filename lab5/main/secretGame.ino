

// Play a fun challenging game for 60 seconds
// then return to work!
void foodGame() {
  while(Serial.availible() > 0) {
    Serial.read();
  }
  Serial.println("\n***Feel up to a game engineers??\n");
  goodDelay1();
  
  char resp = Serial.read();
  // Look for a yes response
  if (resp == 'y') {
  tft.textColor(RED);
  tft.setCursor(0,0);
  tft.print("Eat all the food before time runs out!!");
  tft.textColor(WHITE);
  tft.setCursor(0,15);
  tft.print("60.0");
  int foodXCord = rand(50,150);
  int foodYCord = rand(50,150);
  int playerX = rand(50,150);
  int playerY = rand(50,150);
  int time = 60.0
  tft.clear();
  int foodEaten = 0;
  double time = millis();
  while ( millis() - time < 60 && foodEatn < 5) {
      
    if (foodEaten == 5) {
    tft.clear();
    tft.setCursor(30,120);
    tft.print("WINNER WINNER WINNER");
    }
  }
  Serial.println("Okay you had enough fun, now go explore the galaxy!");
}
  
  
 
