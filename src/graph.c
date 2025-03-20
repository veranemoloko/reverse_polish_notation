#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw.h"
#include "errType.h"
#include "input.h"
#include "stack.h"
#include "units.h"

int main() {
    Units units = unitsNew();
    char *exp = NULL;

    ErrTypes err = input(&exp);
    if (err) {
        printErr(err);
        exit(1);
    }

    err = unitsInit(exp, &units);
    if (err) {
        printErr(err);
        free(exp);
        exit(1);
    }

    err = algDijkstra(&units.tokens);
    if (err) {
        printErr(err);
        free(exp);
        exit(1);
    }

    err = draw(units, exp);
    if (err) {
        printErr(err);
        free(exp);
        exit(1);
    }

    free(units.numbers.data);
    free(units.tokens.data);
    free(exp);

    return 0;
}
