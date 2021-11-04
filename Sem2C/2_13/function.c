//
// Created by Adam Ludwiczak on 28/05/2021.
//

#include "function.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int load_data(struct message_t* cp, int size, const char* filename)
{
    if (filename == NULL || cp == NULL || size < 1)
        return -1;

    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        return -2;

    unsigned int n;

    if (fread(&n, sizeof(unsigned int), 1, file) != 1)
    {
        fclose(file);
        return -3;
    }

    if(n % 24 != 0)
    {
        fclose(file);
        return -3;
    }

    n /= sizeof(struct message_t);

    if ((int)n > size) n = size;
    else size = n;

    while (n > 0 && fread(cp++, sizeof(struct message_t), 1, file) == 1)
    {
        n--;
    }

    if (n != 0)
    {
        fclose(file);
        return -3;
    }

    fclose(file);
    return size;
}
int decode_message(const struct message_t* cp, int size, char* msg, int text_size) {
    if (size < 1 || size > 100 || msg == NULL || cp == NULL || text_size < 1)
        return 1;

    unsigned char* ptr = (unsigned char*)cp+0;
    int i = 0, x=0;
    while (isalpha(*ptr) == 0 && isdigit(*ptr) == 0)
    {
        ptr++;
    }

    while (1)
    {
        if (i == size)
        {
            *msg = '\x0';
            break;
        }

        i++;
        ptr++;

        if (x + 7 >= text_size-1)
        {
            memmove(msg, ptr, text_size-1-x);
            msg += text_size-1-x;
            *msg = '\x0';
            break;
        }

        memmove(msg, ptr, 7);
        x += 7;

        msg += 7;
        ptr += 19;

        if (x + 4 >= text_size)
        {
            memmove(msg, ptr, text_size-x-1);
            msg += text_size-1-x;
            *msg = '\x0';
            break;
        }

        memmove(msg, ptr, 4);
        x += 4;

        if (x >= text_size)
        {
            *msg = '\x0';
            break;
        }

        msg += 4;
        ptr += 4;

        if (*(ptr-1) == '\x0' || *ptr == '\x0')
        {
            *msg = '\x0';
            break;
        }
    }

    return 0;
}