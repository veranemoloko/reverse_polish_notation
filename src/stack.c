#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

int getPriority(MathToken token) {
    if (token == OP_ADD || token == OP_SUB)
        return 1;
    else if (token == OP_MUL || token == OP_DIV)
        return 2;
    return 3;
}

int comPriority(MathToken a, MathToken b) {
    a = getPriority(a);
    b = getPriority(b);
    return a - b;
}

void popStack(MathToken *outStack, size_t *outCnt, MathToken *opStack, size_t *opCnt) {
    if (opStack[*opCnt] == L_PAREN) return;
    while (opStack[*opCnt] != L_PAREN) {
        outStack[(*outCnt)++] = opStack[(*opCnt)--];
    }
}

void pushStack(MathToken *outStack, size_t *outCnt, MathToken *opStack, size_t *opCnt, MathToken token) {
    int resComp = comPriority(token, opStack[(*opCnt) - 1]);
    if (resComp <= 0) {
        outStack[(*outCnt)++] = opStack[(*opCnt) - 1];
        opStack[(*opCnt) - 1] = token;
    } else {
        opStack[(*opCnt)++] = token;
    }
}

ErrTypes algDijkstra(Tokens *tokens) {
    size_t outCnt = 0;
    MathToken *outStack = malloc(sizeof(MathToken) * tokens->length);
    if (outStack == NULL) return MEM_ALG_ERR;

    size_t opCnt = 0;
    MathToken *operStack = malloc(sizeof(MathToken) * tokens->length);
    free(outStack);
    if (operStack == NULL) return MEM_ALG_ERR;

    for (size_t i = 0; i < tokens->length; i++) {
        if (tokens->data[i] == X) {
            outStack[outCnt++] = X;
        } else if (tokens->data[i] == NUMBER) {
            outStack[outCnt++] = NUMBER;
        } else if (tokens->data[i] == L_PAREN) {
            operStack[opCnt++] = L_PAREN;
        } else if (tokens->data[i] == R_PAREN) {
            opCnt--;
            popStack(outStack, &outCnt, operStack, &opCnt);
        } else {
            if (opCnt > 0) {
                if (operStack[opCnt - 1] == L_PAREN) {
                    operStack[opCnt++] = tokens->data[i];
                    continue;
                }
                pushStack(outStack, &outCnt, operStack, &opCnt, tokens->data[i]);
                continue;
            }
            operStack[opCnt++] = tokens->data[i];
        }
    }
    if (opCnt > 0) {
        for (size_t i = opCnt; i > 0; i--) {
            outStack[outCnt++] = operStack[i - 1];
        }
        outStack[outCnt] = operStack[0];
    }

    for (size_t i = 0; i < outCnt; i++) {
        tokens->data[i] = outStack[i];
    }
    tokens->length = outCnt;

    free(operStack);
    free(outStack);

    return OK;
}
