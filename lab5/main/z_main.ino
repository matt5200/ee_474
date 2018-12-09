powerSubsystemData psd;

thrusterSubsystemData td;
consoleDisplayData cd;
warningAlarmData wd;
solarPanelControlData spd;
consoleKeypadData  ckd;
vehicleCommsData vcd;
transportDistanceData tpd;
pirateDetectionData pd;
pirateManagementData pmd;

char arrCommands [7] = {'F','B','L','R','D','H'};

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600);


  displayOff = false;
  batteryLevel1= 0;
  fuelLevel1= 0;
  powerConsumption1= 0;
  fuelLow1= 0;
  batteryLow1= 0;
  solarPanelState1= false;
  transportDist1= 0;
  imageData1= 0;
  earthCommand1= 'S';
  satResponse1= 0;
  imageData = 0;
  powerGeneration1 = 0;
  

  detected = false;
  placeTime2 = 0;
  ack = false;
  timer = 0;
  timer2 = 0;
  timer3= 0;
  transportDist = 2000;
  placeTime= 0;
  placeDist= 0;
  placeholder= 7;  // initialize to 7 in main
  distanceDone= true;


  pinMode(25, OUTPUT);
  pinMode(A11, INPUT);
  pinMode(A12, INPUT);
  pinMode(A13, INPUT);
  pinMode(A14, INPUT);
  pinMode(A15, INPUT);
  // Set booleans for battery and fuel flash to true
  batt_flash = true;
  batt_flash_two = true;
  fuel_flash = true;
  fuel_flash_two = true;
  endOfTravel = false;
  stable = true;
  // Set booleans for battery and fuel flash to true
  batt_flash = true;
  fuel_flash = true;
  fuel_flash_two = true;
  placeTemp = 0;

  // The following code is for the tft display
  #ifdef USE_Elegoo_SHIELD_PINOUT
  Serial.println(F("Using Elegoo 2.4\" tft Arduino Shield Pinout"));
  #else
  Serial.println(F("Using Elegoo 2.4\" tft Breakout Board Pinout"));
  #endif

  Serial.print("tft size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

   uint16_t identifier = tft.readID();
   if(identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(identifier==0x0101)
  {     
      identifier=0x9341;
       Serial.println(F("Found 0x9341 LCD driver"));
  }
  else if(identifier==0x1111)
  {     
      identifier=0x9328;
       Serial.println(F("Found 0x9328 LCD driver"));
  }
  else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" tft Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_tft.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    identifier=0x9328;
  
  }
  tft.begin(identifier);

    Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  Serial.println("OK!");
  
  tft.fillScreen(BLACK);
  flashTemp = true;
  motorComplete = false;
  solarPanelState = false;
  batteryLevel = 100;
  powerConsumption = 0;
  powerGeneration = 0;
  cycle = 1;
  reverse = 0;
  fuelLow = false;
  batteryLow = false;
  fuelLevel = 100;
  thrusterCommand = 0;
  currentLength = 0;
  solarPanelDeploy = false;
  solarPanelRetract = false;
  batteryOverTemperature= false;
  batteryLevelPtr= buff[0];
  flashing = true;
  place = 0;
  driveMotorSpeedInc = false;
  driveMotorSpeedDec = false;
  rate = .5;
  currCommand = 0;
  batteryTemperature= 0;
  batteryTemperature2= 0;
  command = arrCommands[currCommand];
  alienDist = 500;
  earthCommand = 0;
  earthCommand1 = 0;
  satResponse1 = 0;
  satResponse = 0;
  batteryTemp1= 0;
  batteryTemp21= 0;

  // imageCaptureData
  im.imageData = &imageData;
  
  // Set pointers for pirate management
  pd.alienDist = &alienDist;
  pmd.alienDist = &alienDist;
    
  // Set the struct pointers for the power subsystem
  psd.solarPanelState = &solarPanelState;
  psd.batteryLevel = &batteryLevel;
  psd.batteryLevelPtr = &batteryLevelPtr;
  psd.powerConsumption = &powerConsumption;
  psd.powerGeneration = &powerGeneration;
  psd.batteryOverTemperature= &batteryOverTemperature; 
  psd.batteryTemperature= &batteryTemperature;
  psd.batteryTemperature2= &batteryTemperature2;



  // Set the struct pointers for the satellite comms
  sd.fuelLow = &fuelLow;
  sd.batteryLow = &batteryLow;
  sd.solarPanelState = &solarPanelState;
  sd.batteryLevel = &batteryLevel;
  sd.fuelLevel = &fuelLevel;
  sd.powerConsumption = &powerConsumption;
  sd.powerGeneration = &powerGeneration;
  sd.thrusterCommand = &thrusterCommand;
  sd.transportDist  = &transportDist;
  sd.earthCommand = &earthCommand;
  sd.satResponse = &satResponse;
  sd.batteryTemperature = &batteryTemperature;
  sd.batteryTemperature2= &batteryTemperature2;
  sd.imageData = &imageData;


  // Set the struct pointers for the task command
  cnd.earthCommand = &earthCommand;
  cnd.satResponse = &satResponse;
  cnd.fuelLow = &fuelLow;
  cnd.batteryLow = &batteryLow;
  cnd.solarPanelState = &solarPanelState;
  cnd.batteryLevel = &batteryLevel;
  cnd.batteryTemperature = &batteryTemperature;
  cnd.fuelLevel = &fuelLevel;
  cnd.powerConsumption = &powerConsumption;
  cnd.powerGeneration = &powerGeneration;
  cnd.imageData = &imageData;
  cnd.transportDist  = &transportDist;
  

  // Set the struct pointers for the thruster system
  td.fuelLevel = &fuelLevel;
  td.thrusterCommand = &thrusterCommand;

  // transport distance
  tpd.transportDist = &transportDist;
   
  // Set the struct pointers for the warning data
  wd.batteryLow = &batteryLow; 
  wd.fuelLevel = &fuelLevel;
  wd.fuelLow = &batteryLow; 
  wd.batteryLevel = &batteryLevel;
  wd.batteryOverTemperature = &batteryOverTemperature;

  // Remote Data Computer
  rd.batteryLevel= &batteryLevel;
  rd.fuelLevel= &fuelLevel;
  rd.powerConsumption= &powerConsumption;
  rd.batteryTemperature = &batteryTemperature;
  rd.fuelLow = &fuelLow;
  rd.batteryLow= &batteryLow;
  rd.solarPanelState= &solarPanelState;
  rd.transportDist= &transportDist;
  rd.imageData= &imageData;
  rd.batteryTemperature2 = &batteryTemperature2;


  // earth data
  ed.batteryTemp1 = &batteryTemp1;
  ed.batteryLevel1= &batteryLevel1;
  ed.fuelLevel1= &fuelLevel1;
  ed.powerConsumption1= &powerConsumption1 ;
  ed.powerGeneration1= &powerGeneration1 ;
  ed.fuelLow1= &fuelLow1;
  ed.batteryLow1= &batteryLow1;
  ed.solarPanelState1= &solarPanelState1;
  ed.transportDist1 = &transportDist1 ;
  ed.imageData1= &imageData1;
  ed.earthCommand1= &earthCommand1;
  ed.satResponse1= &satResponse1;
  ed.imageData1= &imageData1;
  ed.batteryTemp21= &batteryTemp21;
   
  
  // Set the struct pointers for the console display data.
  cd.fuelLow = &fuelLow;
  cd.batteryLow = &batteryLow;
  cd.solarPanelState = &solarPanelState;
  cd.fuelLevel = &fuelLevel;
  cd.batteryLevel = &batteryLevel;
  cd.powerConsumption = &powerConsumption;
  cd.powerGeneration = &powerGeneration;
  cd.transportDist = &transportDist;

  // Initialize all console keypad data
  ckd.driveMotorSpeedInc = &driveMotorSpeedInc;
  ckd.driveMotorSpeedDec = &driveMotorSpeedDec;

  // Initialize solar panel state datae
  spd.solarPanelState = &solarPanelState;
  spd.solarPanelDeploy = &solarPanelDeploy;
  spd.solarPanelRetract = &solarPanelRetract;
  spd.driveMotorSpeedInc = &driveMotorSpeedInc;
  spd.driveMotorSpeedDec = &driveMotorSpeedDec;

  vcd.command = &command;
  vcd.response = &response;
  
  randomSeed(analogRead(0));
  void* nothing;
  // Initialize all TCBs
  a.myTask = &powerSubsystem;
  a.taskDataPtr = &psd; 
  b.myTask = &thrusterSubsystem;
  b.taskDataPtr = &td;
  c.myTask = &satelliteComs;
  c.taskDataPtr = &sd;
  d.myTask = &ConsoleDisplay;
  d.taskDataPtr = &cd;
  e.myTask = &WarningAlarm;
  e.taskDataPtr = &wd;
  f.myTask = &solarPanelControl;
  f.taskDataPtr = &spd;
  g.myTask = &consoleKeypadTask;
  g.taskDataPtr = &ckd;
  h.myTask = &vehicleCommunicate;
  h.taskDataPtr= &vcd;
  k.taskDataPtr = &tpd;
  k.myTask = &transportDistance;
  l.taskDataPtr = &psd;
  l.myTask = &batteryTemp;
  m.myTask = &imageCapture;
  m.taskDataPtr = &im;
  n.myTask = &pirateDetection;
  n.taskDataPtr = &pd;
  o.myTask = &pirateManagement;
  o.taskDataPtr = &pmd;
  p.myTask = &commandTask;
  p.taskDataPtr = &cnd;
  q.myTask = &earth;
  q.taskDataPtr = &ed;
  r.myTask = &remoteDataComputer;
  r.taskDataPtr = &rd;
  void* temp;
  s.myTask = &selfDestruct;
  s.taskDataPtr= &temp;
  t.myTask= &secretGame;
  t.taskDataPtr= &temp;
  
  Serial.println("STARTUP PROCEDURE RUNNING");
  Serial.println("ALL SYSTEM TASKS SHALL BE RUN...");
  delay(100);


   // Run All TCBS
   (a.myTask)(a.taskDataPtr);
   (b.myTask)(b.taskDataPtr);
   // (c.myTask)(c.taskDataPtr);
   (d.myTask)(d.taskDataPtr);
   (e.myTask)(e.taskDataPtr);
   (f.myTask)(f.taskDataPtr);
   (g.myTask)(g.taskDataPtr);
   // (h.myTask)(h.taskDataPtr);
   (n.myTask)(n.taskDataPtr);
   (o.myTask)(o.taskDataPtr);
   // (p.myTask)(p.taskDataPtr);
   //(q.myTask)(q.taskDataPtr);
   (r.myTask)(r.taskDataPtr);

   insert(&front, &back, &q);
   insert(&front, &back, &c);
   insert(&front, &back, &r);
   insert(&front, &back, &b); 
   insert(&front, &back, &d);
   //Commented out due to structure change
   //insert(&front, &back, &e);
   //insert(&front, &back, &f);
   insert(&front, &back, &h);
   insert(&front, &back, &a);
   insert(&front, &back, &n);

   delay(1000);
   Serial.println("END OF STARTUP...");
   int initial = 0;
}

void loop() {
  globalCount = millis();
  delay(100);
  command = arrCommands[currCommand];
  currCommand++;
  if (currCommand == 6) {
    currCommand = 0;
  }
  
  // Function calls
  for (int i = 0; i < currentLength; i++) {
       if (analogRead(A12)*5/1023 > .1) {
        stable = true;
       }
       else {
        stable = false;
       }
       Serial.println("EXECUTING NEXT FUNCTION");
       Serial.print("STABLE: ");
       Serial.println(stable);
       (getN(&front, &back, i)->myTask)(getN(&front, &back, i)->taskDataPtr);
       Serial.print("END OF TRAVEL: ");
       Serial.println(endOfTravel);
       if (endOfTravel) {
        insert(&front, &back, &f);
        endOfTravel = false;
        (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
         deleteNode(&front, &back, currentLength - 1);
      }
      if (stopTasks) {
        stopTasks = false;
        Serial.println("Ending STOP mode");
        break;
      }
     insert(&front, &back, &e);
    (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
     deleteNode(&front, &back, currentLength - 1);
  }
    
    if(ack == true) {
      batteryOverTemperature = false;
      ack = false;
    }
 
      if (solarPanelState ) {
        insert(&front, &back, &l);
        endOfTravel = false;
        (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
         deleteNode(&front, &back, currentLength - 1);
    }
    insert(&front, &back, &e);
    (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
    deleteNode(&front, &back, currentLength - 1);

  if(ack == true) {
    batteryOverTemperature = false;
    ack = false;
  }
  cycle++;
 Serial.println("\n***Would you like to self destruct?***");
  while(Serial.available() > 0) {
     Serial.read();
  }
  goodDelay1();
  if (Serial.read() == 'y') {
     insert(&front, &back, &s);
     (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
  }
  insert(&front, &back, &t);
 (getN(&front, &back, currentLength - 1)->myTask)(getN(&front, &back, currentLength - 1)->taskDataPtr);
   deleteNode(&front, &back, currentLength - 1);
}



  // This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, int x, int y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();
  uint8_t  lcdidx = 0;
  boolean  first = true;

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print(F("Loading image '"));
  Serial.print(filename);
  Serial.println('\'');
  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.println(F("File not found"));
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.println(F("File size: ")); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print(F("Image size: "));
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...
          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each column...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              // Push LCD buffer to the display first
              if(lcdidx > 0) {
                tft.pushColors(lcdbuffer, lcdidx, first);
                lcdidx = 0;
                first  = false;
              }
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            lcdbuffer[lcdidx++] = tft.color565(r,g,b);
          } // end pixel
        } // end scanline
        // Write any remaining data to LCD
        if(lcdidx > 0) {
          tft.pushColors(lcdbuffer, lcdidx, first);
        } 
        Serial.print(F("Loaded in "));
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println(F("BMP format not recognized."));
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
