// Nedan följer Einar Bergvikens lösningar för delkapitel 1.1

#include <stdio.h>
#include <windows.h>

// 1.1.1 --------------------------------------------------------------
// a)
void oneOneOne() {
    int number1 = 5;
    int number2 = 10;
    int result = number1*number2;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Låt oss göra lite matte\n");
    printf("%d * %d = %d \n", number1, number2, result);
}

// b)
/*
- Preprocessor är steget som processerar filen och gör saker för att förbereda innan kompilering.
Saker som t.ex att ta bort kommentarer, fixar #include osv. 

- Kompilatorn är det steget som tar en en .c fil och översätter den till assemblerspråk.

- Länkare tar olika filer med binära instruktioner och länkar dem i den ordningen de ska utföras och skapar
skapar en exekverbar fil.
*/

// 1.1.2 --------------------------------------------------------------
/*
a) vad är det hexadecimala värdet för tecknet ”$”?
b) vilka två heltal utgör gränserna för alla versaler i LATIN-1?
c) vilken datatyp används i C för att representera ASCII-tecken?

a) 0x24
b) 65 och 90
c) char


d) skriv ett eget program som skriver ut:
I C kan vi göra en massa saker med escape-sekvenser:
vi har tabb
eller vi kan aktivera ett larm
(programmet ska larma vid exekvering)
OBS: tomrummet mellan ”har” och ”tabb” är ett tabulatortecken.
*/

void oneOneTwoD() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("I C kan vi göra en massa saker med escape-sekvenser:\n");
    printf("vi har tabb\teller vi kan aktivera ett larm\n");
    printf("\a"); // Aktiverar ljud vid körning?
}

// 1.1.3 --------------------------------------------------------------

#if 0
a) /* printf("Skriv ut..."); */
b) // printf("Skriv */ ut...");
c) printf("// Skriv ut...");
d) printf(//"Skriv ut...");
e) printf(/* Skriv ut... */""); 
#endif

// a) Kommer inte skriva ut någonting eftersom raden är kommenterad men komplierar.
// b) Samma som ovan; kommer inte skriva ut någonting eftersom raden är kommenterad men komplierar.
// c) Kommer skriva ut // Skriv ut... eftersom det är en korrekt printf-sats.
// d) Kompilerar inte eftersom // kommenterar bort resten av printf-satsen och printf saknar ");" .
// e) Kommer skriva ut ingenting eftersom det är en korrekt printf-sats men med en tom sträng.


int main(void) { 
    // oneOneOne();
    oneOneTwoD();
    printf("")
}


// gcc -Wall -Wextra -std=c11