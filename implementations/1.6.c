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

struct node {
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
};

// Allokerar en ny nod med malloc. Noden har inga barn från början.
struct node *skapaNod(int data, struct node *parent) {
    struct node *nyNod = malloc(sizeof(struct node));

    if (nyNod == NULL) {
        printf("Kunde inte allokera minne.\n");
        exit(1);
    }

    nyNod->data = data;
    nyNod->parent = parent;
    nyNod->left = NULL;
    nyNod->right = NULL;

    return nyNod;
}

// Skriver ut trädet liggande, med roten längst till vänster och höger gren överst.
// Funktionen anropar sig själv för höger och vänster barn (rekursion).
void skrivTrad(struct node *rot, int niva) {
    if (rot == NULL) {
        return;
    }

    skrivTrad(rot->right, niva + 1);

    // En nivå djupare i trädet ger fyra mellanslag till
    for (int i = 0; i < niva; i++) {
        printf("    ");
    }

    if (rot->parent == NULL) {
        printf("%d (rot)\n", rot->data);
    } else {
        printf("%d (förälder %d)\n", rot->data, rot->parent->data);
    }

    skrivTrad(rot->left, niva + 1);
}

// Frigör barnen först och noden själv sist, annars tappar vi pekarna till barnen
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

    // Bygg trädet i figuren uppifrån och ner
    struct node *rot = skapaNod(1, NULL);

    rot->left = skapaNod(2, rot);
    rot->right = skapaNod(3, rot);

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
gcc -Wall -Wextra -std=c11 1.6.c -o oneSix
#endif