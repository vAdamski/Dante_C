//
// Created by Adam Ludwiczak on 23/05/2021.
//

#include "int_operations.h"

int add_int(int a, int b)
{
    return a + b;
}
int sub_int(int a, int b)
{
    return a - b;
}
int div_int(int a, int b)
{
    if(b == 0) return 0;
    return a / b;
}
int mul_int(int a, int b)
{
    return a * b;
}

int calculate(int a, int b, int(*function)(int, int))
{
    return function(a, b);
}