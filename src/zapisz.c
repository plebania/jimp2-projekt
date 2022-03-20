#include <stdio.h>
#include <stdlib.h>
#include "graf.h"

//void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE * out, struct graf *g)
{
    for (int x = 0; x < g->wierzcholki->cells; x++)
    {
        fprintf(out, " ");
        for (int y = 0; y < g->wierzcholki->tab[x]->krawedzie->cells; y++)
            fprintf(out, "[%d-%lf->%d]\n", g->wierzcholki->tab[x]->nr, g->wierzcholki->tab[x]->krawedzie->tab[y]->waga, g->wierzcholki->tab[x]->krawedzie->tab[y]->_do->nr);
        fprintf(out, " \n");
    }
}