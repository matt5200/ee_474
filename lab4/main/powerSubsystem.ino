// Struct containing all power subsystems data
typedef struct powerSubsystemData {
  bool* solarPanelState;
  bool* solarPanelDeploy;
  bool* solarPanelRetract;
  unsigned int* batteryLevelPtr;
  unsigned short* batteryLevel;
  unsigned short* powerConsumption;
  unsigned short* powerGeneration;
  bool* batteryOverTemperature; 
  unsigned short* batteryTemperature; 
  unsigned short* batteryTemperature2;
} powerSubsystemData;

int cycle;
int reverse;
bool endOfTravel;

// put this in main
int buff[16]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int buffTemp[16]  = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; 
int place;
int placeTemp; // newwwwwwwwwwwww

void powerSubsystem(void* p);

void powerSubsystem(void* p) {
  Serial.println("FUNCTION 1");
  powerSubsystemData* power = (powerSubsystemData*) p;

    // put pinMode(A13, OUTPUT)
  // in setup in main
  delayMicroseconds(600);
  float voltage = analogRead(A13); 
  float converted = voltage * 6.5 / 1023.0; // 0-5V range
  if (converted > 5) {
    converted = 5;
  }
  *power->batteryLevelPtr = floor(converted * 7.2); // 0-36V range
  buff[place] = *power->batteryLevelPtr;
  Serial.println("CONVERTED");
  Serial.println(converted);
  Serial.println("POWER");
  Serial.println(*power->batteryLevelPtr);
  Serial.println("PLACE");
  Serial.println(place);

  // batteryTemperature ISSSS NOOOOOOOOOOOTTTTTTTTTT DDDDDDOOOOOONNNNNNNNNEEEEEE
  if (*power->solarPanelState == true) {
    delayMicroseconds(600);
    float temp = analogRead(A14);
    float conv = temp * 3.25 / 1023.0;
    if (conv > 3.25) {
      conv = 3.25;
    }
    float temp2 = analogRead(A15);
    float conv2 = temp2 * 3.25 / 1023.0;
    if (conv2 > 3.25) {
      conv2 = 3.25;
    }
    Serial.print("Battery Temp1: ");
    Serial.println(conv);
    Serial.print("Battery Temp2: ");
    Serial.println(conv2);
    float comp1 = *power->batteryTemperature;
    float comp2 = *power->batteryTemperature2;
    *power->batteryTemperature = 32*conv + 33;
    *power->batteryTemperature2 = 32*conv2 + 33;
     Serial.print("Battery Temp1 eq: ");
    Serial.println(*power->batteryTemperature);
    Serial.print("Battery Temp2 eq: ");
    Serial.println(*power->batteryTemperature2);
    buffTemp[placeTemp] = *power->batteryTemperature * 1000; // store in millivolts
    if (placeTemp == 15) {
      placeTemp = 0;
    } else {
      placeTemp++;
    }
    buffTemp[placeTemp] = *power->batteryTemperature2 * 1000; // store in millivolts
    if (placeTemp == 15) {
      placeTemp = 0;
    } else {
      placeTemp++;
    }
    float bigger = max(*power->batteryTemperature, *power->batteryTemperature2);
    if (bigger > 1.2 * comp1 && bigger > 1.2 * comp2) {
      *power->batteryOverTemperature = true; 
    } else {
      *power->batteryOverTemperature = false; 
    }
  }
  
  if (place == 15) {
    place = 0;
  } else {
    place++;
  }
  
  *power->batteryLevel = *power->batteryLevelPtr * 100 / 36;
  
  // Logic for calculating the power consumption
  if (*power->powerConsumption > 10) {
    reverse = 1;
  } else if (*power->powerConsumption < 5) {
    reverse = 0;
  }
  if (reverse == 0) {
    if (cycle % 2 == 0) {
      *power->powerConsumption = *power->powerConsumption + 2;
    } else {
      if (*power->powerConsumption > 0) {
        *power->powerConsumption = *power->powerConsumption - 1;
      }
    }
  } else {
    if (cycle % 2 == 0) {
        *power->powerConsumption = *power->powerConsumption + 1;
    } else {
      if (*power->powerConsumption > 1) {
        *power->powerConsumption = *power->powerConsumption - 2;
      }
    }
  }

  // Logic for updating the Power Generation
  if (*power->solarPanelState == true) {
    if (*power->batteryLevel > 95) {
      endOfTravel = true;
      *power->solarPanelState = false;
      *power->powerGeneration = 0;
      *power->solarPanelRetract= true;
    } else {
        if (cycle % 2 == 0) {
          if (*power->powerGeneration + 2 <= 100) {
            *power->powerGeneration = *power->powerGeneration + 2;
          } 
          else { 
            *power->powerGeneration = 100; 
          }
        } else {
          if (*power->batteryLevel < 51) {
            if (*power->powerGeneration + 1 <= 100) {
              *power->powerGeneration = *power->powerGeneration + 1;
            }
          }
        }
    }
  } else {
    if (*power->batteryLevel <= 10) {
      endOfTravel = true;
      *power->solarPanelState = true;
      *power->solarPanelDeploy = true;
    }
  }

}
