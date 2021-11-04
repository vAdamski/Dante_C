#include <stdio.h>

#include "for_loop.h"

int main() {
    void (*funcs[4])(double);
    *(funcs + 0) = print_value;
    *(funcs + 1) = print_accumulated;
    *(funcs + 2) = print_square;
    *(funcs + 3) = print_abs;
    double start, step, end;
    int op;
    printf("Podaj s s e");
    if (scanf("%lf %lf %lf", &start, &step, &end) != 3) {
        printf("Incorrect input");
        return 1;
    }
    if ((start > end && step > 0) || (start < end && step < 0) || step == 0) {
        printf("Incorrect input data");
        return 2;
    }
    printf("Op");
    if (scanf("%d", &op) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (op < 0 || op > 3) {
        printf("Incorrect input data");
        return 2;
    }
    for_loop(start, step, end, *(funcs + op));
    return 0;
}