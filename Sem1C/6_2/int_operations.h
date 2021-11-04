//
// Created by Adam Ludwiczak on 31/05/2021.
//

#ifndef INC_6_2_INT_OPERATIONS_H
#define INC_6_2_INT_OPERATIONS_H


enum operations_t{
    op_add = 0,
    op_sub = 1,
    op_div = 2,
    op_mul = 3
};

int add_int(int a,int b);
int sub_int(int a,int b);
int div_int(int a,int b);
int mul_int(int a,int b);

typedef int (*op_func)(int,int);
op_func get_function(enum operations_t op);


#endif //INC_6_2_INT_OPERATIONS_H
