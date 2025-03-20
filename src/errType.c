#include "errType.h"

#include <stdio.h>

void printErr(ErrTypes errEnum) {
    switch (errEnum) {
        case MEM_ERR:
            printf("Error: Memory allocation failed.\n");
            break;
        case MEM_INPUT_ERR:
            printf("Error: Memory allocation failed in the input function.\n");
            break;
        case MEM_ALG_ERR:
            printf("Error: Memory allocation failed in the Dijkstra algorithm function.\n");
            break;
        case MEM_TOKENS_ADD_ERR:
            printf("Error: Memory allocation failed while pushing tokens to the stack.\n");
            break;
        case MEM_NUMBERS_ADD_ERR:
            printf("Error: Memory allocation failed while pushing numbers to the stack.\n");
            break;
        case VALID_ERR:
            printf("Error: The expression is invalid.\n");
            break;
        case VALID_NUMBERS_ERR:
            printf("Error: Invalid numbers in the expression.\n");
            break;
        case CALC_VALID_ERR:
            printf("Error: The expression is invalid for stack evaluation.\n");
            break;
        case OK:
            break;
    }
}