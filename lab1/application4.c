// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// the main program

int main(void) {
    int i;
    int j;
    char line[] = "abcd";
    for (i = 0; i < 10; i++) {
        printf(line);
        delay(20);
    }
    for (j = 0; j < 10; j++) {
        printf(line);
        delay(10);
    }

    int count = 0;
    for (i = 0; i < 10; i++) {
        count++;
        if (count == 1) {
            printf("abcd\r");
            Sleep(1000);
            system("cls");
        } else if (count == 2) {
            printf(" b d\r");
            Sleep(1000);
            system("cls");
        } else if (count == 3) {
            printf("a c\r");
            Sleep(1000);
            system("cls");
        } else if (count == 4) {
            printf(" b d\r");
            Sleep(1000);
            system("cls");
        } else if (count == 5) {
            printf("abcd\r");
            Sleep(1000);
            system("cls");
        } else if (count == 6) {
            printf("");
            Sleep(1000);
            system("cls");
            count = 0;
        }
    }
	return 0;
}
