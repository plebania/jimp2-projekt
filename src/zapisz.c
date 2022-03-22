#include <stdio.h>
#include <stdlib.h>
#include "graf.h"

//void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE * out, struct graf *g)
{
    for (int x = 0; x < g->wierzcholki->cells; x++)
    {
        for (int y = 0; y < g->wierzcholki->tab[x]->krawedzie->cells; y++)
            fprintf(out, "\t %d :%lf", g->wierzcholki->tab[x]->krawedzie->tab[y]->_do->nr, g->wierzcholki->tab[x]->krawedzie->tab[y]->waga);
        fprintf(out, "\n");
    }
}