#include <stdio.h>

void change(int *x) {
    *x = 100;
}

void main(void) {
    intint number = 5;
    change(number); 
// Since number is passed by value, 
// the change function will not affect the original variable!
    printf("%d\n", number);
}