#include "KeyboardController.h"

typedef struct consoleKeypadData {
  bool* driveMotorSpeedInc;
  bool* driveMotorSpeedDec;
} consoleKeypadData;

void consoleKeypadTask(void* c);

//void keyPressed() {
  //val = keyboard.getKey();
//}

void consoleKeypadTask(void* c) {
  consoleKeypadData* consoleKeypadTask = (consoleKeypadData*) c;

  if (Serial.available() > 0) {
    val = (char)Serial.read();
    if (val == 'Q') {
      driveMotorSpeedDec = true;
      driveMotorSpeedInc = false;
    } else if (val == 'W') {
        driveMotorSpeedInc = true;
        driveMotorSpeedDec = false;
    }
  }
/*  if (val == 49) {  // 1 key was pressed
    driveMotorSpeedDec = true;
    driveMotorSpeedInc = false;
  } else if (val == 50) { // 2 key was pressed
    driveMotorSpeedInc = true;
    driveMotorSpeedDec = false;
  } */ 
}

// make var a global variable?
/*//Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void keyPressed(){
 Serial.write(keyboard.getKey());
 Serial.println();
}

void loop(){
  usb.Task();

} */
