
typedef struct consoleKeypadData {
  bool* driveMotorSpeedInc;
  bool* driveMotorSpeedDec;
} consoleKeypadData;

void consoleKeypadTask(void* c);


void consoleKeypadTask(void* c) {
  consoleKeypadData* consoleKeypadTask = (consoleKeypadData*) c;

  while (Serial.available() > 0) {
    char val = (char)Serial.read();
    if (val == 'Q') {
      *consoleKeypadTask->driveMotorSpeedDec = true;
      *consoleKeypadTask->driveMotorSpeedInc = false;
      break;
    } else if (val == 'W') {
      *consoleKeypadTask->driveMotorSpeedInc = true;
      *consoleKeypadTask->driveMotorSpeedDec = false;
      break;
    }
  }
}
