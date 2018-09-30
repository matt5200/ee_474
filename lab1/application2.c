// preprocessor directive to support printing to the display

#include <stdio.h>
#include <unistd.h>
#include <windows.h>
#include <stdlib.h>

// the main program

int main(void) {
    printf("a");
    Sleep(1000);
    printf("b");
    Sleep(1000);
    printf("c");
    Sleep(1000);
    printf("d");
    Sleep(1000);
    system("cls");
    printf("abc");
    Sleep(1000);
    system("cls");
    printf("ab");
    Sleep(1000);
    system("cls");
    printf("a");
    Sleep(1000);
    system("cls");
	return 0;
}
