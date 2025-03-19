#include "calculate.h"

#include <math.h>
#include <stdio.h>

#include "errType.h"
#include "mem.h"

double unaMinus(double num) { return -num; }
double ctg(double num) { return 1.0 / tan(num); }

double sumD(double a, double b) { return a + b; }
double subD(double a, double b) { return a - b; }
double mulD(double a, double b) { return a * b; }
double divD(double a, double b) { return a / b; }

ErrTypes calculateUnary(Numbers *numbers, double (*op)(double)) {
    if (numbers->length < 1) return CALC_VALID_ERR;
    numbers->data[numbers->length - 1] = op(numbers->data[numbers->length - 1]);
    return OK;
}
ErrTypes calculateBinary(Numbers *numbers, double (*op)(double, double)) {
    if (numbers->length < 2) return CALC_VALID_ERR;
    numbers->data[numbers->length - 2] =
        op(numbers->data[numbers->length - 2], numbers->data[numbers->length - 1]);
    numbers->length--;
    return OK;
}

ErrTypes polishCalculate(const Units units, double x, double *y) {
    Units resUnits = unitsNew();
    ErrTypes err = OK;
    size_t j = 0;
    for (size_t i = 0; i < units.tokens.length; i++) {
        switch (units.tokens.data[i]) {
            case NUMBER: {
                err = numbersAdd(&resUnits.numbers, units.numbers.data[j++]);
                if (err) return MEM_ERR;
                continue;
            }
            case X: {
                err = numbersAdd(&resUnits.numbers, x);
                if (err) return MEM_ERR;
                continue;
            }
            case OP_ADD:
                err = calculateBinary(&resUnits.numbers, sumD);
                break;
            case OP_SUB:
                err = calculateBinary(&resUnits.numbers, subD);
                break;
            case OP_MUL:
                err = calculateBinary(&resUnits.numbers, mulD);
                break;
            case OP_DIV:
                err = calculateBinary(&resUnits.numbers, divD);
                break;
            case FN_SIN:
                err = calculateUnary(&resUnits.numbers, sin);
                break;
            case FN_COS:
                err = calculateUnary(&resUnits.numbers, cos);
                break;
            case FN_TG:
                err = calculateUnary(&resUnits.numbers, tan);
                break;
            case FN_CTG:
                err = calculateUnary(&resUnits.numbers, ctg);
                break;
            case FN_LN:
                err = calculateUnary(&resUnits.numbers, log);
                break;
            case FN_SQRT:
                err = calculateUnary(&resUnits.numbers, sqrt);
                break;
            case FN_NEG:
                err = calculateUnary(&resUnits.numbers, unaMinus);
                break;
            case L_PAREN:
                break;
            case R_PAREN:
                break;
        }
        if (err) return err;
    }
    if (resUnits.numbers.length != 1) return err;
    *y = resUnits.numbers.data[0];

    free(resUnits.numbers.data);
    free(resUnits.tokens.data);

    return 0;
}
