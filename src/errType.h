#ifndef ERRTYPE_H
#define ERRTYPE_H

typedef enum {
    OK,
    MEM_ERR = 166,
    MEM_INPUT_ERR,
    MEM_ALG_ERR,
    MEM_TOKENS_ADD_ERR,
    MEM_NUMBERS_ADD_ERR,
    VALID_ERR,
    VALID_NUMBERS_ERR,
    CALC_VALID_ERR,
} ErrTypes;

void printErr(ErrTypes);

#endif