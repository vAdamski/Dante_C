#include <stdio.h>
#include "structurefile.h"

int main()
{
    //Zmienne
    struct figure_t figures[50];
    int ans = 0;
    int x = 0;

    //Wczytywanie danych
    while(x < 50)
    {
        printf("Enter figure's type: ");
        if(scanf("%d", &ans) != 1)
        {
            printf("Incorrect input");
            return 1;
        }
        if (ans == 0)
        {
            break;
        }
        if(ans == 1)
        {
            printf("Enter vertices' coordinates of a triangle (x1 y1 x2 y2 x3 y3): ");
            (figures+x)->type = 1;
            int error = scanf("%d %d %d %d %d %d",  &(figures+x)->triangle.p1.x, &(figures+x)->triangle.p1.y,
                                                    &(figures+x)->triangle.p2.x, &(figures+x)->triangle.p2.y,
                                                    &(figures+x)->triangle.p3.x, &(figures+x)->triangle.p3.y);

            if (error != 6)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else if (ans == 2)
        {
            printf("Enter coordinates of a rectangle along with its dimensions (x y width height): ");
            (figures+x)->type = 2;
            int error = scanf("%d %d %d %d",    &(figures+x)->rect.p.x, &(figures+x)->rect.p.y,
                                                &(figures+x)->rect.width, &(figures+x)->rect.height);

            if (error != 4)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else if (ans == 3)
        {
            printf("Enter coordinates and radius of a circle: ");
            (figures+x)->type = 3;
            int error = scanf("%d %d %f", &(figures+x)->circ.c.x, &(figures+x)->circ.c.y, &(figures+x)->circ.r);

            if (error != 3)
            {
                printf("Incorrect input\n");
                return 1;
            }
        }
        else
        {
            printf("Incorrect input data\n");
            return 2;
        }

        x++;
    }

    //Sprawdzanie danych
    for(int i = 0; i < x; i++)
    {
        //Sprawdxanie trojkat
        if((figures+i)->type == 1)
        {
            if
            (
                ((figures+i)->triangle.p1.x == (figures+i)->triangle.p2.x) && ((figures+i)->triangle.p1.y == (figures+i)->triangle.p2.y) ||
                ((figures+i)->triangle.p2.x == (figures+i)->triangle.p3.x) && ((figures+i)->triangle.p2.y == (figures+i)->triangle.p3.y) ||
                ((figures+i)->triangle.p1.x == (figures+i)->triangle.p3.x) && ((figures+i)->triangle.p1.y == (figures+i)->triangle.p3.y)
            )
            {
                printf("Incorrect input data");
                return 2;
            }
        }
        else if ((figures+i)->type == 2)
        {
            if((figures+i)->rect.height < 0 || (figures+i)->rect.width < 0)
            {
                printf("Incorrect input data");
                return 2;
            }
        }
        else if ((figures+i)->type == 3)
        {
            if((figures+i)->circ.r <= 0)
            {
                printf("Incorrect input data");
                return 2;
            }
        }
    }

    struct figure_t *p[50];

    for(int i=0;i<x;i++){
        *(p+i)=figures+i;
    }

    sort_by_area(p, x);

    for (int i = 0; i < x; ++i)
    {
        display_figure(*(p+i));
    }

    return 0;
}
