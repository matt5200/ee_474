// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// first delay loop
void f1Data(unsigned long delay1, unsigned long delay2) {
    int i;
    int j;
    for (i = 0; i < delay1; i++) {
        for (j = 0; j < delay2; j++) {
            {}
        }
    }
}
