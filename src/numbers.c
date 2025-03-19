#include "numbers.h"

#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "errType.h"
#include "mem.h"
#include "units.h"

Numbers numbersNew() {
    Numbers numbers;
    numbers.data = NULL;
    numbers.capacity = 0;
    numbers.length = 0;
    return numbers;
}

double parsNumber(const char *exp, size_t i) {
    double num;
    char *endptr;
    errno = 0;
    num = strtod(exp + i, &endptr);
    if (errno == ERANGE || !isfinite(num)) {
        return -1.0;
    }
    return num;
}

ErrTypes numbersAdd(Numbers *numbers, double num) {
    bool pushed = true;
    STACK_PUSH(numbers, double, num, &pushed);
    return pushed ? OK : MEM_ERR;
}
