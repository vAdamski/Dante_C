#ifndef FOR_LOOP_H
#define FOR_LOOP_H

void for_loop(double start_value, double step, double stop_value, void(*func)(double));

void print_value(double v);

void print_accumulated(double v);

void print_square(double v);

void print_abs(double v);

#endif //FOR_LOOP_H
