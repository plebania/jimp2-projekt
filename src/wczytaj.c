#include <stdio.h>
#include "graf.h"

struct graf *wczytaj_graf(FILE * in, struct graf *g)
{
    while(!feof(in))
    {
        //fscanf(in, "%d %d", &)
        for (int x = 0; x < g->wierzcholki->cells; x++)
        {
            for (int y = 0; y < g->wierzcholki->tab[x]->krawedzie->cells; y++)
                fscanf(in, "\t %d :%lf", &g->wierzcholki->tab[x]->krawedzie->tab[y]->_do->nr, &g->wierzcholki->tab[x]->krawedzie->tab[y]->waga);
        }
    }
}