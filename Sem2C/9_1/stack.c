#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

int stack_init(struct stack_t **stack, int N) {
    if (stack == NULL) return 1;
    if (N < 1)return 1;
    *stack = malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }
    (*stack)->capacity = N;
    (*stack)->data = malloc(N * sizeof(int));
    if ((*stack)->data == NULL) {
        free(*stack);
        *stack = NULL;
        return 2;
    }
    (*stack)->head = 0;
    return 0;
}

int stack_push(struct stack_t *stack, int value) {
    if (stack == NULL) return 1;
    if (stack->data == NULL) return 1;
    if (stack->head > stack->capacity) return 1;
    if (stack->head < 0) return 1;
    if (stack->capacity <= 0)return 1;
    if (stack->head == stack->capacity) {
        int *ptr = realloc(stack->data, sizeof(int) * stack->capacity * 2);
        if (ptr == NULL) {
            return 2;
        }
        stack->data = ptr;
        stack->capacity *= 2;
    }
    *(stack->data + stack->head) = value;
    stack->head++;
    return 0;
}

int stack_pop(struct stack_t *stack, int *err_code) {
    if (stack == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }
    if (stack->data == NULL) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }
    if (stack->head > stack->capacity) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }
    if (stack->head < 0) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }
    if (stack->capacity <= 0) {
        if (err_code != NULL) *err_code = 1;
        return 1;
    }
    if (stack->head == 0) {
        if (err_code != NULL) *err_code = 2;
        return 1;
    }
    if (err_code != NULL) *err_code = 0;
    stack->head--;

    return *(stack->data + stack->head);

}

void stack_display(const struct stack_t *stack) {
    if (stack == NULL) {
        return;
    }
    if (stack->data == NULL) {
        return;
    }
    if (stack->head > stack->capacity) {
        return;
    }
    if (stack->head < 0) {
        return;
    }
    if (stack->capacity <= 0) {
        return;
    }
    if (stack->head == 0) {
        return;
    }
    int i;
    for (i = stack->head - 1; i >= 0; i--) {
        printf("%d ", *(stack->data + i));
    }
}

void stack_free(struct stack_t *stack) {
    if (stack != NULL) {
        if (stack->data != NULL) {
            free(stack->data);
        }
        free(stack);
    }
}