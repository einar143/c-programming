#include <stdio.h>
#include <windows.h>
#include "ett.h"
#include "tva.h"

// 3.2.1 --------------------------------------------------------------
/* Programmet anropar två funktioner som ligger i varsitt dynamiskt länkat bibliotek.
main.c känner bara till funktionsprototyperna i ett.h och tva.h. Själva koden
för funktionerna ligger i ett.dll och tva.dll och laddas när programmet startar.

"\n" räcker för radmatning och vagnretur, i Windows skrivs det ut som \r\n.
*/

// Hur det hänger ihop:
//
//   ett.c  --gcc -shared-->  ett.dll   (innehåller koden för skrivEtt)
//   tva.c  --gcc -shared-->  tva.dll   (innehåller koden för skrivTva)
//   main.c --gcc---------->  main.exe  (innehåller INTE koden för skrivEtt/skrivTva)
//
// ett.h och tva.h innehåller bara prototyperna, alltså "funktionen finns,
// heter så här och tar inga argument". Det räcker för att kompilatorn ska
// godkänna anropen i main.c. Var koden faktiskt finns löser länkaren.
//
// Statisk länkning (3.1.1): koden kopieras in i main.exe vid bygget.
// Dynamisk länkning (den här uppgiften): main.exe får bara en lapp om att
// "skrivEtt finns i ett.dll", och Windows laddar in .dll-filen när
// programmet startar. Tar man bort ett.dll går main.exe inte att starta.

int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Programstart\n");

    // Anropen ser ut som vanliga funktionsanrop. main.c behöver inte veta
    // att funktionerna ligger i en .dll, det är länkarens sak.
    skrivEtt();     // ligger i ett.dll
    skrivTva();     // ligger i tva.dll

    return 0;
}

#if 0
Bygg de två biblioteken först (-shared gör en .dll istället för en .exe):
gcc -Wall -Wextra -std=c11 -shared ett.c -o ett.dll
gcc -Wall -Wextra -std=c11 -shared tva.c -o tva.dll

Bygg sedan programmet och länka mot biblioteken:
gcc -Wall -Wextra -std=c11 main.c ett.dll tva.dll -o main

ett.dll och tva.dll måste ligga i samma mapp som main.exe när programmet körs.

Bevis på att det är dynamiskt: döp om ett.dll och kör main.exe igen.
Windows säger då att ett.dll saknas och programmet startar inte alls.
#endif
