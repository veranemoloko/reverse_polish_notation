#include "units.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errType.h"
#include "numbers.h"
#include "stack.h"
#include "tokens.h"
#include "validate.h"

Units unitsNew() {
    Units unit;
    unit.tokens = tokensNew();
    unit.numbers = numbersNew();
    return unit;
}

ErrTypes unitsInit(char *exp, Units *units) {
    int err = isValidExp(exp);
    if (err) return err;
    err = tokenize(exp, &units->tokens, &units->numbers);
    if (err) return err;
    return OK;
}

ErrTypes tokenize(const char *exp, Tokens *tokens, Numbers *numbers) {
    ErrTypes err = OK;

    for (size_t i = 0; i < strlen(exp); i++) {
        if (isspace(exp[i])) continue;

        if (exp[i] == '-' && (i == 0 || exp[i - 1] == '(' || isOperator(exp[i - 1]))) {
            err = tokensAdd(tokens, FN_NEG);
            continue;
        }

        switch (exp[i]) {
            case 'x':
                err = tokensAdd(tokens, X);
                break;
            case '+':
                err = tokensAdd(tokens, OP_ADD);
                break;
            case '/':
                err = tokensAdd(tokens, OP_DIV);
                break;
            case '*':
                err = tokensAdd(tokens, OP_MUL);
                break;
            case '-':
                err = tokensAdd(tokens, OP_SUB);
                break;
            case '(':
                err = tokensAdd(tokens, L_PAREN);
                break;
            case ')':
                err = tokensAdd(tokens, R_PAREN);
                break;
            case 'l':
                err = tokensAdd(tokens, FN_LN);
                i++;
                break;
            case 't':
                err = tokensAdd(tokens, FN_TG);
                break;
            case 's': {
                if (exp[i + 1] == 'i') {
                    err = tokensAdd(tokens, FN_SIN);
                    i += 2;
                } else {
                    err = tokensAdd(tokens, FN_SQRT);
                    i += 3;
                }
            } break;
            case 'c': {
                if (exp[i + 1] == 'o')
                    err = tokensAdd(tokens, FN_COS);
                else
                    err = tokensAdd(tokens, FN_CTG);
                i += 2;
            }
        }
        if (isdigit(exp[i])) {
            size_t start = i;
            err = tokensAdd(tokens, NUMBER);
            if (err) return MEM_TOKENS_ADD_ERR;

            while (isdigit(exp[i]) || exp[i] == '.') i++;
            i--;

            double num = parsNumber(exp, start);
            if (num < 0) return VALID_NUMBERS_ERR;
            err = numbersAdd(numbers, num);
            if (err) return MEM_NUMBERS_ADD_ERR;
        }
        if (err) return MEM_TOKENS_ADD_ERR;
    }
    return OK;
}