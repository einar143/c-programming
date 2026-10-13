#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <limits.h>

// 1.3.1 --------------------------------------------------------------
/* Skriv ett program som skriver ut antalet bitar i en int på din dator. */

void oneThreeOne(void) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // sizeof ger storleken i byte och CHAR_BIT är antalet bitar i en byte
    int antalBitar = sizeof(int) * CHAR_BIT;

    printf("En int är %d byte, alltså %d bitar på den här datorn.\n", (int)sizeof(int), antalBitar);
}

// 1.3.2 --------------------------------------------------------------
/*
int a=1, b=2, c=3;      (8 bitar)

a  = 0000 0001
b  = 0000 0010
c  = 0000 0011
~b = 1111 1101
~c = 1111 1100

Ordningen operatorerna beräknas i:  ~  sen  &  sen  ^  sen  |  sen  &&

a) a & ~b & ~c
   a & ~b       = 0000 0001 & 1111 1101 = 0000 0001
   ... & ~c     = 0000 0001 & 1111 1100 = 0000 0000
   Svar: 0

b) a & ~b & c
   a & ~b       = 0000 0001
   ... & c      = 0000 0001 & 0000 0011 = 0000 0001
   Svar: 1

c) a && ~b & c
   & beräknas före &&
   ~b & c       = 1111 1101 & 0000 0011 = 0000 0001
   a && 1       = sant && sant = 1
   Svar: 1

d) a ^ b & c
   & beräknas före ^
   b & c        = 0000 0010 & 0000 0011 = 0000 0010
   a ^ ...      = 0000 0001 ^ 0000 0010 = 0000 0011
   Svar: 3

e) a & b ^ ~c
   a & b        = 0000 0001 & 0000 0010 = 0000 0000
   ... ^ ~c     = 0000 0000 ^ 1111 1100 = 1111 1100
   Svar: -4 (tvåkomplement, 252 om talet är teckenlöst)

f) a | b & c
   & beräknas före |
   b & c        = 0000 0010
   a | ...      = 0000 0001 | 0000 0010 = 0000 0011
   Svar: 3
*/

// 1.3.3 --------------------------------------------------------------
/*
int a = (!(1==0)+(0==1)*1)+(1||1&&0)+(!1+1);

Första parentesen: (!(1==0)+(0==1)*1)
   (1==0) = 0
   !0     = 1
   (0==1) = 0
   0*1    = 0       * beräknas före +
   1 + 0  = 1

Andra parentesen: (1||1&&0)
   1&&0   = 0       && beräknas före ||
   1||0   = 1

Tredje parentesen: (!1+1)
   !1     = 0       ! beräknas före +
   0 + 1  = 1

a = 1 + 1 + 1 = 3
*/

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
    int prisOre     = (int)round(pris * 100);
    int betaltOre   = (int)round(betalt * 100);

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

// 1.3.6 --------------------------------------------------------------
/* Skriv ett program som beräknar och skriver ut (med lämplig formatering) resultat från funktionen:
f(x) = 4x^3 + 3sin^2(x) - 5x - 7
i) Samtliga heltal x [-15,15]
ii) Samtliga x [-1,1] med en upplösning i x på 0.1
*/

void oneThreeSix(void) {
    double x;
    double resultat;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // i) Alla heltal från -15 till 15
    printf("i) Heltal x från -15 till 15\n");
    printf("%6s %14s\n", "x", "f(x)");

    for (int i = -15; i <= 15; i++) {
        x = i;
        resultat = 4 * x * x * x + 3 * sin(x) * sin(x) - 5 * x - 7;
        printf("%6d %14.4f\n", i, resultat);
    }

    // ii) Från -1 till 1 med steg 0.1
    // Loopar över heltal och delar med 10 för att undvika flyttalsproblem
    printf("\nii) x från -1 till 1 med steg 0.1\n");
    printf("%6s %14s\n", "x", "f(x)");

    for (int i = -10; i <= 10; i++) {
        x = i / 10.0;
        resultat = 4 * x * x * x + 3 * sin(x) * sin(x) - 5 * x - 7;
        printf("%6.1f %14.4f\n", x, resultat);
    }
}

int main(void) {
    oneThreeOne();
    // oneThreeSix();
    // oneThreeFive();
    return 0;
}


#if 0
gcc -Wall -Wextra -std=c11 1.3.c -o oneThree
#endif