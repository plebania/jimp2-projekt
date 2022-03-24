#include <stdio.h>
#include <stdlib.h>
#include "graf.h"

// void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE *out, struct graf *g)
{
    for (int x = 0; x < g->cells; x++)
    {
        fprintf(out, " ");
        for (int y = 0; y < g->tab[x]->cells; y++)
            fprintf(out, "[%d-%lf->%d]\n", x, g->tab[x]->tab[y]->waga, g->tab[x]->tab[y]->_do);
        fprintf(out, " \n");
    }
}