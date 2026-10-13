#include <stdio.h>
#include <windows.h>
#include <math.h>

// 1.6.2 --------------------------------------------------------------

struct node {
    int data;
    struct node *parent;
    struct node *left;
    struct node *right;
};


#if 0
gcc -Wall -Wextra -std=c11 1.6.c -o oneSix
#endif