#ifndef COMPARATORS_H
#define COMPARATORS_H
int sort_int(int *arr,int size, int(*comparator)(int,int));

int comp_int(int a, int b);

int comp_int_abs(int a, int b);

int comp_int_length(int a, int b);

int comp_int_digits_sum(int a, int b);

#endif //COMPARATORS_H
