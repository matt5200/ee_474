// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// delays the letters a certain amount of time
// depending on user input
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

// the main program

int main(void) {

    printf("Please enter a delay value \n");  // get user input for delay value
	int one = scanf("%d", &one);
	printf("Please enter a second delay value \n");  // get user input for delay value
	int two = scanf("%d", &two);

   // int h;
   // int i;
   // int j;
    int e = 0;
    int f = 0;
    int count = 0;
    // When t1 is true, then AB should be printed
    boolean t1 = 1;
    // When t2 is true, the CD should be printed
    // when both are true, then both should be printed
    boolean t2 = 1;
    // displays the correct sequence depending on the time elapsed
    while (1==1) {

    // Four possible prints
    // A B
    // C D
    // ABCD

        printf("ABCD\r");
        // after the following code has executed
        // the A B letters must change state
        delay(e, two, one, f, t2, t1, 0);
        t1 = !t1;
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
	return 0;
}
