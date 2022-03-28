#include "graf_fun.h"
#include <stdlib.h>
#define INFTY 999999
#include "stdio.h"

struct stos *dodaj_w(struct stos *s, int w)
{
    if (s->cells >= s->size)
    {
        s->size *= 2;
        s->tab = realloc(s->tab, sizeof(int) * s->size);
    }
    s->tab[s->cells] = w;
    s->cells++;
    return s;
}

int zdejmij_w(struct stos *s)
{
    if (s->cells)
    {
        s->cells--;
        return s->tab[s->cells];
    }
    return -1;
}

struct stos *init_stos(unsigned int min_size)
{
    struct stos *s = malloc(sizeof(struct stos));
    s->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    s->size = size;
    s->tab = malloc(sizeof(int) * size);
    return s;
}

void free_stos(struct stos *s)
{
    free(s->tab);
}

void bfs(struct graf *g, int od)
{
    struct stos *s = init_stos(g->cells);
    int *poprzednik, *odleglosc, *zwiedzone;
    poprzednik = malloc(sizeof(int) * (g->cells));
    odleglosc = malloc(sizeof(int) * (g->cells));
    zwiedzone = malloc(sizeof(int) * (g->cells));
    for (int x = 0; x < g->cells; x++)
    {
        odleglosc[x] = INFTY;
        poprzednik[x] = 0;
        zwiedzone[x] = 0;
    }
    odleglosc[od] = 0;
    s = dodaj_w(s, od);
    int w, v;
    while (s->cells)
    {
        w = zdejmij_w(s);
        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            if (zwiedzone[v] == 0)
            {
                zwiedzone[v] = 1;
                odleglosc[v] = odleglosc[w] + 1;
                poprzednik[v] = w;
                s = dodaj_w(s, v);
            }
        }
        zwiedzone[w] = 2;
    }
    // for (int x = 0; x < g->cells; x++)
    //     printf("wierzcholek: %d, odleglosc %d, poprzednik %d\n", x, odleglosc[x], poprzednik[x]);
    free(poprzednik);
    free(odleglosc);
    free(zwiedzone);
    free_stos(s);
    free(s);
}