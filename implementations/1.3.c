#include <stdio.h>
#include <windows.h>
#include <math.h>

void oneThreeFive(void) {
    double pris;
    double betalt;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);


    // Läs in pris och betalt belopp
    printf("Hur mycket kostar varan? ");
    scanf("%lf", &pris);

    printf("Hur mycket har kunden betalat? ");
    scanf("%lf", &betalt);

    // Handera ogiltiga belopp och situationer
    if (betalt < pris) { 
        printf("Kunden har betalat for lite :( \n"); 
        return;
    } else if (pris < 0 || betalt < 0) {
        printf("Ogiltigt belopp.\n");
        return;
    } else if (betalt == pris) {
        printf("Ingen växel att ge tillbaka :) \n");
        return;
    } else if (betalt > 10000) {
        printf("Kunden har betalat för mycket, maxbelopp är 10000 kr.\n");
        return;
    } else if (pris > 10000) {
        printf("Priset är för högt, maxbelopp är 10000 kr.\n");
        return; }
//    } else {            // Behövs detta vid %lf och scanf? 
//        printf("Felaktig inmatning.\n");
//        return;
//    }

    // Konvertera belopp till ören för att undvika flyttalsproblem
    int prisOre = (int)round(pris * 100);
    int betaltOre = (int)round(betalt * 100);

    // Beräkna växel
    int vaxel = betaltOre - prisOre;

    // Avrunda tillbaka till närmaste 50 öre
    vaxel = ((vaxel + 25) / 50) * 50;
    printf("\nVäxel: %.2f kr\n\n", vaxel / 100.0);

    int valorer[] = {
        100000,
        50000,
        10000,
        5000,
        2000,
        1000,
        500,
        100,
        50
    };

    char *namn[] = {
        "1000 kr",
        "500 kr",
        "100 kr",
        "50 kr",
        "20 kr",
        "10 kr",
        "5 kr",
        "1 kr",
        "50 ore"
    };

    // Beräkna antalet sedlar och mynt för varje valör
    int antalValor = sizeof(valorer) / sizeof(valorer[0]); 

    for (int i = 0; i < antalValor; i++) {
        int antal = vaxel / valorer[i];

        if (antal > 0) {
            printf("%s: %d\n", namn[i], antal);
        }

        vaxel = vaxel - antal * valorer[i];
        // vaxel = vaxel - (vaxel / valorer[i]) * valorer[i];
        // 
    }
}

int main(void) { 
    oneThreeFive();
    return 0;
}


#if 0
gcc -Wall -Wextra -std=c11 1.3.c -o oneThree
#endif