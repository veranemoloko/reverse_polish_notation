#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

#include "errType.h"
#include "units.h"

int pushTokens(int *, MathToken);
int comPriority(MathToken, MathToken);
ErrTypes algDijkstra(Tokens *);

#endif