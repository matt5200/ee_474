// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// delays the letters a certain amount of time
// dependent on user input
void delay(int e, int two, int one, int f, boolean t2, boolean t1, int cycle) {
    long int c;
    if (cycle < 2) {
        for (c = 1; c <= one*100; c++) {
            e++;
            if (cycle == 0) {
                if (e == two*100) {
                    e = 0;
                    f = 0;
                    t2 = !t2;
                    system("cls");
                    if (t1 == 1 && t2 ==1) {
                        // remove whatever is on screen and put on correct text
                        printf("ABCD\r");
                    } else if (t1 == 0 && t2 == 1) {
                        printf(" B D\r");
                    } else if (t1 == 1 && t2 == 0) {
                        printf("A C\r");
                    } else {
                        system("cls");
                    }
                }
            }
        }
        cycle++;
        delay(e, two, one, f, t2, t1, cycle);
    }
}
