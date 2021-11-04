//
// Created by Adam Ludwiczak on 05/06/2021.
//

#ifndef INC_6_5_CHAR_OPERATIONS_H
#define INC_6_5_CHAR_OPERATIONS_H

typedef char (*func)(char);
char *letter_modifier(const char *ch, func function);

char lower_to_upper(char ch);
char upper_to_lower(char ch);
char space_to_dash(char ch);
char reverse_letter(char ch);
#endif //INC_6_5_CHAR_OPERATIONS_H
