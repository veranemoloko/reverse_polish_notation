#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdlib.h>

#include "errType.h"

typedef enum {
    X,
    NUMBER,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    FN_SIN,
    FN_COS,
    FN_TG,
    FN_CTG,
    FN_SQRT,
    FN_LN,
    FN_NEG,
    L_PAREN,
    R_PAREN
} MathToken;

typedef struct {
    MathToken *data;
    size_t length;
    size_t capacity;
} Tokens;

Tokens tokensNew();
ErrTypes tokensAdd(Tokens *, MathToken);

#endif