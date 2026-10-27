#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>

#define MAXTEXT     30000   // max antal tecken (byte) i texten
#define MAXORD      2000    // max antal olika ord vi kan hålla reda på
#define MAXLANGD    50      // max längd på ett ord, inklusive '\0'
#define ANTALKODER  5       // vi byter ut de fem vanligaste orden

// 2.1.4 --------------------------------------------------------------
/* Använd en godtycklig text på ca 2-3 sidor som du sparar som en fil och skriv sedan ett program
som hittar de fem ord som förekommer mest frekvent. Programmet ska sedan ersätta dessa med
varsin 'kod' som (helst) tar mindre utrymme i minnet. Skriv ut resultatet till en ny fil och meddela i
kommandofönstret hur mycket plats som sparats. Skriv en funktion för att dekomprimera filen och
kontrollera att originaltexten återfås.
*/

// Hur programmet tänker:
//
//   1. Läs hela text.txt till ett char-fält i minnet.
//   2. Gå igenom texten ord för ord och räkna hur många gånger varje ord finns.
//   3. Välj ut de fem ord som finns flest gånger.
//   4. Komprimera: skriv texten till en ny fil, men byt ut de fem orden mot
//      ett enda tecken var:  # $ % & @
//      Exempel:  "det är som det är"  ->  "# $ % # $"  (om det, är, som valts)
//      Ordet "som" är 3 byte men koden % är bara 1 byte, så varje gång
//      "som" förekommer sparar vi 2 byte.
//   5. Dekomprimera: läs den komprimerade filen och byt tillbaka koderna mot orden.
//   6. Jämför den dekomprimerade filen med originalet, byte för byte.
//
// Hur vet dekomprimeringen vilket ord en kod betyder?
// Vi skriver de fem orden på första raden i den komprimerade filen:
//
//   det är som att en          <- första raden: ordlistan
//   # $ ... resten av texten   <- texten med koder
//
// Första ordet hör till #, andra till $, och så vidare. Den raden tar
// också plats, och räknas med när vi räknar ut hur mycket som sparats.

// Koderna. koder[0] = '#' står för det vanligaste ordet, koder[1] = '$' för det näst
// vanligaste osv. Det här är tecken som inte brukar finnas i vanlig text.
// Ligger utanför funktionerna eftersom både komprimera och dekomprimera behöver dem.
char koder[ANTALKODER] = {'#', '$', '%', '&', '@'};

// Avgör om ett tecken är en del av ett ord.
// isalpha (från ctype.h) känner bara igen a-z och A-Z.
// å, ä och ö sparas i filen som två byte var (UTF-8), och de byten har
// alltid ett värde på 128 eller mer. Därför räknar vi sådana byte som bokstäver.
// (unsigned char) behövs eftersom char kan vara negativ på vissa datorer.
int arBokstav(char c) {
    if (isalpha((unsigned char)c) || (unsigned char)c >= 128) {
        return 1;
    }
    return 0;
}

// Läser hela filen till fältet text. Returnerar antal byte, eller -1 vid fel.
//
// "rb" betyder att filen läses i binärläge. Då ändrar inte Windows på
// radbrytningarna, och vi får exakt de byte som ligger i filen.
// Det är viktigt här eftersom vi ska jämföra filstorlekar och innehåll exakt.
int lasFil(char *filnamn, char text[]) {
    FILE *fil = fopen(filnamn, "rb");
    int langd = 0;
    int c;

    if (fil == NULL) {
        printf("Kunde inte öppna filen %s.\n", filnamn);
        return -1;
    }

    // fgetc läser ett tecken i taget och returnerar EOF när filen är slut.
    // c är en int och inte en char, eftersom EOF inte är ett vanligt tecken.
    while ((c = fgetc(fil)) != EOF) {
        if (langd >= MAXTEXT - 1) {
            printf("Filen är för stor, max %d tecken.\n", MAXTEXT - 1);
            fclose(fil);
            return -1;
        }
        text[langd] = c;
        langd++;
    }
    text[langd] = '\0';     // gör texten till en sträng

    fclose(fil);
    return langd;
}

// Kopierar ordet som börjar på text[start] till ord och returnerar ordets längd.
// Exempel: text = "Det är", start = 0  ->  ord = "Det", returnerar 3
int lasOrd(char text[], int start, char ord[]) {
    int j = 0;

    // Fortsätt så länge det är bokstäver. '\0' i slutet av texten är ingen
    // bokstav, så loopen slutar där också. j < MAXLANGD - 1 skyddar ord[]
    // från att svämma över om ett ord skulle vara extremt långt.
    while (arBokstav(text[start + j]) && j < MAXLANGD - 1) {
        ord[j] = text[start + j];
        j++;
    }
    ord[j] = '\0';

    return j;
}

// Går igenom texten och räknar hur många gånger varje ord förekommer.
// ordlista[i] är ett ord och antal[i] är hur många gånger det finns.
// Returnerar hur många olika ord som hittades.
//
// char ordlista[][MAXLANGD] är ett fält av strängar (ett matrisfält av char,
// som bild i 2.1.6). Vid en parameter måste antalet kolumner stå med,
// annars vet C inte hur långt det är mellan två ord i minnet.
int raknaOrd(char text[], int langd, char ordlista[][MAXLANGD], int antal[]) {
    int antalOlika = 0;
    char ord[MAXLANGD];
    int i = 0;
    int hittad;

    while (i < langd) {
        if (arBokstav(text[i])) {
            int ordLangd = lasOrd(text, i, ord);

            // Finns ordet redan i listan? strcmp returnerar 0 om två strängar
            // är lika. (Med == jämför man adresser, inte innehållet.)
            hittad = 0;
            for (int k = 0; k < antalOlika; k++) {
                if (strcmp(ordlista[k], ord) == 0) {
                    antal[k]++;
                    hittad = 1;
                    break;
                }
            }

            // Nytt ord: lägg det sist i listan med antal 1
            if (!hittad && antalOlika < MAXORD) {
                strcpy(ordlista[antalOlika], ord);
                antal[antalOlika] = 1;
                antalOlika++;
            }

            i = i + ordLangd;   // hoppa förbi hela ordet
        } else {
            i++;                // mellanslag, punkt, radbrytning ... hoppa ett steg
        }
    }

    return antalOlika;
}

// Väljer ut de fem ord som förekommer flest gånger och kopierar dem till vanligaste.
// Varje varv letar vi upp det ord med högst antal som inte redan är valt.
void hittaVanligaste(char ordlista[][MAXLANGD], int antal[], int antalOlika,
                     char vanligaste[][MAXLANGD], int vanligasteAntal[]) {
    int redanVald[MAXORD] = {0};    // 1 om ordet redan är valt, alla börjar på 0

    for (int k = 0; k < ANTALKODER; k++) {
        int basta = -1;     // index till det bästa ordet hittills, -1 = inget än

        for (int i = 0; i < antalOlika; i++) {
            if (!redanVald[i] && (basta == -1 || antal[i] > antal[basta])) {
                basta = i;
            }
        }

        redanVald[basta] = 1;
        strcpy(vanligaste[k], ordlista[basta]);
        vanligasteAntal[k] = antal[basta];
    }
}

// Skriver den komprimerade filen. Returnerar 1 om det gick bra, annars 0.
int komprimera(char text[], int langd, char vanligaste[][MAXLANGD], char *utfilnamn) {
    FILE *utfil = fopen(utfilnamn, "wb");
    char ord[MAXLANGD];
    int i = 0;

    if (utfil == NULL) {
        printf("Kunde inte skapa filen %s.\n", utfilnamn);
        return 0;
    }

    // Första raden: de fem orden, så att dekomprimeringen vet vad koderna betyder
    for (int k = 0; k < ANTALKODER; k++) {
        fprintf(utfil, "%s", vanligaste[k]);
        if (k < ANTALKODER - 1) {
            fprintf(utfil, " ");
        }
    }
    fprintf(utfil, "\n");

    // Samma genomgång av texten som i raknaOrd, men nu skriver vi istället för att räkna
    while (i < langd) {
        if (arBokstav(text[i])) {
            int ordLangd = lasOrd(text, i, ord);
            int kod = -1;   // -1 betyder att ordet inte är ett av de fem

            for (int k = 0; k < ANTALKODER; k++) {
                if (strcmp(ord, vanligaste[k]) == 0) {
                    kod = k;
                }
            }

            if (kod != -1) {
                fputc(koder[kod], utfil);   // skriv koden, ett enda tecken
            } else {
                fputs(ord, utfil);          // skriv ordet som det är
            }

            i = i + ordLangd;
        } else {
            // Allt som inte är bokstäver (mellanslag, punkter, radbrytningar)
            // kopieras precis som det är
            fputc(text[i], utfil);
            i++;
        }
    }

    fclose(utfil);
    return 1;
}

// Läser den komprimerade filen och skriver tillbaka originaltexten.
// Funktionen behöver inget från resten av programmet: ordlistan står i filen.
// Returnerar 1 om det gick bra, annars 0.
int dekomprimera(char *infilnamn, char *utfilnamn) {
    char ordlista[ANTALKODER][MAXLANGD];
    FILE *infil = fopen(infilnamn, "rb");
    FILE *utfil;
    int c;
    int hittad;

    if (infil == NULL) {
        printf("Kunde inte öppna filen %s.\n", infilnamn);
        return 0;
    }

    // Läs de fem orden på första raden. %49s läser ett ord (fram till ett mellanslag).
    for (int k = 0; k < ANTALKODER; k++) {
        if (fscanf(infil, "%49s", ordlista[k]) != 1) {
            printf("Den komprimerade filen saknar ordlistan.\n");
            fclose(infil);
            return 0;
        }
    }
    fgetc(infil);   // läs bort radbrytningen efter ordlistan

    utfil = fopen(utfilnamn, "wb");
    if (utfil == NULL) {
        printf("Kunde inte skapa filen %s.\n", utfilnamn);
        fclose(infil);
        return 0;
    }

    // Ett tecken i taget: är det en kod skriver vi ordet, annars tecknet självt
    while ((c = fgetc(infil)) != EOF) {
        hittad = 0;
        for (int k = 0; k < ANTALKODER; k++) {
            if (c == koder[k]) {
                fputs(ordlista[k], utfil);
                hittad = 1;
            }
        }
        if (!hittad) {
            fputc(c, utfil);
        }
    }

    fclose(infil);
    fclose(utfil);
    return 1;
}

// Räknar hur många byte en fil är genom att läsa den tecken för tecken
long filStorlek(char *filnamn) {
    FILE *fil = fopen(filnamn, "rb");
    long storlek = 0;

    if (fil == NULL) {
        return -1;
    }
    while (fgetc(fil) != EOF) {
        storlek++;
    }
    fclose(fil);
    return storlek;
}

// Jämför två filer byte för byte. Returnerar 1 om de är exakt lika, annars 0.
int jamforFiler(char *filnamn1, char *filnamn2) {
    FILE *fil1 = fopen(filnamn1, "rb");
    FILE *fil2 = fopen(filnamn2, "rb");
    int c1;
    int c2;
    int lika = 1;

    if (fil1 == NULL || fil2 == NULL) {
        printf("Kunde inte öppna filerna för jämförelse.\n");
        if (fil1 != NULL) fclose(fil1);
        if (fil2 != NULL) fclose(fil2);
        return 0;
    }

    // Läs ett tecken från varje fil tills de skiljer sig eller båda tar slut.
    // Är den ena filen kortare blir c1 eller c2 EOF och då skiljer de sig också.
    do {
        c1 = fgetc(fil1);
        c2 = fgetc(fil2);
        if (c1 != c2) {
            lika = 0;
        }
    } while (lika && c1 != EOF);

    fclose(fil1);
    fclose(fil2);
    return lika;
}

void twoOneFour(void) {
    // static gör att de stora fälten inte läggs på stacken (som är begränsad),
    // utan på samma ställe som globala variabler. ordlista är 2000 * 50 = 100 000 byte.
    static char text[MAXTEXT];
    static char ordlista[MAXORD][MAXLANGD];
    static int antal[MAXORD];

    char vanligaste[ANTALKODER][MAXLANGD];
    int vanligasteAntal[ANTALKODER];
    char filnamn[100];
    int langd;
    int antalOlika;
    long originalStorlek;
    long komprimeradStorlek;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Vilken fil ska komprimeras? (t.ex. text.txt) ");
    if (scanf("%99s", filnamn) != 1) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    // 1. Läs in texten
    langd = lasFil(filnamn, text);
    if (langd < 0) {
        return;
    }
    if (langd == 0) {
        printf("Filen är tom, det finns inget att komprimera.\n");
        return;
    }

    // Koderna får inte redan finnas i texten, då vet dekomprimeringen inte
    // om # betyder ett ord eller ett riktigt #. strchr letar efter ett tecken
    // i en sträng och returnerar NULL om det inte finns.
    for (int k = 0; k < ANTALKODER; k++) {
        if (strchr(text, koder[k]) != NULL) {
            printf("Texten innehåller redan tecknet %c, kan inte använda det som kod.\n", koder[k]);
            return;
        }
    }

    // 2. Räkna orden
    antalOlika = raknaOrd(text, langd, ordlista, antal);
    if (antalOlika < ANTALKODER) {
        printf("Texten har färre än %d olika ord.\n", ANTALKODER);
        return;
    }

    // 3. Hitta de fem vanligaste
    hittaVanligaste(ordlista, antal, antalOlika, vanligaste, vanligasteAntal);

    printf("\nTexten har %d tecken och %d olika ord.\n", langd, antalOlika);
    printf("De fem vanligaste orden:\n");
    for (int k = 0; k < ANTALKODER; k++) {
        // Inget %-8s här: ä är 2 byte och då hamnar kolumnerna snett (samma som i 1.5.11)
        printf("  %c  =  %s, %d gånger\n", koder[k], vanligaste[k], vanligasteAntal[k]);
    }

    // 4. Komprimera
    if (!komprimera(text, langd, vanligaste, "komprimerad.txt")) {
        return;
    }

    originalStorlek = filStorlek(filnamn);
    komprimeradStorlek = filStorlek("komprimerad.txt");

    printf("\nOriginal:     %ld byte\n", originalStorlek);
    printf("Komprimerad:  %ld byte (sparad i komprimerad.txt)\n", komprimeradStorlek);
    // 100.0 och inte 100, annars blir det heltalsdivision och svaret blir 0
    printf("Sparat:       %ld byte (%.1f %%)\n", originalStorlek - komprimeradStorlek,
           100.0 * (originalStorlek - komprimeradStorlek) / originalStorlek);

    // 5. Dekomprimera
    if (!dekomprimera("komprimerad.txt", "dekomprimerad.txt")) {
        return;
    }

    // 6. Kontrollera att vi fick tillbaka exakt samma text
    if (jamforFiler(filnamn, "dekomprimerad.txt")) {
        printf("\nKontroll: dekomprimerad.txt är identisk med %s.\n", filnamn);
    } else {
        printf("\nKontroll: FEL, dekomprimerad.txt skiljer sig från %s.\n", filnamn);
    }
}

int main(void) {
    twoOneFour();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 2.1.4.c -o twoOneFour
#endif
