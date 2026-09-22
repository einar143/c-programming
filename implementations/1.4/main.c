#include <stdio.h>
#include "convert.h"

int main(void)
{
    double meter;

    printf("Ange avstand i meter: ");
    scanf("%lf", &meter);

    printf("%.2f m = %.2f mm\n", meter, metersToMillimeters(meter));

    return 0;
}

#if 0
gcc -Wall -Wextra -std=c11 main.c convert.c -o convert
gcc -Wall main.c convert.c -o convert
#endif