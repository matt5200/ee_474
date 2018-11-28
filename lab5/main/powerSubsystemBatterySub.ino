
void batteryTemp(void* p) {
  powerSubsystemData* power = (powerSubsystemData*) p;
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
}
