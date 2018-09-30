// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// the main program

int main(void) {
    int i;
    // flashes abcd in about one-second intervals
    for (i = 0; i < 10; i++) {
        printf("abcd\r");
        Sleep(1000);
        system("cls");
        Sleep(1000);
    }
	return 0;
}
