#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>

int sort_int(int *arr, int size, int(*comparator)(int, int)) {
    if (arr == NULL || size <= 0 || comparator == NULL) {
        return 1;
    }
    int change = 1;
    while (change == 1) {
        change = 0;
        for (int i = 0; i < size - 1; i++) {
            if (comparator(*(arr + i), *(arr + i + 1)) == 1) {
                change = 1;
                int t = *(arr + i);
                *(arr + i) = *(arr + i + 1);
                *(arr + i + 1) = t;
            }
        }
    }
    return 0;
}

int comp_int(int a, int b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

int comp_int_abs(int a, int b) {
    if (a < 0) {
        a = -a;
    }
    if (b < 0) {
        b = -b;
    }
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

int digit_sum(int n) {
    if (n < 0) {
        n = -n;
    }
    if (n == 0) {
        return 0;
    }
    return n % 10 + digit_sum(n / 10);
}

int length(int n) {
    if (n < 0) {
        n = -n;
    }
    if (n < 10 && n > -10) {
        return 1;
    }
    return 1 + length(n / 10);
}

int comp_int_length(int a, int b) {
    if (length(a) < length(b)) {
        return -1;
    }
    if (length(a) > length(b)) {
        return 1;
    }
    return 0;

}

int comp_int_digits_sum(int a, int b) {
    if (digit_sum(a) < digit_sum(b)) {
        return -1;
    }
    if (digit_sum(a) > digit_sum(b)) {
        return 1;
    }
    return 0;
}