#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

// 1.6.1 --------------------------------------------------------------
/* Utgå från följande deklaration av en nod i en dubbelt länkad lista:

struct node {
    double data;
    struct node *next;
    struct node *previous;
};

Skriv ett program som har interaktiva funktioner för att
    a) Skapa en ny nod (dvs, kedjan med en ensam nod),
    b) lägga till en nod i slutet av kedjan av noder,
    c) ta bort en nod på en viss plats i kedjan av noder,
    d) gå igenom kedjan och skriva ut alla värden.
Och demonstrera denna funktionalitet. Ditt program måste allokera noderna dynamiskt,
och frigöra minnet för dem efteråt.
*/

struct node {
    double data;
    struct node *next;          // nästa nod, NULL om det här är den sista
    struct node *previous;      // föregående nod, NULL om det här är den första
};

// a) Allokerar en ny nod med malloc. Noden har inga grannar från början.

// malloc(sizeof(struct node)) ber om precis så många byte som en nod behöver
struct node *skapaNod(double data) {
    struct node *nyNod = malloc(sizeof(struct node));

    // malloc returnerar NULL om det inte fanns något minne kvar
    if (nyNod == NULL) {
        printf("Kunde inte allokera minne.\n");
        exit(1);
    }

    // -> används när vi har en PEKARE till en struct.
    // nyNod->data betyder samma sak som (*nyNod).data,
    // alltså "gå till adressen nyNod och ta fältet data".
    nyNod->data = data;
    nyNod->next = NULL;
    nyNod->previous = NULL;

    return nyNod;
}

// b) Lägger till en ny nod sist i kedjan och returnerar början av kedjan.
//
// Funktionen returnerar forsta eftersom forsta kan ändras: om kedjan var tom
// blir den nya noden den första.
// vi returnerar det nya värdet istället för att ändra via en pekare.)
struct node *laggTillSist(struct node *forsta, double data) {
    struct node *nyNod = skapaNod(data);
    struct node *aktuell = forsta;

    // Tom kedja: den nya noden blir hela kedjan
    if (forsta == NULL) {
        return nyNod;
    }

    // Gå framåt nod för nod tills vi står på den sista.
    // Den sista noden känns igen på att dess next är NULL.
    while (aktuell->next != NULL) {
        aktuell = aktuell->next;
    }

    // Koppla ihop åt båda hållen:
    //   [aktuell] -> [nyNod]   och   [aktuell] <- [nyNod]
    aktuell->next = nyNod;
    nyNod->previous = aktuell;

    return forsta;
}

// c) Tar bort noden på en viss plats (plats 1 är den första noden)
// och returnerar början av kedjan, eftersom den kan ändras om vi tar bort plats 1.
struct node *taBortNod(struct node *forsta, int plats) {
    struct node *aktuell = forsta;
    int i = 1;

    if (forsta == NULL) {
        printf("Kedjan är tom, det finns inget att ta bort.\n");
        return NULL;
    }

    if (plats < 1) {
        printf("Platserna börjar på 1.\n");
        return forsta;
    }

    // Gå fram till noden på rätt plats.
    // Tar slut på kedjan (aktuell blir NULL) om platsen inte finns.
    while (aktuell != NULL && i < plats) {
        aktuell = aktuell->next;
        i++;
    }

    if (aktuell == NULL) {
        printf("Det finns ingen nod på plats %d.\n", plats);
        return forsta;
    }

    // Nu ska aktuell lyftas ut och grannarna kopplas ihop med varandra:
    //
    //   före:   [A] <-> [aktuell] <-> [B]
    //   efter:  [A] <-> [B]

    // A:s next ska peka på B. Finns det ingen A tar vi bort den första noden,
    // och då blir B den nya första.
    
    // aktuell->previous->next  =  aktuell->next;
    //└──────┬─────────┘└─┬─┘    └──────┬─────┘
    //   noden A       A:s next      noden B
    if (aktuell->previous != NULL) {
        aktuell->previous->next = aktuell->next;
    } else {
        forsta = aktuell->next;
    }

    // B:s previous ska peka på A. Finns det ingen B tar vi bort den sista noden
    // och då behöver ingenting göras här.
    if (aktuell->next != NULL) {
        aktuell->next->previous = aktuell->previous;
    }

    // Först nu, när ingen annan nod pekar på aktuell, lämnar vi tillbaka minnet.
    // Om vi gjorde free först skulle vi inte längre få läsa aktuell->next.
    printf("Tog bort %.2f från plats %d.\n", aktuell->data, plats);
    free(aktuell);

    return forsta;
}

// d) Går igenom kedjan från början till slut och skriver ut alla värden
void skrivLista(struct node *forsta) {
    struct node *aktuell = forsta;
    int plats = 1;

    if (forsta == NULL) {
        printf("Kedjan är tom.\n");
        return;
    }

    // Vanligt mönster för att gå igenom en länkad lista:
    // börja på första noden och hoppa till next tills vi hamnar på NULL.
    while (aktuell != NULL) {
        printf("Plats %d: %.2f\n", plats, aktuell->data);
        aktuell = aktuell->next;
        plats++;
    }
}

// Frigör alla noder. Vi måste spara next INNAN free,
// för efter free får vi inte längre läsa något ur noden.
void friaLista(struct node *forsta) {
    struct node *aktuell = forsta;
    struct node *nasta;

    while (aktuell != NULL) {
        nasta = aktuell->next;
        free(aktuell);
        aktuell = nasta;
    }
}

// Läser in ett decimaltal. Returnerar 1 om det gick bra, annars 0.
int lasTal(double *tal) {
    int c;

    printf("Vilket tal? ");

    // tal är redan en pekare (adress), så här behövs inget & framför
    if (scanf("%lf", tal) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);    // töm raden
        printf("Felaktig inmatning.\n");
        return 0;
    }
    return 1;
}

void oneSixOne(void) {
    struct node *forsta = NULL;     // NULL betyder att kedjan är tom
    int choice = 0;
    int plats;
    double tal;
    int c;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    while (choice != 5) {
        printf("\n1) Skapa ny kedja med en ensam nod\n");
        printf("2) Lägg till en nod sist\n");
        printf("3) Ta bort nod på en viss plats\n");
        printf("4) Skriv ut alla värden\n");
        printf("5) Avsluta programmet\n\n");
        printf("> ");

        // Om inmatningen inte är ett heltal töms raden och menyn visas igen
        if (scanf("%d", &choice) != 1) {
            while ((c = getchar()) != '\n' && c != EOF);
            choice = 0;
        }

        switch (choice) {
            case 1:
                if (lasTal(&tal)) {
                    // Finns det redan en kedja frigörs den först,
                    // annars skulle de gamla noderna bli kvar i minnet (minnesläcka)
                    friaLista(forsta);
                    forsta = skapaNod(tal);
                    printf("Ny kedja skapad.\n");
                }
                break;

            case 2:
                if (lasTal(&tal)) {
                    forsta = laggTillSist(forsta, tal);
                }
                break;

            case 3:
                printf("Vilken plats? ");
                if (scanf("%d", &plats) != 1) {
                    while ((c = getchar()) != '\n' && c != EOF);
                    printf("Felaktig inmatning.\n");
                } else {
                    forsta = taBortNod(forsta, plats);
                }
                break;

            case 4:
                skrivLista(forsta);
                break;

            case 5:
                printf("Programmet avslutas.\n");
                break;

            default:
                printf("Ogiltigt val, välj 1-5.\n");
                break;
        }
    }

    // Alla noder skapades med malloc, så alla måste lämnas tillbaka med free
    friaLista(forsta);
    printf("Minnet för alla noder är frigjort.\n");
}

int main(void) {
    oneSixOne();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 1.6.1.c -o oneSixOne
#endif
