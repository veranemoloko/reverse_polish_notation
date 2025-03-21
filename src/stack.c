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

void popStack(MathToken *outStack, size_t *outCnt, MathToken *opStack, size_t *operCnt) {
    if (opStack[*operCnt] == L_PAREN) return;
    while (opStack[*operCnt] != L_PAREN) {
        outStack[(*outCnt)++] = opStack[(*operCnt)--];
    }
}

void pushStack(MathToken *outStack, size_t *outCnt, MathToken *opStack, size_t *operCnt, MathToken token) {
    int resComp = comPriority(token, opStack[(*operCnt) - 1]);
    if (resComp <= 0) {
        outStack[(*outCnt)++] = opStack[(*operCnt) - 1];
        opStack[(*operCnt) - 1] = token;
    } else {
        opStack[(*operCnt)++] = token;
    }
}

ErrTypes algDijkstra(Tokens *tokens) {
    size_t outCnt = 0;
    MathToken *outStack = malloc(sizeof(MathToken) * tokens->length);
    if (outStack == NULL) return MEM_ALG_ERR;

    size_t operCnt = 0;
    MathToken *operStack = malloc(sizeof(MathToken) * tokens->length);
    if (operStack == NULL) {
        free(outStack);
        return MEM_ALG_ERR;
    }

    for (size_t i = 0; i < tokens->length; i++) {
        if (tokens->data[i] == X) {
            outStack[outCnt++] = X;
        } else if (tokens->data[i] == NUMBER) {
            outStack[outCnt++] = NUMBER;
        } else if (tokens->data[i] == L_PAREN) {
            operStack[operCnt++] = L_PAREN;
        } else if (tokens->data[i] == R_PAREN) {
            operCnt--;
            popStack(outStack, &outCnt, operStack, &operCnt);
        } else {
            if (operCnt > 0) {
                if (operStack[operCnt - 1] == L_PAREN) {
                    operStack[operCnt++] = tokens->data[i];
                    continue;
                }
                pushStack(outStack, &outCnt, operStack, &operCnt, tokens->data[i]);
                continue;
            }
            operStack[operCnt++] = tokens->data[i];
        }
    }

    if (operCnt > 0) {
        for (size_t i = operCnt; i > 0; i--) {
            outStack[outCnt++] = operStack[i - 1];
        }
    }

    for (size_t i = 0; i < outCnt; i++) {
        tokens->data[i] = outStack[i];
    }
    tokens->length = outCnt;

    free(operStack);
    free(outStack);

    return OK;
}
