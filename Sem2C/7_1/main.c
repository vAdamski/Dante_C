#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

int stats(int *sum, float *avg, int num, ...) {
    if (sum == NULL || avg == NULL || num <= 0) {
        return 1;
    }
    va_list list;
            va_start(list, num);
    int i;
    *sum = 0;
    for (i = 0; i < num; i++) {
        *sum += va_arg(list, int);
    }
    *avg = (float) *sum / (float) num;
            va_end(list);
    return 0;
}

int main(int argc, char **argv) {
    printf("Ile: ");
    int ile;
    if (scanf("%d", &ile) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (ile <= 0 || ile > 3) {
        printf("Incorrect input data");
        return 2;
    }
    int sum;
    float avg;
    int a, b, c;
    printf("Numery ");
    if (ile == 1) {
        if (scanf("%d", &a) != 1) {
            printf("Incorrect input");
            return 1;
        }
        stats(&sum, &avg, 1, a);
    }
    if (ile == 2) {
        if (scanf("%d", &a) != 1) {
            printf("Incorrect input");
            return 1;
        }
        if (scanf("%d", &b) != 1) {
            printf("Incorrect input");
            return 1;
        }
        stats(&sum, &avg, 2, a, b);
    }
    if (ile == 3) {
        if (scanf("%d", &a) != 1) {
            printf("Incorrect input");
            return 1;
        }
        if (scanf("%d", &b) != 1) {
            printf("Incorrect input");
            return 1;
        }
        if (scanf("%d", &c) != 1) {
            printf("Incorrect input");
            return 1;
        }
        stats(&sum, &avg, 3, a, b, c);
    }
    printf("%d %f\n", sum, avg);
    return 0;
}
