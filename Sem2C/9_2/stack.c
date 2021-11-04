#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int stack_init(struct stack_t **stack) {
    if (stack == NULL) {
        return 1;
    }
    *stack = malloc(sizeof(struct stack_t));
    if (*stack == NULL) {
        return 2;
    }
    (*stack)->head = NULL;
    return 0;
}

int stack_push(struct stack_t *stack, int value) {
    if (stack == NULL) {
        return 1;
    }
    struct node_t *node = malloc(sizeof(struct node_t));
    if (node == NULL) {
        return 2;
    }
    node->data = value;
    node->next = stack->head;
    stack->head = node;
    return 0;
}

void stack_display(const struct stack_t *stack) {
    if (stack == NULL) {
        return;
    }
    struct node_t *node = stack->head;
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
}

int stack_pop(struct stack_t *stack, int *err_code) {
    if (stack == NULL || stack->head == NULL) {
        if (err_code)*err_code = 1;
        return 0;
    }
    if (err_code)*err_code = 0;
    struct node_t *node = stack->head;
    stack->head = node->next;
    int val = node->data;
    free(node);
    return val;
}

void stack_destroy(struct stack_t **stack) {
    if (stack == NULL) {
        return;
    }
    struct node_t *node = (*stack)->head;
    while (node != NULL) {
        struct node_t *del = node;
        node = node->next;
        free(del);
    }
    free(*stack);
}

int stack_empty(const struct stack_t *stack) {
    if (stack == NULL) {
        return 2;
    }
    if (stack->head == NULL) {
        return 1;
    }
    return 0;
}