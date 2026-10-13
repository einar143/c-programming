#include <stdio.h>
#include <windows.h>

#define RADER       20
#define KOLUMNER    30

// 2.1.6 --------------------------------------------------------------
/* Skapa en textfil som består av 20 rader, var och en innehållande 30 heltal. Heltalen ska vara i
intervallet 0-9 och separeras med mellanslag. Filen är en digital representation av en bild, där
värdena 0 till 9 representerar ökande nivåer av mörker. Skriv ett program som läser innehållet i filen
till ett 20x30-matrisfält av heltal. Omvandla den digitala representationen till en bild, där
programmet använder värdena för att initiera ett 20x31-matrisfält av tecken, där ett 0-värde
motsvaras av ett mellanslag, värdet 1 av en punkt, och så vidare. Sista tecknet (det 31:a) i varje rad
bör vara ett null-tecken, vilket gör matrisen till ett fält med 20 strängar. Låt programmet visa den
resulterande bilden samt lagra resultatet i en textfil.
*/

void twoOneSix(void) {
    int tal[RADER][KOLUMNER];
    char bild[RADER][KOLUMNER + 1];
    char tecken[] = " .:-=+*%@#";       // index 0-9, högre tal ger mer svärta
    char filnamn[100];
    FILE *infil;
    FILE *utfil;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Vilken fil ska läsas in? (t.ex. bild.txt) ");
    if (scanf("%99s", filnamn) != 1) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    infil = fopen(filnamn, "r");
    if (infil == NULL) {
        printf("Kunde inte öppna filen %s.\n", filnamn);
        return;
    }

    // Läs in alla heltal från filen till matrisen
    for (int i = 0; i < RADER; i++) {
        for (int j = 0; j < KOLUMNER; j++) {
            if (fscanf(infil, "%d", &tal[i][j]) != 1 || tal[i][j] < 0 || tal[i][j] > 9) {
                printf("Fel i filen på rad %d, tal nummer %d.\n", i + 1, j + 1);
                fclose(infil);
                return;
            }
        }
    }
    fclose(infil);

    // Byt ut varje heltal mot ett tecken och avsluta varje rad med nolltecken
    for (int i = 0; i < RADER; i++) {
        for (int j = 0; j < KOLUMNER; j++) {
            bild[i][j] = tecken[tal[i][j]];
        }
        bild[i][KOLUMNER] = '\0';
    }

    utfil = fopen("bild_ut.txt", "w");
    if (utfil == NULL) {
        printf("Kunde inte skapa filen bild_ut.txt.\n");
        return;
    }

    // Varje rad är nu en sträng och kan skrivas ut med %s
    for (int i = 0; i < RADER; i++) {
        printf("%s\n", bild[i]);
        fprintf(utfil, "%s\n", bild[i]);
    }
    fclose(utfil);

    printf("\nBilden är sparad i bild_ut.txt.\n");
}

int main(void) {
    twoOneSix();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 2.1.c -o twoOne
#endif
