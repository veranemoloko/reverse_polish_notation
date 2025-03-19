#ifndef MEM_H
#define MEM_H

#define STACK_PUSH(stack, ItemType, item, pushed)                               \
    do {                                                                        \
        if (stack->data == NULL) {                                              \
            size_t capacity = 8;                                                \
            stack->data = malloc(capacity * sizeof(ItemType));                  \
            if (stack->data != NULL) {                                          \
                stack->capacity = capacity;                                     \
            } else                                                              \
                *pushed = false;                                                \
        } else if (stack->capacity == stack->length) {                          \
            size_t capacity = stack->capacity * 2;                              \
            ItemType *temp = realloc(stack->data, capacity * sizeof(ItemType)); \
            if (temp != NULL) {                                                 \
                stack->data = temp;                                             \
                stack->capacity = capacity;                                     \
            } else                                                              \
                *pushed = false;                                                \
        }                                                                       \
        if (*pushed) stack->data[stack->length++] = num;                        \
    } while (0);

#endif