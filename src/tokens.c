#include "tokens.h"

#include "errType.h"
#include "mem.h"
#include "stdbool.h"

Tokens tokensNew() {
    Tokens tokens;
    tokens.data = NULL;
    tokens.capacity = 0;
    tokens.length = 0;
    return tokens;
}

ErrTypes tokensAdd(Tokens *tokens, MathToken num) {
    bool pushed = true;
    STACK_PUSH(tokens, MathToken, num, &pushed);
    return pushed ? OK : MEM_TOKENS_ADD_ERR;
}
