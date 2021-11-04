#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "structurefile.h"


//Pole trojkata
float area_triangle(const struct triangle_t *t)
{
    if(t == NULL || &t->p1 == NULL || &t->p2 == NULL || &t->p3 == NULL) return -1;

    if (t->p1.x == t->p2.x && t->p1.y == t->p2.y) {
        return -1;
    }
    if(t->p1.x==t->p3.x && t->p1.y==t->p3.y){
        return -1;
    }
    if(t->p2.x==t->p3.x && t->p2.y==t->p3.y){
        return -1;
    }

    int x=(t->p2.x-t->p1.x)*(t->p3.y-t->p1.y)-(t->p2.y-t->p1.y)*(t->p3.x-t->p1.x);

    return 0.5*abs(x);
}
//Pole prostokata
float area_rectangle(const struct rectangle_t *r)
{
    if(r == NULL || r->width < 0 || r->height < 0) return -1;
    return (float)(r->width * r->height);
}
//Pole kola
float area_circle(const struct circle_t *c)
{
    if(c == NULL) return -1;
    if(c->r <= 0) return -1;

    return M_PI*pow(c->r,2);
}
//Pole figury x
float area_figure(const struct figure_t *f)
{
    if(f == NULL) return -1;

    if(f->type == TRIANGLE)
    {
        if
        (
            (f->triangle.p1.x == f->triangle.p2.x && f->triangle.p1.y == f->triangle.p2.y) ||
            (f->triangle.p1.x == f->triangle.p3.x && f->triangle.p1.y == f->triangle.p3.y) ||
            (f->triangle.p2.x == f->triangle.p3.x && f->triangle.p2.y == f->triangle.p3.y)
        )
        {
            return -1;
        }
        else
        {
            return area_triangle(&f->triangle);
        }
    }
    else if(f->type == RECTANGLE)
    {
        if(f->rect.height < 0 || f->rect.width < 0)
            return -1;
        else
            return area_rectangle(&f->rect);
    }
    else if(f->type == CIRCLE)
    {
        if(f->circ.r <= 0)
            return -1;
        else
            return area_circle(&f->circ);
    }
    else
    {
        return -1;
    }
}

void display_rectangle(const struct rectangle_t *rect)
{
    //Rectangle (-1, 8), width = 10, height = 17
    if(rect == NULL) return;
    printf("Rectangle (%d, %d), width = %d, height = %d\n", rect->p.x, rect->p.y, rect->width, rect->height);
}

void display_triangle(const struct triangle_t *t)
{
    //Triangle p1(1, -3), p2(-4, -10), p3(-4, -9)
    if(t == NULL) return;
    printf("Triangle p1(%d, %d), p2(%d, %d), p3(%d, %d)\n", t->p1.x, t->p1.y, t->p2.x, t->p2.y, t->p3.x, t->p3.y);
}

void display_circle(const struct circle_t *circ)
{
    //Circle (-10, 1), radius = 6.921945
    if(circ == NULL) return;
    printf("Circle (%d, %d), radius = %f\n", circ->c.x, circ->c.y, circ->r);
}

void display_figure(struct figure_t *f)
{
    if(f == NULL) return;

    if(f->type == 1)
    {
        display_triangle(&f->triangle);
    }
    else if (f->type == 2)
    {
        display_rectangle(&f->rect);
    }
    else if (f->type == 3)
    {
        display_circle(&f->circ);
    }
    else
    {
        return;
    }

}

int sort_by_area(struct figure_t **figures, int size)
{
    struct figure_t *f;
    if(figures == NULL || size < 1) return 1;

    for (int i = 0; i < size; ++i)
    {
        if(area_figure(*(figures + i)) == -1) return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if(area_figure(*(figures + j)) < area_figure(*(figures + j + 1)))
            {
                f = *(figures + j + 1);
                *(figures + j + 1) = *(figures + j);
                *(figures + j) = f;
            }
        }
    }
    return 0;
}
