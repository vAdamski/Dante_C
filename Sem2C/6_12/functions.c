//
// Created by Adam Ludwiczak on 31/05/2021.
//

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void print_chicken(void)
{
    printf(" MM\n"
           "<' \\___/|\n"
           "  \\_  _/\n"
           "    ][\n\n");
}
void print_egg(void)
{
    printf("  .~~~.\n"
           " /     \\\n"
           "(\\/\\/\\/\\)\n"
           " \\     /\n"
           "  `~~~`\n\n");
}
void print_rabbit(void)
{
    printf(" \\\\   //\n"
           "  )\\-/(\n"
           "  /o o\\\n"
           " ( =T= )\n"
           " /'---'\\\n\n");
}

void* easter(int size, void (*f1)(void), void (*f2)(void), void (*f3)(void))
{
    if(size < 1 || f1 == NULL || f2 == NULL || f3 == NULL) return NULL;

    int numLottery;
    time_t time_s;
    srand((unsigned) time(&time_s));
    void (**tab)(void);
    tab = malloc(size * sizeof(void (*)(void)));
    if (tab == NULL)
        return NULL;

    for (int i = 0; i < size; ++i)
    {
        numLottery = rand() % 3;

        switch (numLottery)
        {
            case 0:
                *(tab + i) = f1;
                break;
            case 1:
                *(tab + i) = f2;
                break;
            case 2:
                *(tab + i) = f3;
                break;
            default:
                *(tab + i) = NULL;
                break;
        }
    }
    return tab;
}