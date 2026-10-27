#include <stdio.h>
#include <windows.h>
#include <limits.h>

// 1.4.2 --------------------------------------------------------------

void dubblera(int x) {
    x = 2 * x;
}

// b)
int dubbleraRetur(int x) {
    return 2 * x;
}

void oneFourTwo(void) {
    int number = 5;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Före dubblera: %d\n", number);
    dubblera(number);
    printf("Efter dubblera: %d\n", number);

    number = dubbleraRetur(number);
    printf("Efter dubbleraRetur: %d\n", number);
}

// a) Programmet skriver ut 5 både före och efter dubblera.
// C skickar argument "by value", så x i dubblera är en kopia av number.
// Funktionen dubblerar bara kopian, och kopian försvinner när funktionen är klar.
//
// b) Antingen returnerar funktionen det nya värdet (dubbleraRetur ovan) och
// man skriver number = dubbleraRetur(number), eller så tar funktionen emot
// en pekare, void dubblera(int *x), och ändrar värdet på adressen (se 1.5.1 c).

































// 1.4.4 --------------------------------------------------------------
/* Skriv ett program med en funktion som skifta (eller flytta) ett teckenlöst heltal (unsigned int) ett
antal steg åt vänster. Båda ges som indata. Givet två tal, x och y, så skall bitarna i x flyttas y platser
åt vänster, och bitarna som förloras till vänster hamna till höger.
*/






unsigned int roteraVanster(unsigned int x, unsigned int y) {
    unsigned int antalBitar = sizeof(unsigned int) * CHAR_BIT;

    // Att rotera 32 steg ger samma tal igen, så bara resten behövs
    y = y % antalBitar;

    // x >> 32 är inte definierat i C, så noll steg hanteras för sig
    if (y == 0) {
        return x;
    }

    // Vänstra delen skiftas ut, och samma bitar hämtas in från höger
    return (x << y) | (x >> (antalBitar - y));
}

// Skriver ut alla bitar i ett tal, mest signifikanta biten först
void skrivBitar(unsigned int x) {
    int antalBitar = sizeof(unsigned int) * CHAR_BIT;

    for (int i = antalBitar - 1; i >= 0; i--) {
        printf("%u", (x >> i) & 1);
    }
    printf("\n");
}

void oneFourFour(void) {
    unsigned int x;
    unsigned int y;
    unsigned int resultat;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Mata in ett positivt heltal x: ");
    if (scanf("%u", &x) != 1) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    printf("Hur många steg åt vänster? ");
    if (scanf("%u", &y) != 1) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    resultat = roteraVanster(x, y);

    printf("\nFöre:  %10u  ", x);
    skrivBitar(x);
    printf("Efter: %10u  ", resultat);
    skrivBitar(resultat);
}

int main(void) {
    oneFourTwo();
    // oneFourFour();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 1.4.c -o oneFour
#endif
