#include "input.h"

#include <stdio.h>
#include <stdlib.h>

#include "errType.h"

ErrTypes input(char **exp) {
    size_t lenStr = 0;
    size_t lenBuf = 8;

    *exp = malloc(sizeof(char) * lenBuf);
    if (*exp == NULL) return MEM_INPUT_ERR;

    int ch;
    char *tmp;

    while ((ch = getc(stdin)) != '\n' && ch != EOF) {
        if (lenBuf == lenStr) {
            lenBuf *= 2;
            tmp = realloc(*exp, lenBuf * sizeof(char));
            if (tmp == NULL) {
                free(*exp);
                return MEM_INPUT_ERR;
            }
            *exp = tmp;
        }
        (*exp)[lenStr++] = (char)ch;
    }

    if (lenBuf == lenStr) {
        tmp = realloc(*exp, (lenStr + 1) * sizeof(char));
        if (tmp == NULL) {
            free(*exp);
            return MEM_INPUT_ERR;
        }
        *exp = tmp;
    }
    (*exp)[lenStr] = '\0';
    return OK;
}
