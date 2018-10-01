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

// the main program

int main(void) {

    printf("Please enter a delay value \n");  // get user input for delay value
	int one = scanf("%d", &one);
	printf("Please enter a second delay value \n");  // get user input for delay value
	int two = scanf("%d", &two);

    int h;
    int count = 0;
    // displays the correct sequence depending on the time elapsed
    for (h = 0; h < 10; h++) {
        count++;
        if (count == 1) {
            printf("abcd\r");
            f1Data(one, two);
            system("cls");
        } else if (count == 2) {
            printf(" b d\r");
            f1Data(one, two);
            system("cls");
        } else if (count == 3) {
            printf("a c\r");
            f1Data(one, two);
            system("cls");
        } else if (count == 4) {
            printf(" b d\r");
            f1Data(one, two);
            system("cls");
        } else if (count == 5) {
            printf("abcd\r");
            f1Data(one, two);
            system("cls");
        } else if (count == 6) {
            printf("");
            f1Data(one, two);
            system("cls");
            count = 0;
        }
    }
	return 0;
}
