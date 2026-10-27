#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <errno.h>

// 1.5.1 c) (versionen utan pekare, void dubblera(int x), ligger i 1.4.c)
void dubblera(int *x) {
    *x = *x * 2;
}

// 1.5.1 --------------------------------------------------------------
void oneFiveOne() {
    int number = 10;
    int *numberpointer = &number;

    // &number          → "where is number?"
    // *numberpointer   → "what is stored where numberpointer points?"
    
    // a)
    printf("%i\n", numberpointer + 1);      // 6422284
    printf("%i\n", number+1);               // 11
    printf("%i\n", *(&number)+1);           // 11
    printf("%i\n", *(numberpointer + 1));   // 6422284
    printf("%i\n", *numberpointer + 1);     // 11
    printf("%i\n", &number + 1);            // 6422284

    // b)
    // & är address-of-operatorn. Den används för att få fram minnesadressen
    // till en variabel.
    //
    // När vi skriver:
    // scanf("%d", &heltal);
    //
    // skickar vi adressen till heltal istället för värdet som heltal innehåller.
    // scanf behöver adressen eftersom funktionen ska kunna skriva det inlästa
    // värdet direkt till variabelns plats i minnet.
    //
    // Samma princip kan användas för att ändra en variabel i en egen funktion.
    
}



// 1.5.2 --------------------------------------------------------------
/* Gör ett program med en meny liknande uppgift 1.3.4. Ditt program skall skapa en sträng i minnet:
char text[] = "Gothenburg";
samt en pekare som pekar på början av strängen:
char *my_pointer = text;
Låt nu användaren manipulera pekaren med menyvalen, och skriv ut vad pekaren pekar på. Pekaren
får inte peka utanför det allokerade minnet.
*/

void oneFiveTwo(void) {
    char text[] = "Gothenburg";
    char *my_pointer = text;
    int langd = strlen(text);
    int choice = 0;
    int c;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    while (choice != 4) {
        printf("Strängen är: \"%s\".\n", text);
        printf("Pekaren pekar på \"%c\", välj en operation:\n", *my_pointer);
        printf("1) Plus 1\n");
        printf("2) Minus 1\n");
        printf("4) Avsluta programmet\n\n");
        printf("> ");

        // Om inmatningen inte är ett heltal töms raden och menyn visas igen
        if (scanf("%d", &choice) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            choice = 0;
        }

        switch (choice) {
            case 1:
                // text + langd - 1 är adressen till sista bokstaven
                if (my_pointer < text + langd - 1) {
                    my_pointer++;
                } else {
                    printf("Pekaren är redan på sista tecknet.\n");
                }
                break;

            case 2:
                // text är adressen till första bokstaven
                if (my_pointer > text) {
                    my_pointer--;
                } else {
                    printf("Pekaren är redan på första tecknet.\n");
                }
                break;

            case 4:
                printf("Programmet avslutas.\n");
                break;

            default:
                printf("Ogiltigt val, välj 1, 2 eller 4.\n");
                break;
        }
    }
}

// 1.5.3 --------------------------------------------------------------
/* Skriv ett program som har tre pekarfält: en int*[], en char*[], och en double*[], alla med 4 element.
Programmet ska skriva ut adressen till alla element med hjälp av en for-loop och pekararitmetik.
Programmet ska även skriva ut skillnaden mellan adresserna i det tredje och det andra elementet av
alla fält.
Vad får du för resultat? Varför är det på detta sätt?
*/

void oneFiveThree(void) {
    int *intFalt[4] = {NULL};
    char *charFalt[4] = {NULL};
    double *doubleFalt[4] = {NULL};

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // intFalt + i är adressen till element nummer i
    printf("%-10s %-12s %-12s %-12s\n", "Element", "int*[]", "char*[]", "double*[]");
    for (int i = 0; i < 4; i++) {
        printf("%-10d %-12p %-12p %-12p\n", i, (void *)(intFalt + i), (void *)(charFalt + i), (void *)(doubleFalt + i));
    }

    // Pekarna görs om till char * för att få skillnaden i byte
    printf("\nSkillnad mellan tredje och andra elementet i byte:\n");
    printf("int*[]:    %d\n", (int)((char *)(intFalt + 2) - (char *)(intFalt + 1)));
    printf("char*[]:   %d\n", (int)((char *)(charFalt + 2) - (char *)(charFalt + 1)));
    printf("double*[]: %d\n", (int)((char *)(doubleFalt + 2) - (char *)(doubleFalt + 1)));

    // Utan omvandlingen räknar C i antal element istället för byte
    printf("\nSkillnad i antal element: %d\n", (int)((intFalt + 2) - (intFalt + 1)));

    printf("\nStorlek på en pekare: %d byte\n", (int)sizeof(int *));
}

// Resultat: skillnaden är lika stor i alla tre fälten (samma som sizeof(int *)).
// Elementen i fälten är pekare, inte int, char eller double. En pekare är en
// adress och alla adresser är lika stora oavsett vad de pekar på.
// Hade fälten varit int[], char[] och double[] hade skillnaden blivit 4, 1 och 8.
//
// Pekararitmetik: intFalt + 1 flyttar ett helt element framåt, alltså
// sizeof(elementet) byte, inte en byte. Därför blir skillnaden 1 i antal element.




















// 1.5.4 --------------------------------------------------------------
/*

ett fält är en fast plats i minnet, en pekare är en variabel som innehåller en adress.

a) double dblField [100];
   
   dblField = dblField + 10;

   Går inte att kompilera. dblField är namnet på ett fält och fungerar som en
   fast adress till första elementet. Det går inte att tilldela ett fält ett
   nytt värde, fältet ligger där det ligger i minnet.

b) double dblField [100], *pDblField;
   
   pDblField = dblField + 10;

   Kompilerar. pDblField är en vanlig pekarvariabel och får adressen till
   element nummer 10, alltså samma sak som &dblField[10].
*/

































// 1.5.10 --------------------------------------------------------------
/* Skriv ett valfritt program som använder sig av ett fält av pekare till funktioner som
alla returnerar ett 32-bitars heltal för att lösa en fritt vald matematisk uppgift.
Följande deklaration finns:
int (*ipFunks [3] ) (void);
*/

// Funktionerna tar inga argument (void), så talen ligger utanför funktionerna
int talA;
int talB;

int summa(void) {
    return talA + talB;
}

int differens(void) {
    return talA - talB;
}

int produkt(void) {
    return talA * talB;
}

void oneFiveTen(void) {
    int (*ipFunks [3] ) (void);
    char *namn[] = {
        "Summa",
        "Differens",
        "Produkt"
    };

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Funktionens namn utan parenteser är adressen till funktionen
    ipFunks[0] = summa;
    ipFunks[1] = differens;
    ipFunks[2] = produkt;

    printf("Mata in två heltal: ");
    if (scanf("%d %d", &talA, &talB) != 2) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }

    // Anropar funktionerna en i taget genom pekarna i fältet
    for (int i = 0; i < 3; i++) {
        printf("%-10s %d\n", namn[i], ipFunks[i]());
    }
}

// 1.5.11 --------------------------------------------------------------
char *SafeCopyString(char *dest, const char *origin, size_t count)
{
    size_t length = 0;
    size_t copied;
    size_t i;
    int backwards = 0;
    int truncated;

    if (dest == NULL || origin == NULL || count == 0) {
        errno = EINVAL;
        return NULL;
    }

    /* Sök efter nolltecknet inom läsgränsen. */
    while (length < count && origin[length] != '\0') {
        ++length;
    }

    truncated = (length == count);
    copied = truncated ? count - 1 : length;

    /* Kontrollera om överlapp kräver kopiering baklänges. */
    for (i = 1; i < copied; ++i) {
        if (dest == origin + i) {
            backwards = 1;
            break;
        }
    }

    if (backwards) {
        for (i = copied; i > 0; --i) {
            dest[i - 1] = origin[i - 1];
        }
    } else {
        for (i = 0; i < copied; ++i) {
            dest[i] = origin[i];
        }
    }

    dest[copied] = '\0';
    errno = truncated ? ERANGE : 0;

    return dest;
}

// Kör en kopiering och skriver ut resultatet och om något fel signalerades
void testaKopiering(char *beskrivning, char *dest, const char *origin, size_t count) {
    char *resultat = SafeCopyString(dest, origin, count);

    printf("%-28s ", beskrivning);
    if (resultat == NULL) {
        printf("FEL: ogiltiga argument, inget kopierades\n");
    } else if (errno == ERANGE) {
        printf("\"%s\" (VARNING: strängen kortades av)\n", resultat);
    } else {
        printf("\"%s\"\n", resultat);
    }
}

void oneFiveEleven(void) {
    char dest[20];
    char liten[5];
    char ejNollterminerad[4] = {'a', 'b', 'c', 'd'};    // saknar '\0'
    char overlapp[20] = "abcdef";
    char inmatning[100];

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // count är hur många tecken som får plats i dest, inklusive nolltecknet
    // (beskrivningarna är utan å, ä, ö för att kolumnerna ska hamna rätt med %-28s)
    testaKopiering("Normal text:", dest, "Hello", sizeof(dest));
    testaKopiering("Tom text:", dest, "", sizeof(dest));
    testaKopiering("dest har bara 5 platser:", liten, "Gothenburg", sizeof(liten));
    testaKopiering("Ej nollterminerad:", dest, ejNollterminerad, sizeof(ejNollterminerad));
    testaKopiering("dest ligger inuti origin:", overlapp + 2, overlapp, 10);
    testaKopiering("dest = NULL:", NULL, "Hello", sizeof(dest));
    testaKopiering("origin = NULL:", dest, NULL, sizeof(dest));
    testaKopiering("count = 0:", dest, "Hello", 0);

    // Egen inmatning kopieras till en buffert med plats för 9 tecken
    printf("\nSkriv en text: ");
    if (fgets(inmatning, sizeof(inmatning), stdin) == NULL) {
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }
    inmatning[strcspn(inmatning, "\n")] = '\0';     // ta bort radbrytningen från fgets

    testaKopiering("Kopia (max 9 tecken):", dest, inmatning, 10);
}

int main(void) {
    // oneFiveOne();
    oneFiveTwo();
    // oneFiveThree();
    // oneFiveTen();
    // oneFiveEleven();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 1.5.c -o oneFive
#endif