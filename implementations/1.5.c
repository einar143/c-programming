#include <stdio.h>
#include <windows.h>

void dubblera(int *x) {
    *x = *x * 2;
}

void dubblera(int x) {
    x = x * 2;
}

// 1.5.1 --------------------------------------------------------------
void oneFiveOne() {
    int number = 10;
    int *numberpointer = &number;

    // &number          → "where is number?"
    // *numberpointer   → "what is stored where numberpointer points?"
    
    // a)
    printf("%i\n", numberpointer + 1);      // 6422284
    printf("%i\n", number+1);               // 11
    printf("%i\n", *(&number)+1);           // 11
    printf("%i\n", *(numberpointer + 1));   // 6422284
    printf("%i\n", *numberpointer + 1);     // 11
    printf("%i\n", &number + 1);            // 6422284

    // b)
    // & är address-of-operatorn. Den används för att få fram minnesadressen
    // till en variabel.
    //
    // När vi skriver:
    // scanf("%d", &heltal);
    //
    // skickar vi adressen till heltal istället för värdet som heltal innehåller.
    // scanf behöver adressen eftersom funktionen ska kunna skriva det inlästa
    // värdet direkt till variabelns plats i minnet.
    //
    // Samma princip kan användas för att ändra en variabel i en egen funktion.
    
}



// 1.5.11 --------------------------------------------------------------

void oneFiveEleven() {
    // TODO
// char *SafeCopyString ( char *dest, const char *origin, size_t count);

    
}

int main(void) { 
    oneFiveOne();
    dubblera(10);
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 1.5.c -o oneFive
#endif