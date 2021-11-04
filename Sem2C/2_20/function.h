//
// Created by Adam Ludwiczak on 28/05/2021.
//

#ifndef INC_2_20_FUNCTION_H
#define INC_2_20_FUNCTION_H

int power(int base, int a);
int decode(const char * filename, char *txt, int size);
char *decimal_to_binary(int n);
int encode(const char *input, char *txt, const char *output);
void clean_stdin(void);

#endif //INC_2_20_FUNCTION_H