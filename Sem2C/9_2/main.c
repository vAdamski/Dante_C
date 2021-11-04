#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main() {
    struct stack_t *stack;
    if (stack_init(&stack)) {
        printf("Failed to allocate memory");
        return 8;
    }
    while (1) {
        printf("Co teraz? ");
        int ch;
        if (scanf("%d", &ch) != 1) {
            printf("Incorrect input");
            stack_destroy(&stack);
            return 1;
        }
        int a;
        switch (ch) {
            case 0:
                stack_destroy(&stack);
                return 0;
            case 1:
                printf("Podaj liczbe");
                if (scanf("%d", &a) != 1) {
                    printf("Incorrect input");
                    stack_destroy(&stack);
                    return 1;
                }
                if (stack_push(stack, a)) {
                    stack_destroy(&stack);
                    printf("Failed to allocate memory");
                    return 8;
                }
                break;
            case 2:
                if (stack_empty(stack)) {
                    printf("Stack is empty\n");
                    continue;
                }
                a = stack_pop(stack, NULL);
                printf("%d\n", a);
                break;
            case 3:
                if (stack_empty(stack)) {
                    printf("1\n");
                } else {
                    printf("0\n");
                }
                break;
            case 4:
                if (stack_empty(stack)) {
                    printf("Stack is empty\n");
                    continue;
                }
                stack_display(stack);
                printf("\n");
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
    return 0;
}