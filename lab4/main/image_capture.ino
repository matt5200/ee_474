
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Serial.println("JUST ONCE ->->->->->->->->->->->->->->->->");
}

void loop() {
    signed int a [256];
    signed int b [256];
    
    for (int i = 0; i < 256; i++) {
        a[i] = analogRead(A0)*.0049*10 - 10;
     //   Serial.println(a[i]);
        b[i] = 0;
        delayMicroseconds(100);
    }
    int d = optfft(a, b);
//    Serial.println("INDEX IS ");

    Serial.println(d);
/*
    f=fs *m_index /N
    f: freq of the measured signal
    fs: sample freq
    m_index: index which corresponds to the maximum magnitude
    Mag^2 = real^2 +imag^2
    N: sequence length or N=2^m
*/
    double freq;// = pow((a[d]*a[d] + b[d]*b[d]),.5);
    freq = 5000*(d/256.0);
    Serial.print("\n\n D WAS ");
    Serial.println(d);
    Serial.print("\n\n Freq WAS ");
    Serial.println(freq);
}
