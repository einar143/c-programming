// Nedan följer Einar Bergvikens lösningar för delkapitel 1.2

#include <stdio.h>
#include <windows.h>

// 1.2.1 --------------------------------------------------------------
/* Skriv ett program som läser in ett heltal, multiplicerar det med två och beräknar hur många siffror
resultatet har. Om användaren matar in felaktig data (dvs, inte ett heltal) skall programmet skriva ut
ett meddelande och avslutas. Tips: använd funktionen scanf */

void oneTwoOne() {
    double number; // tidigare  <int number;>

    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    printf("Mata in ett heltal: ");

    if (scanf("%lf", &number) != 1 || number != (int)number) { // tidigare var inte andra conditioner med
        printf("Felaktig inmatning. Programmet avslutas.\n");
        return;
    }
    int result = number * 2; 
    int digitCount = 0;
    int temp = result;
    if (temp == 0) {
        digitCount = 1; // Hantera fallet när resultatet är 0
    } else {
        while (temp != 0) {
            temp /= 10;
            digitCount++;
        }
    }
    printf("Resultatet av %d * 2 är %d och det har %d siffror.\n",
       (int)number, result, digitCount);
    }

// 1.2.2 --------------------------------------------------------------
/*
Skriv ett program som läser in två heltal, låt oss kalla dem P och Q. Använd funktionen printf för
att producera följande utskrifter från programmet:
• Talet P på hexadecimal form,
• Talet P/Q på flyttalsform med exakt 3 decimaler,
• Talet P%Q på heltalsform
• Talet Q*P på tiopotensform (”scientific notation”),
• Talet Q med nollpadding till totalt 9 siffror (ex: 747 skrivs 000000747) 
*/

void oneTwoTwo() {
    int P;
    int Q;

    printf("Mata in P: ");
    scanf("%d", &P);

    printf("Mata in Q: ");
    scanf("%d", &Q);

    printf("P i hexadecimal form: %x\n", P);
    printf("P/Q med 3 decimaler: %.3f\n", (double)P / Q);
    printf("P %% Q: %d\n", P % Q);
    printf("Q * P i tiopotensform: %e\n", (double)Q * P);
    printf("Q med nollpadding: %09d\n", Q);
}


int main(void) { // Körning av funktioner för delkapitel 1.2
    // oneTwoOne();
    oneTwoTwo();
    return 0;
}


// gcc -Wall -Wextra -std=c11