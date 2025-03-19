#ifndef UNITS_H
#define UNITS_H

#include "errType.h"
#include "numbers.h"
#include "tokens.h"

typedef struct {
    Tokens tokens;
    Numbers numbers;
} Units;

Units unitsNew();
ErrTypes unitsInit(char *, Units *);
ErrTypes tokenize(const char *, Tokens *, Numbers *);

#endif