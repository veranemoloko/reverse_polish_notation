#include "validate.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isOperator(char ch) {
    char operators[4] = {'+', '-', '*', '/'};
    for (size_t i = 0; i < 4; i++) {
        if (ch == operators[i]) return 1;
    }
    return 0;
}

int is_valid_dot_double(size_t *i, const char *exp) {
    int dot_cnt = 0;
    while (isdigit(exp[*i]) || exp[*i] == '.') {
        if (exp[*i] == '.') dot_cnt++;
        if (dot_cnt > 1) return 1;
        (*i)++;
    }
    (*i)--;
    return 0;
}

int is_valid_func(size_t *i, const char *exp) {
    char buf_name_func[5];
    int j = 0;
    while (isalpha(exp[*i])) buf_name_func[j++] = exp[(*i)++];
    buf_name_func[j] = '\0';
    char *name_func[6] = {"sin", "cos", "tg", "ctg", "ln", "sqrt"};
    for (size_t f = 0; f < 6; f++) {
        if (!strcmp(buf_name_func, name_func[f]) && exp[(*i)--] == '(') return 0;
    }
    return 1;
}

int parens_balance(int *balance, char ch) {
    if (ch == '(') {
        (*balance)++;
    } else if (ch == ')')
        (*balance)--;
    if (*balance < 0) return 1;
    return 0;
}

int isValidExp(const char *exp) {
    int balance_pars = 0;
    size_t len = strlen(exp);

    for (size_t i = 0; i < len; i++) {
        if (exp[i] == '(' || exp[i] == ')') {
            if (parens_balance(&balance_pars, exp[i])) return 1;
            continue;
        } else if (exp[i] == 'x' || exp[i] == ' ')
            continue;
        else if (isOperator(exp[i]))
            continue;
        else if (isalpha(exp[i])) {
            if (is_valid_func(&i, exp)) return 1;
            continue;
        } else if (isdigit(exp[i])) {
            if (is_valid_dot_double(&i, exp)) return 1;
            continue;
        } else if (exp[i] == '.')
            return 1;
        else
            return 1;
    }
    if (balance_pars != 0) return 1;
    return 0;
}
