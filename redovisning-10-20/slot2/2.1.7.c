#include <stdio.h>
#include <windows.h>
#include "isort.h"

#define ANTAL 20

// 2.1.7 --------------------------------------------------------------
/* Implementera ett alternativ till standardbiblioteks funktionen qsort, genom att använda
insättningssorterings algoritmen. Sorteringsfunktionen ska vara definierad på samma sätt som qsort:
void isort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));
Implementera funktionen i filen isort.c
Skriv också ett program som testar din algoritm för en array med 20 element.
*/

// Själva sorteringen ligger i isort.c. Den här filen testar den.
//
// isort vet inte vilken typ elementen har. Därför skriver vi en
// jämförelsefunktion för varje typ vi vill sortera, och skickar in den.
// Samma isort sorterar då både int och double, det är hela poängen.

// Jämför två int. isort skickar adresserna som const void *,
// så först gör vi om dem till int-pekare och hämtar värdena med *.
//
// Returvärdet följer samma regel som för qsort:
//   < 0  om a ska ligga före b
//   > 0  om a ska ligga efter b
//     0  om de är lika
int jamforInt(const void *p1, const void *p2) {
    int a = *(const int *)p1;
    int b = *(const int *)p2;

    // Man ser ibland "return a - b;" men det kan bli fel (overflow)
    // för väldigt stora tal, så vi jämför istället.
    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    }
    return 0;
}

// Samma sak för double. Bara typen i omvandlingen skiljer.
int jamforDouble(const void *p1, const void *p2) {
    double a = *(const double *)p1;
    double b = *(const double *)p2;

    if (a < b) {
        return -1;
    } else if (a > b) {
        return 1;
    }
    return 0;
}

void skrivIntFalt(int falt[], int antal) {
    for (int i = 0; i < antal; i++) {
        printf("%d ", falt[i]);
    }
    printf("\n");
}

void skrivDoubleFalt(double falt[], int antal) {
    for (int i = 0; i < antal; i++) {
        printf("%.1f ", falt[i]);
    }
    printf("\n");
}

void twoOneSeven(void) {
    // 20 heltal i blandad ordning, med några negativa och några dubbletter
    int heltal[ANTAL] = {42, 7, -3, 19, 0, 88, 7, 15, -10, 63,
                         2, 99, 31, -3, 50, 11, 4, 76, 23, 1};

    // 20 decimaltal som nästan är sorterade, det fall där
    // insättningssortering är som bäst
    double decimaltal[ANTAL] = {0.5, 1.0, 1.5, 3.0, 2.5, 3.5, 4.0, 4.5, 5.0, 5.5,
                                7.0, 6.0, 6.5, 7.5, 8.0, 8.5, 9.0, 9.5, 10.0, 9.9};

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Heltal före:  ");
    skrivIntFalt(heltal, ANTAL);

    // Anropet ser ut precis som ett anrop till qsort:
    //   heltal          adressen till första elementet (fältets namn är en adress)
    //   ANTAL           20 element
    //   sizeof(int)     varje element är 4 byte
    //   jamforInt       funktionens namn utan parenteser är dess adress
    isort(heltal, ANTAL, sizeof(int), jamforInt);

    printf("Heltal efter: ");
    skrivIntFalt(heltal, ANTAL);

    printf("\nDecimaltal före:  ");
    skrivDoubleFalt(decimaltal, ANTAL);

    // Samma funktion, men nu är varje element 8 byte och vi jämför double
    isort(decimaltal, ANTAL, sizeof(double), jamforDouble);

    printf("Decimaltal efter: ");
    skrivDoubleFalt(decimaltal, ANTAL);
}

int main(void) {
    twoOneSeven();
    return 0;
}

#if 0
isort.c måste kompileras med, precis som convert.c i 1.4:
gcc -Wall -Wextra -std=c11 2.1.7.c isort.c -o twoOneSeven
#endif
