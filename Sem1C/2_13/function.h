//
// Created by Adam Ludwiczak on 28/05/2021.
//

#ifndef INC_2_13_FUNCTION_H
#define INC_2_13_FUNCTION_H

struct message_t
{
    char a;
    double b;
    int c;
};

int load_data(struct message_t* cp, int size, const char* filename);
int decode_message(const struct message_t* cp, int size, char* msg, int text_size);

#endif //INC_2_13_FUNCTION_H
