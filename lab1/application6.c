// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// the main program

int main(void) {

    printf("Please enter a delay value \n");  // get user input for delay value
	int onee;
	int* one = &onee;
	*one = scanf("%d", &onee);  // used for referencing
	printf("Please enter a second delay value \n");  // get user input for delay value
	int twoo;
	int* two = &twoo;
	*two = scanf("%d", &twoo);  // used for referencing

    int h;
    int i;
    int j;
    int count = 0;
    // displays the correct sequence depending on the time elapsed
    for (h = 0; h < 10; h++) {
        count++;
        if (count == 1) {
            printf("abcd\r");
            for (i = 0; i < *one; i++) {   // delay
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
        } else if (count == 2) {
            printf(" b d\r");
            for (i = 0; i < *one; i++) {   // delay
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
        } else if (count == 3) {
            printf("a c\r");
            for (i = 0; i < *one; i++) {    // delay
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
        } else if (count == 4) {
            printf(" b d\r");
            for (i = 0; i < *one; i++) {            // delay
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
        } else if (count == 5) {
            printf("abcd\r");
            for (i = 0; i < *one; i++) {
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
        } else if (count == 6) {
            printf("");
            for (i = 0; i < *one; i++) {           // delay
                for (j = 0; j < *two; j++) {
                    {}
                }
            }
            system("cls");
            count = 0;
        }
    }
	return 0;
}
