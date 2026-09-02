// Nedan följer Einar Bergvikens lösningar för delkapitel 1.1

#include <stdio.h>
#include <windows.h>

// 1.1.1 
// a)
void oneOneOne() {
    int number1 = 5;
    int number2 = 10;
    int result = number1*number2;
    printf("Låt oss göra lite matte\n");
    printf("%d",&result);
}

// b)
/*
- Preprocessor är steget som processerar filen och gör saker för att förbereda innan kompilering.
Saker som t.ex att ta bort kommentarer, fixar #include osv. 

- Kompilatorn är det steget som tar en en .c fil och översätter den till assemblerspråk.

- Länkare tar olika filer med binära instruktioner och länkar dem i den ordningen de ska utföras och skapar
en exekverbar fil
*/

// 1.1.2



int main(void) {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    printf("åäö\n");

    oneOneOne();
    return 0;
}