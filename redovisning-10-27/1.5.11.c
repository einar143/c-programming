#include <stdio.h>
#include <windows.h>

// 1.5.11 --------------------------------------------------------------
/* Skriv ett program med en eller flera funktioner som kopierar information från en sträng till en
annan. Er deklaration (och definition) ska se ut så här:

        char *SafeCopyString ( char *dest, const char *origin, size_t count);

Funktionen ska returnera pekaren till den resulterande strängen och om det är nödvändigt ska den
också signalera till användaren att ett fel inträffat under kopieringen. Tänk igenom vilka specialfall
det finns. Det är inte tillåtet att använda standardfunktionen strncpy () eller liknande funktioner.
Testa programmet med alla olika aktuella parametrar.
*/

// count = hur många tecken som får plats i dest, nolltecknet inräknat.
// Funktionen läser aldrig mer än count tecken från origin, så även en sträng
// utan '\0' i slutet går att kopiera utan att man läser utanför den.
char *SafeCopyString(char *dest, const char *origin, size_t count) {
    size_t i = 0;

    // Specialfall: inget att kopiera till/från, eller ingen plats alls
    if (dest == NULL || origin == NULL || count == 0) {
        printf("Fel: ogiltiga argument, inget kopierades.\n");
        return NULL;
    }

    // Kopiera tecken för tecken tills '\0' kommer eller dest är full (en plats sparas till '\0')
    while (i < count - 1 && origin[i] != '\0') {
        dest[i] = origin[i];
        i++;
    }
    dest[i] = '\0';

    // Om vi inte stannade på '\0' så fanns det mer kvar i origin som inte fick plats
    if (origin[i] != '\0') {
        printf("Varning: texten fick inte plats och kortades av.\n");
    }

    return dest;
}

void oneFiveEleven(void) {
    char dest[10];
    char inteNollterminerad[4] = {'a', 'b', 'c', 'd'};     // saknar '\0'
    char *resultat;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("1. Vanlig text:\n");
    resultat = SafeCopyString(dest, "Hej", sizeof(dest));
    printf("\"%s\"\n\n", resultat);

    printf("2. Tom text:\n");
    resultat = SafeCopyString(dest, "", sizeof(dest));
    printf("\"%s\"\n\n", resultat);

    printf("3. För lång text (dest har 10 platser):\n");
    resultat = SafeCopyString(dest, "Gothenburg Sweden", sizeof(dest));
    printf("\"%s\"\n\n", resultat);

    printf("4. Text utan nolltecken:\n");
    resultat = SafeCopyString(dest, inteNollterminerad, sizeof(inteNollterminerad));
    printf("\"%s\"\n\n", resultat);

    printf("5. dest = NULL:\n");
    resultat = SafeCopyString(NULL, "Hej", sizeof(dest));
    if (resultat == NULL) {
        printf("Fick tillbaka NULL\n\n");
    }

    printf("6. origin = NULL:\n");
    resultat = SafeCopyString(dest, NULL, sizeof(dest));
    if (resultat == NULL) {
        printf("Fick tillbaka NULL\n\n");
    }

    printf("7. count = 0:\n");
    resultat = SafeCopyString(dest, "Hej", 0);
    if (resultat == NULL) {
        printf("Fick tillbaka NULL\n");
    }
}

int main(void) {
    oneFiveEleven();
    return 0;
}

// gcc -Wall -Wextra -std=c11 1.5.11.c -o oneFiveEleven
