#include <stdio.h>
#include <windows.h>


// 1.5.1 --------------------------------------------------------------
void oneFiveOne() {
    int number = 10;
    int *numberpointer = &number;

    //&number   → "where is number?"
    //*numberpointer   → "what is stored where numberpointer points?"
    
    printf("%i\n", numberpointer + 1);      // 6422284
    printf("%i\n", number+1);               // 11
    printf("%i\n", *(&number)+1);           // 11
    printf("%i\n", *(numberpointer + 1));   // 6422284
    printf("%i\n", *numberpointer + 1);     // 11
    printf("%i\n", &number + 1);            // 6422284
}

// 1.5.11 --------------------------------------------------------------
char *SafeCopyString(char *dest, const char *origin, size_t count)
{
    size_t length = 0;
    size_t copied;
    size_t i;
    int backwards = 0;
    int truncated;

    if (dest == NULL || origin == NULL || count == 0) {
        errno = EINVAL;
        return NULL;
    }

    /* Sök efter nolltecknet inom läsgränsen. */
    while (length < count && origin[length] != '\0') {
        ++length;
    }

    truncated = (length == count);
    copied = truncated ? count - 1 : length;

    /* Kontrollera om överlapp kräver kopiering baklänges. */
    for (i = 1; i < copied; ++i) {
        if (dest == origin + i) {
            backwards = 1;
            break;
        }
    }

    if (backwards) {
        for (i = copied; i > 0; --i) {
            dest[i - 1] = origin[i - 1];
        }
    } else {
        for (i = 0; i < copied; ++i) {
            dest[i] = origin[i];
        }
    }

    dest[copied] = '\0';
    errno = truncated ? ERANGE : 0;

    return dest;
}

#if 0
gcc -Wall -Wextra -std=c11 1.5.c -o oneFive
#endif