#include <stdio.h>

int age = 23;
float temperature = 22.5f;
double pi = 3.1415926535;
char letter = 'A';
char name[] = "Einar";

int *ptr = &x;

int main(void) {
    printf("Hello, world!\n");
    printf("I am %d years old\n", age);
    printf("The temperature is %.1f degrees Celsius\n", temperature);
    printf("Pi is approximately %.10f\n", pi);
    printf("The first letter of the alphabet is %c\n", letter);
    printf("My name is %s\n", name);
    return 0;
}