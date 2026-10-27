#include <stdlib.h>
#include <string.h>
#include "isort.h"

// 2.1.7 isort --------------------------------------------------------
//
// Insättningssortering (insertion sort) fungerar som när man sorterar
// spelkort i handen: man tar upp ett kort i taget och skjuter in det
// på rätt plats bland de kort man redan har sorterat.
//
// Exempel med talen  5 2 4 1:
//
//   i = 1:  ta 2.   5 är större, flytta 5 ett steg höger.       ->  2 5 4 1
//   i = 2:  ta 4.   5 är större, flytta 5.  2 är mindre, stopp. ->  2 4 5 1
//   i = 3:  ta 1.   5, 4 och 2 är större, flytta alla.          ->  1 2 4 5
//
// Allt till vänster om i är alltid sorterat.
// Är listan nästan sorterad behöver nästan inget flyttas, därför är
// insättningssortering snabb just för nästan sorterade listor.
//
// Det svåra här är inte algoritmen utan att funktionen ska fungera för
// ALLA typer (int, double, structs ...), precis som qsort:
//
//   base     adress till första elementet. void * betyder "en adress till
//            vad som helst", funktionen vet inte vilken typ det är.
//   nmemb    antal element i fältet
//   size     hur många byte ett element är, t.ex. sizeof(int) = 4
//   compare  en pekare till en funktion som jämför två element.
//            Det är den som vet vilken typ det är, inte isort.
//            (Pekare till funktioner har vi använt i 1.5.10.)

void isort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *))
{
    // Man får inte räkna med en void-pekare (base + 1 går inte),
    // eftersom C inte vet hur stort ett element är.
    // En char är exakt 1 byte, så med en char-pekare blir
    // falt + 8 precis 8 byte längre fram i minnet.
    char *falt = (char *)base;

    // Element nummer n ligger alltså på adressen  falt + n * size
    // Exempel för int (size = 4):  element 3 ligger 3 * 4 = 12 byte in.

    // Vi behöver en tillfällig plats för elementet vi håller i handen.
    // Vi vet inte hur stort ett element är förrän programmet körs,
    // därför allokeras platsen med malloc istället för en vanlig variabel.
    char *temp = malloc(size);
    size_t i;
    size_t j;

    if (temp == NULL) {
        return;
    }

    for (i = 1; i < nmemb; i++) {
        // memcpy(till, från, antal byte) kopierar byte för byte.
        // Vi kan inte skriva temp = falt[i] eftersom vi inte vet typen,
        // men vi vet hur många byte som ska kopieras: size.
        memcpy(temp, falt + i * size, size);

        // Gå åt vänster så länge elementet till vänster är större än temp.
        // compare returnerar > 0 om första argumentet ska ligga efter det andra.
        //
        // j > 0 måste kontrolleras först: size_t kan inte bli negativ,
        // och när j är 0 finns det inget element till vänster.
        j = i;
        while (j > 0 && compare(falt + (j - 1) * size, temp) > 0) {
            // Flytta det större elementet ett steg åt höger
            memcpy(falt + j * size, falt + (j - 1) * size, size);
            j--;
        }

        // Nu är j den lediga platsen där temp ska in
        memcpy(falt + j * size, temp, size);
    }

    // Allt som allokeras med malloc ska lämnas tillbaka med free
    free(temp);
}
