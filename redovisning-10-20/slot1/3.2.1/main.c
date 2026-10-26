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

int main(void)
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Programstart\n");
    skrivEtt();     // ligger i ett.dll
    skrivTva();     // ligger i tva.dll

    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 -shared ett.c -o ett.dll
gcc -Wall -Wextra -std=c11 -shared tva.c -o tva.dll
gcc -Wall -Wextra -std=c11 main.c ett.dll tva.dll -o main

ett.dll och tva.dll måste ligga i samma mapp som main.exe när programmet körs.
#endif
