// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
//#include <windows.h>
#include <stdlib.h>

// the main program

int main(void) {
    printf("a");
    sleep(1);
    printf("b");
    sleep(1);
    printf("c");
    sleep(1);
    printf("d");
    sleep(1);
    system("clear");
    printf("abc");
    sleep(1);
    system("clear");
    printf("ab");
    sleep(1);
    system("clear");
    printf("a");
    sleep(1);
    system("clear");
	return 0;
}
