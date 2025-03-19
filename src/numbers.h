#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdlib.h>

#include "errType.h"

typedef struct {
    double *data;
    size_t length;
    size_t capacity;
} Numbers;

Numbers numbersNew();
double parsNumber(const char *, size_t);
ErrTypes numbersAdd(Numbers *, double);

#endif