//
// Created by Adam Ludwiczak on 31/05/2021.
//

#include "int_operations.h"
#include <stdio.h>

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

op_func get_function(enum operations_t op)
{
    switch(op)
    {
        case op_add:
            return add_int;
        case op_sub:
            return sub_int;
        case op_div:
            return div_int;
        case op_mul:
            return mul_int;
        default:
            return NULL;
    }
}