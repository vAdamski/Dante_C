//
// Created by Adam Ludwiczak on 05/06/2021.
//

#include "char_operations.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *letter_modifier(const char *ch, func function)
{
    if (ch == NULL || function == NULL) return NULL;

    int lenghtText = (int)strlen(ch);

    char *newText = malloc((lenghtText + 1) * sizeof(char));
    if (newText == NULL) return NULL;

    strcpy(newText, ch);

    for (int i = 0; i < lenghtText; ++i)
    {
        *(newText + i) = function(*(newText + i));
    }

    return newText;
}
char lower_to_upper(char ch)
{
    if (ch >= 97 && ch <= 122)
    {
        ch -= 32;
    }

    return ch;
}
char upper_to_lower(char ch)
{
    if (ch >= 65 && ch <= 90)
    {
        ch += 32;
    }

    return ch;
}
char space_to_dash(char ch)
{
    if (ch == ' ')
    {
        return '_';
    }

    return ch;
}
char reverse_letter(char ch)
{
    if (ch >= 97 && ch <= 122)
    {
        return (char)(122 - (ch - 97));
    }

    if (ch >= 65 && ch <= 90)
    {
        return (char)(90 - (ch - 65));
    }

    return ch;
}