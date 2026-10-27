#ifndef ISORT_H
#define ISORT_H

// size_t finns i stddef.h
#include <stddef.h>

// Samma parametrar som qsort i stdlib.h, så isort kan användas på precis samma sätt
void isort(void *base, size_t nmemb, size_t size, int (*compare)(const void *, const void *));

#endif
