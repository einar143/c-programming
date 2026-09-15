// Nedan följer Einar Bergvikens lösningar för delkapitel 1.3

#include <stdio.h>
#include <windows.h>
#include <conio.h>

// 1.3.4 --------------------------------------------------------------
/* Skriv ett program som låter användaren manipulera ett heltal genom en meny. Talet är från början
lika med 0, och användaren erbjuds följande val i en meny:
1) Addera 1
2) Multiplicera med 2
3) Subtrahera 3
4) Avsluta programmet
Vid val 1-3 utförs operationen, och användaren kommer tillbaka till menyn. Vid val 4 avslutas
programmet. Om användaren matar in något annat så skall programmet hantera det på något
lämpligt vis. Tips: använd en case-sats för användarens val i menyn, och en while-sats för att
repetera programmet tills användaren väljer att avsluta. 
*/

void oneThreeFour() {
    int number = 0;
    int end = 0;
    int choice = 1;
    int consoleOption;

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    while (end == 0) {
        while (1) {
            system("cls");

            printf("Talet är nu %d, välj en operation med piltangenterna:\n\n",number);
            switch (choice) {
                case 1:
                    printf("> 1) Addera 1\n");
                    printf("  2) Multiplicera med 2\n");
                    printf("  3) Subtrahera 3\n");
                    printf("  4) Avsluta programmet\n");
                    break;

                case 2:
                    printf("  1) Addera 1\n");
                    printf("> 2) Multiplicera med 2\n");
                    printf("  3) Subtrahera 3\n");
                    printf("  4) Avsluta programmet\n");
                    break;

                case 3:
                    printf("  1) Addera 1\n");
                    printf("  2) Multiplicera med 2\n");
                    printf("> 3) Subtrahera 3\n");
                    printf("  4) Avsluta programmet\n");
                    break;

                case 4:
                    printf("  1) Addera 1\n");
                    printf("  2) Multiplicera med 2\n");
                    printf("  3) Subtrahera 3\n");
                    printf("> 4) Avsluta programmet\n");
                    break;
            }
            consoleOption = _getch();
            if (consoleOption == 0 || consoleOption == 224) {
                consoleOption = _getch();

                if (consoleOption == 72) { // Uppåtpil
                    /*    choice = (choice + 2) % 4 + 1; // Modulo solution*/
                    choice--;
                    if (choice < 1) { //
                        choice = 4;
                    }
                }

                else if (consoleOption == 80) { // Nedåtpil
                    /*    choice = choice % 4 + 1; // Modulo uppgradering för negativa tal?*/
                    choice++;
                    if (choice > 4) {
                        choice = 1;
                    }
                }
            }

            else if (consoleOption == 13) { // Enter
                break;
            }
        }

        switch (choice) {
            case 1:
                number += 1;
                break;

            case 2:
                number *= 2;
                break;

            case 3:
                number -= 3;
                break;

            case 4:
                printf("\nProgrammet avslutas.\n");
                end = 1;
                break;
        }
    }
}


// 1.3.5 --------------------------------------------------------------
/* När du handlar i en affär och betalar kontant får du kanske växel tillbaka. I regel får affärsbiträdet
hjälp av kassaapparaten med att beräkna summan man ska få tillbaka, men inte alltid vilka sedlar
och mynt som ska lämnas tillbaka. Skriv ett program som beräknar den växel biträdet ska ge
tillbaka i samband med ett köp. 

Programmet ska, förutom att presentera beloppet kunden får
tillbaka avrundat till närmsta 50-öring, även bestämma vilka, och antalet, sedlar och mynt. Kunden
ska få så få sedlar och mynt som möjligt tillbaka. Programmet ska kunna ge växel tillbaka med
sedlar av valörerna 1000, 500, 100, 50 och 20 samt mynten 10, 5, 1 och 50-öring. Du kan anta att
det alltid finns tillräckligt antal av de sedlar och mynt som krävs. */

void oneThreeFive() {
    int number;
}



int main(void) { // Körning av funktioner för delkapitel 1.2
    oneThreeFour();
    // oneThreeFive();
    return 0;
}