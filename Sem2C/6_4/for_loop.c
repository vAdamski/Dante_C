#include <stdio.h>
#include "for_loop.h"

void for_loop(double start_value, double step, double stop_value, void(*func)(double)) {
    if (func == NULL) {
        return;
    }
    if (step == 0) {
        return;
    }
    if (step < 0) {
        if (start_value <= stop_value)
            return;
    } else {
        if (start_value >= stop_value)
            return;
    }
    func(start_value);
    for_loop(start_value + step, step, stop_value, func);
}

void print_value(double v) {
    printf("%lf ", v);
}

void print_accumulated(double v) {
    static double ac = 0;
    ac += v;
    printf("%lf ", ac);
}

void print_square(double v) {
    printf("%lf ", v * v);
}

void print_abs(double v) {
    if (v < 0) {
        v = -v;
    }
    printf("%lf ", v);
}