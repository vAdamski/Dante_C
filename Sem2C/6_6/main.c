#include <stdio.h>

#include "comparators.h"
#include <stdlib.h>

int main() {
    int (**funcs)(int, int);
    funcs = malloc(sizeof(int (*)(int, int)) * 4);
    if (funcs == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    *(funcs) = comp_int;
    *(funcs + 1) = comp_int_abs;
    *(funcs + 2) = comp_int_length;
    *(funcs + 3) = comp_int_digits_sum;
    int len;
    printf("Podaj dlugosc tablicy: ");
    if (scanf("%d", &len) != 1) {
        printf("Incorrect input");
        free(funcs);
        return 1;
    }
    if (len < 1) {
        printf("Incorrect input data");
        free(funcs);
        return 2;
    }
    int *arr = malloc(sizeof(int) * len);
    if (arr == NULL) {
        free(funcs);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Daj licb");
    for (int i = 0; i < len; i++) {
        if (scanf("%d", arr + i) != 1) {
            printf("Incorrect input");
            free(arr);
            free(funcs);
            return 1;
        }
    }
    printf("Podaj rodzaj");
    int op;
    if (scanf("%d", &op) != 1) {
        printf("Incorrect input");
        free(arr);
        free(funcs);
        return 1;
    }
    if (op < 0 || op > 3) {
        printf("Incorrect input data");
        free(arr);
        free(funcs);
        return 2;
    }
    sort_int(arr, len, *(funcs + op));
    for (int i = 0; i < len; i++) {
        printf("%d ", *(arr + i));
    }
    free(arr);
    free(funcs);
    return 0;
}