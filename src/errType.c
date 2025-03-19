#include "errType.h"

#include <stdio.h>

void printErr(ErrTypes errEnum) {
    switch (errEnum) {
        case MEM_ERR:
            printf("Err memory allocate\n");
            break;
        case MEM_INPUT_ERR:
            printf("----Err memory allocate in Input function----\n");
            break;
        case MEM_ALG_ERR:
            printf("----Err memory allocate in algoritm Dijkstra function----\n");
            break;
        case MEM_TOKENS_ADD_ERR:
            printf("----Err memory allocate in push stack tokens----\n");
            break;
        case MEM_NUMBERS_ADD_ERR:
            printf("----Err memory allocate in push stack numbers----\n");
            break;
        case VALID_ERR:
            printf("----Expression is't validate----\n");
            break;
        case VALID_NUMBERS_ERR:
            printf("----Numbers in expression is't validate----\n");
            break;
        case CALC_VALID_ERR:
            printf("----Expression is't validate for colapse stack----\n");
            break;
        case OK:
            break;
    }
}