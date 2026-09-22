#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define KEY_ARROW_PREFIX_1  0
#define KEY_ARROW_PREFIX_2  224
#define KEY_UP              72
#define KEY_DOWN            80
#define KEY_ENTER           13


static const char *menuItems[] = { // Menyalternativ, går att ta bort här

    "Section 1.2 - Variabler, inläsning och utmatning",
    "Section 1.3 - Styruttryck, operatorer och satser",
    "Section 1.4 - Funktioner och funktionsprototyper",
    "Section 1.5 - Pekare och adresser",
    "Section 1.6 - Poster (structs)",
    "Section 2.1 - Standardfunktioner och filströmmar",
    "Section 3.1 - Statisk länkning",
    "Section 3.2 - Dynamisk länkning",
    "Avsluta programmet"
};

#define MENU_COUNT ((int)(sizeof(menuItems) / sizeof(menuItems[0])))

/* Visar vald sektion. Fyll i anropen till dina uppgifter under varje case. */
static void presentSection(int index)
{
    system("cls");
    printf("%s\n\n", menuItems[index]);

    switch (index) {
        case 0: /* 1.1 - t.ex. task_1_1_1(); */ break;
        case 1: 
            printf("test");
            break;
        default: break;
    }

    printf("\nTryck på valfri tangent för att återgå till menyn...");
    _getch();
}

/* Huvudmeny: piltangenter flyttar markören, Enter väljer. */
void sectionChooser(void)
{
    int choice = 0;     // index i menyn
    int running = 1;    // loopen slutar köras när noll
    int key;            // matched against defined values of KEY_xx

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    while (running) {
        system("cls");
        printf("Välkommen till ultra-presenter version 1\n");
        printf("Vänligen välj en funktion att presentera:\n\n");

        for (int i = 0; i < MENU_COUNT; i++) {
            printf("%s %s\n", (i == choice) ? ">" : " ", menuItems[i]);
        }

        key = _getch();

        if (key == KEY_ARROW_PREFIX_1 || key == KEY_ARROW_PREFIX_2) {
            key = _getch();
            if (key == KEY_UP) {
                choice = (choice - 1 + MENU_COUNT) % MENU_COUNT; // Modulo runt antal menyalternativ

            } else if (key == KEY_DOWN) {
                choice = (choice + 1) % MENU_COUNT;  // Samma princip men uppåt Wrap-around
            }

        } else if (key == KEY_ENTER) { // Bryt loop om enter klickas       
            if (choice == MENU_COUNT - 1) {
                printf("\nProgrammet avslutas.\n");
                running = 0;
            } else {
                presentSection(choice);
            }
        }
    }
}

int main(void)
{
    sectionChooser();
    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 present.c -o present.exe
#endif