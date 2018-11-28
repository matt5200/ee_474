
unsigned int* imageDataRawPtr ;
unsigned int* imageDataPtr;
int rawData[256];
int notRawData[256];
int freq [16];
int placeTime2;
int freqBuffer[256];

void imageCapture(void* in) {
    signed int a [256];
    signed int b [256];

    for (int i = 0; i < 256; i++) {
        a[i] = analogRead(A11)*.0049*10 - 10;
        rawData[i] = a[i];
        b[i] = 0;
        delayMicroseconds(100);
    }
    
    imageDataRawPtr = rawData;
    int d = optfft(a, b);


      for (int i = 0; i < 256; i++) {
        notRawData[i] = a[i];
    }
       imageDataPtr = notRawData;
    
    Serial.println(d);
    double freq;
    freq = 5000*(d/256.0);
    Serial.print("\n\n Freq WAS ");
    Serial.println(freq);
   if (placeTime2 == 7) {
        placeTime2 = 0;
      } else {
        placeTime2++;
      }
  freqBuffer[placeTime2] = freq;
  Serial.print("Frequency at  the last index was !!!");
  Serial.println(freqBuffer[placeTime2]);
}
