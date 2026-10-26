#include <stdio.h>
#include <windows.h>

// 1.4.4 --------------------------------------------------------------
/* Skriv ett program med en funktion som skifta (eller flytta) ett teckenlöst heltal (unsigned int) ett
antal steg åt vänster. Båda ges som indata. Givet två tal, x och y, så skall bitarna i x flyttas y platser
åt vänster, och bitarna som förloras till vänster hamna till höger.
*/

unsigned int roteraVanster(unsigned int x, unsigned int y) {
    int antalBitar = sizeof(unsigned int) * 8;     // 32 bitar på min dator

    // 32 steg ger samma tal igen, så det är bara resten som spelar roll
    y = y % antalBitar;

    // x >> 32 är inte definierat i C, därför hanteras 0 steg för sig
    if (y == 0) {
        return x;
    }

    // x << y flyttar åt vänster, x >> (32 - y) hämtar bitarna som föll bort och lägger dem till höger
    return (x << y) | (x >> (antalBitar - y));
}

// Skriver ut talet som ettor och nollor så man ser att det funkar
void skrivBitar(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
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

    printf("Före:  %u\n", x);
    skrivBitar(x);
    printf("Efter: %u\n", resultat);
    skrivBitar(resultat);
}

int main(void) {
    oneFourFour();
    return 0;
}

// gcc -Wall -Wextra -std=c11 1.4.4.c -o oneFourFour
