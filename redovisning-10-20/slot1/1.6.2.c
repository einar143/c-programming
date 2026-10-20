#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

// 1.6.2 --------------------------------------------------------------
/* Skriv ett program som skapar trädet i figuren. Skapa en funktion som givet en rot-nod
skriver ut trädet på något lämpligt sätt. Ditt program måste allokera noderna dynamiskt,
och frigöra minnet för dem efteråt.

Trädet i figuren:
          1
        /   \
       2     3
      / \   /
     4   5 6
*/

// Hur programmet tänker:
//
// Ett binärträd består av noder där varje nod har högst två barn, left och right.
// Noden högst upp (1) kallas roten. Noder utan barn (4, 5, 6) kallas löv.
// Varje nod vet också vem som är dess förälder (parent), så man kan gå uppåt.
//
// Precis som i 1.6.1 skapas noderna med malloc och kopplas ihop med pekare.
// Skillnaden är att en nod här pekar på två noder nedåt istället för en framåt.

struct node {
    int data;
    struct node *parent;    // noden ovanför, NULL för roten
    struct node *left;      // vänster barn, NULL om det inte finns
    struct node *right;     // höger barn, NULL om det inte finns
};

// Allokerar en ny nod med malloc. Noden har inga barn från början.
//
// malloc ger minne som lever kvar tills free anropas, därför kan noden
// användas efter att funktionen har returnerat. Vi returnerar adressen.
struct node *skapaNod(int data, struct node *parent) {
    struct node *nyNod = malloc(sizeof(struct node));

    if (nyNod == NULL) {
        printf("Kunde inte allokera minne.\n");
        exit(1);
    }

    // nyNod->data är samma sak som (*nyNod).data
    nyNod->data = data;
    nyNod->parent = parent;
    nyNod->left = NULL;
    nyNod->right = NULL;

    return nyNod;
}


void skrivTrad(struct node *rot, int niva) {
    // Basfallet: inget barn här, då finns det inget att skriva ut.
    // Utan det här skulle rekursionen aldrig sluta.
    if (rot == NULL) {
        return;
    }

    // Höger först, så att höger gren hamnar överst i utskriften
    skrivTrad(rot->right, niva + 1);

    // En nivå djupare i trädet ger fyra mellanslag till
    for (int i = 0; i < niva; i++) {
        printf("    ");
    }

    // Roten är den enda noden som saknar förälder
    if (rot->parent == NULL) {
        printf("%d (rot)\n", rot->data);
    } else {
        printf("%d (förälder %d)\n", rot->data, rot->parent->data);
    }

    skrivTrad(rot->left, niva + 1);
}

// Frigör barnen först och noden själv sist, annars tappar vi pekarna till barnen
//
// Om vi gjorde free(rot) först skulle rot->left och rot->right inte längre
// gå att läsa, och barnen skulle bli kvar i minnet utan att någon vet var
// de ligger (en minnesläcka).
void friaTrad(struct node *rot) {
    if (rot == NULL) {
        return;
    }

    friaTrad(rot->left);
    friaTrad(rot->right);
    free(rot);
}

void oneSixTwo(void) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Bygg trädet i figuren uppifrån och ner.
    // Andra argumentet är föräldern, så att varje nod vet vem den hänger under.
    struct node *rot = skapaNod(1, NULL);

    rot->left = skapaNod(2, rot);
    rot->right = skapaNod(3, rot);

    // rot->left är noden 2, så rot->left->left är 2:s vänstra barn
    rot->left->left = skapaNod(4, rot->left);
    rot->left->right = skapaNod(5, rot->left);

    rot->right->left = skapaNod(6, rot->right);

    skrivTrad(rot, 0);

    friaTrad(rot);
    printf("\nMinnet för alla noder är frigjort.\n");
}

int main(void) {
    oneSixTwo();
    return 0;
}


#if 0
gcc -Wall -Wextra -std=c11 1.6.2.c -o oneSixTwo
#endif
