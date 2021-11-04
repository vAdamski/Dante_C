#include <stdio.h>
#include "stack.h"

int main() {
    struct stack_t *stack;
    if (stack_init(&stack, 10) == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    while (1) {
        printf("Wybierz opcje ");
        int ch;
        if (scanf("%d", &ch) != 1) {
            printf("Incorrect input");
            stack_free(stack);
            return 1;
        }
        int err;
        switch (ch) {
            case 0:
                stack_free(stack);
                return 0;
                break;
            case 1:
                printf("Liczba: ");
                if (scanf("%d", &ch) != 1) {
                    printf("Incorrect input");
                    stack_free(stack);
                    return 1;
                }
                if (stack_push(stack, ch)) {
                    printf("Failed to allocate memory");
                    stack_free(stack);
                    return 8;
                }
                break;
            case 2:
                ch = stack_pop(stack, &err);
                if (err != 0) {
                    printf("Stack is empty\n");
                } else {
                    printf("%d\n", ch);
                }
                break;
            case 3:
                if (stack->head == 0) {
                    printf("Stack is empty\n");
                } else {
                    stack_display(stack);
                    printf("\n");
                }
                break;
            default:
                printf("Incorrect input data\n");
        }
    }
    return 0;
}