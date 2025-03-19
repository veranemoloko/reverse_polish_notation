#include "draw.h"

#include <math.h>
#include <stdio.h>
#define M_PI 3.14159265358979323846

#include "calculate.h"
#include "errType.h"
#include "units.h"

#define WIDHT 80
#define HIGHT 25

#define MAX_X (4.0 * M_PI)
#define MIN_X 0.0
#define MAX_Y 1.0
#define MIN_Y (-1.0)

void printGraph(char fieldGraph[][WIDHT]) {
    for (int j = 0; j < WIDHT; j++) {
        if (j == WIDHT - 1)
            printf(">");
        else
            printf("-");
    }
    printf(" X = [%.2lf : %.2lf]\n", MIN_X, MAX_X);

    for (int i = 0; i < HIGHT; i++) {
        if (i == HIGHT / 2)
            printf("0");
        else if (i == HIGHT - 1)
            printf("V");
        else
            printf("|");
        for (int j = 0; j < WIDHT; j++) {
            if (fieldGraph[i][j] == '*')
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
    printf(" Y = [%.2lf : %.2lf]\n", MIN_Y, MAX_Y);
}

ErrTypes draw(const Units polishNotation, const char *exp) {
    int err = 0;
    char fieldGraph[HIGHT][WIDHT] = {0};
    for (int i = 0; i < WIDHT; i++) {
        double x = ((double)MAX_X / ((double)WIDHT - 1)) * ((double)i);
        double y;
        err = polishCalculate(polishNotation, x, &y);
        if (err) return err;
        if (y <= MAX_Y && y >= MIN_Y) {
            int j = (int)round((MAX_Y - y) / (MAX_Y - MIN_Y) * (HIGHT - 1));
            j = j >= HIGHT ? HIGHT - 1 : j;
            fieldGraph[j][i] = '*';
        }
    }
    printGraph(fieldGraph);
    printf("Math expression: y = %s\n", exp);
    return OK;
}
