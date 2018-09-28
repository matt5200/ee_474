/*
Building Your Own Applications
Now that you have successfully run an existing application on the target platform, this
next exercise will have you write your own program and then make a series of changes to
it to gain practice in some of the techniques that we will have to use in our more complex
applications.
*/

void application_one();
void application_two();
void application_three();
void application_four();
void application_five();
void application_six();
void application_seven();
void application_eight();

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
   while(1 == 1) {
   application_one();
   }
   return 0;
}

/*
Application 1
Write a program that will display the letters: A B C D console and flash them
together at approximately a one-second rate.
*/
void application_one() {
    while(1==1){
    sleep(1);
    printf("A B C D \n");
    }
}

/*
Application 2
Modify the program in Application 1 to print then erase the letters A then B then
C then D at approximately a one-second rate.
*/

void application_two() {

}

/*
Application 3
Modify the program in Application 1 to flash the letters A and C at a one-second
rate and the letters B and D at a two-second rate.
*/
void application_three() {

}

/*
Application 4
Modify the program to parameterize the two delay() function calls in the two for
loops so that they will support different user specified delays rather than the
single hard coded value as they are now. Where will those values have to be
specified?
*/

void application_four() {

}

/*
Application 5
Modify the program so that each of the two respective for loops is replaced by the
following functions.
void f1Data(unsigned long delay1);
void f2Clear(unsigned long delay2);
*/

void application_five() {

}

/*
Application 6
Modify the program so that parameter, delay, is passed into the two functions in
part 4 above by reference rather than by value.
*/

void application_six() {

}


/*
Application 7
Modify the program so that the two functions in part 5 above are replaced by a
single function. The function should be able to be called with the character to be
displayed and the value of the delay.
*/
void application_seven() {

}

/*
Application 8
Modify the program so that the function you wrote in part 6 is in a separate file.
Your program will now be composed of two files.
*/

void application_eight() {

}