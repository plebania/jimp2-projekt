#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graf.h"
#include "zapisz.h"
int main(int argc, char *argv[])
{
    FILE *out = fopen(argv[1], "w");

    srand(time(NULL));
    struct graf *g = stworz_graf(1, 10);
    for (int x = 0; x < g->wierzcholki->cells; x++)
    {
        printf(" ");
        for (int y = 0; y < g->wierzcholki->tab[x]->krawedzie->cells; y++)
            printf("[%d-%lf->%d]\n", g->wierzcholki->tab[x]->nr, g->wierzcholki->tab[x]->krawedzie->tab[y]->waga, g->wierzcholki->tab[x]->krawedzie->tab[y]->_do->nr);
        printf(" \n");
    }

    // printf("[%d-%lf->%d]\n", g->wierzcholki->tab[x]->nr, g->wierzcholki->tab[x]->krawedzie->tab[y]->waga, g->wierzcholki->tab[x]->krawedzie->tab[y]->_do->nr);
    free_graf(g);
    return 0;
}