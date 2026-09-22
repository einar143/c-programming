#include <stdio.h>
#include <windows.h>


// 1.5.1 --------------------------------------------------------------
void oneFiveOne() {
    int number = 10;
    int *numberpointer = &number;

    //&number   → "where is number?"
    //*numberpointer   → "what is stored where numberpointer points?"
    
    printf("%i\n", numberpointer + 1);      // 6422284
    printf("%i\n", number+1);               // 11
    printf("%i\n", *(&number)+1);           // 11
    printf("%i\n", *(numberpointer + 1));   // 6422284
    printf("%i\n", *numberpointer + 1);     // 11
    printf("%i\n", &number + 1);            // 6422284
}

// 1.5.11 --------------------------------------------------------------

void oneFiveEleven() {
    // TODO
    
}

int main(void) { 
    oneFiveOne();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 1.5.c -o oneFive
#endif