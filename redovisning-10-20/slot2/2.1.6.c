#include <stdio.h>
#include <windows.h>

// #define gör att RADER byts ut mot 20 överallt innan programmet kompileras.
// Då behöver vi bara ändra på ett ställe om bilden får en annan storlek.
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

// Hur programmet tänker, i tre steg:
//
//   1. Läs in:     bild.txt   ->  int tal[20][30]     (talen 0-9)
//   2. Omvandla:   tal[i][j]  ->  char bild[20][31]   (ett tecken per tal)
//   3. Skriv ut:   varje rad i bild är en sträng -> skärmen och bild_ut.txt
//
// Ett matrisfält (tvådimensionellt fält) är ett fält av fält.
// tal[i][j] betyder rad i, kolumn j. Båda börjar räkna från 0.

void twoOneSix(void) {
    int tal[RADER][KOLUMNER];
    char bild[RADER][KOLUMNER + 1];     // +1 för nolltecknet sist i varje rad

    // Talet används som index i den här strängen:
    // tecken[0] = ' ', tecken[1] = '.', ... tecken[9] = '#'
    // Ju högre tal, desto "mörkare" tecken.
    char tecken[] = " .:-=+*%@#";       // index 0-9, högre tal ger mer svärta

    char filnamn[100];
    FILE *infil;                        // FILE * är en pekare till en öppen fil
    FILE *utfil;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // %99s läser högst 99 tecken så att filnamn[100] inte kan svämma över
    // (en plats behövs till nolltecknet). filnamn är ett fält, och namnet på
    // ett fält är redan en adress, därför står det inget & framför.
    printf("Vilken fil ska läsas in? (t.ex. bild.txt) ");
    if (scanf("%99s", filnamn) != 1) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    // fopen öppnar filen, "r" betyder read (läsa).
    // Finns inte filen returneras NULL, och då måste vi sluta här.
    infil = fopen(filnamn, "r");
    if (infil == NULL) {
        printf("Kunde inte öppna filen %s.\n", filnamn);
        return;
    }

    // Steg 1: Läs in alla heltal från filen till matrisen.
    // fscanf fungerar som scanf, men läser från filen istället för tangentbordet.
    // Mellanslag och radbrytningar hoppas över automatiskt av %d.
    // fscanf returnerar hur många värden den lyckades läsa, alltså 1 om det gick bra.
    for (int i = 0; i < RADER; i++) {
        for (int j = 0; j < KOLUMNER; j++) {
            if (fscanf(infil, "%d", &tal[i][j]) != 1 || tal[i][j] < 0 || tal[i][j] > 9) {
                printf("Fel i filen på rad %d, tal nummer %d.\n", i + 1, j + 1);
                fclose(infil);
                return;
            }
        }
    }
    fclose(infil);      // stäng filen när vi är klara med den

    // Steg 2: Byt ut varje heltal mot ett tecken och avsluta varje rad med nolltecken.
    // Exempel: tal[i][j] = 9  ->  tecken[9] = '#'  ->  bild[i][j] = '#'
    for (int i = 0; i < RADER; i++) {
        for (int j = 0; j < KOLUMNER; j++) {
            bild[i][j] = tecken[tal[i][j]];
        }
        // Plats 30 (den 31:a) får '\0'. En sträng i C är bara tecken
        // som slutar med '\0', så nu är bild[i] en vanlig sträng.
        bild[i][KOLUMNER] = '\0';
    }

    // "w" betyder write (skriva). Finns filen redan skrivs den över.
    utfil = fopen("bild_ut.txt", "w");
    if (utfil == NULL) {
        printf("Kunde inte skapa filen bild_ut.txt.\n");
        return;
    }

    // Steg 3: Varje rad är nu en sträng och kan skrivas ut med %s.
    // printf skriver till skärmen, fprintf skriver till filen. Annars samma sak.
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
gcc -Wall -Wextra -std=c11 2.1.6.c -o twoOneSix
#endif
