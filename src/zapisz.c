#include <stdio.h>
#include <stdlib.h>
#include "graf.h"

// void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE *out, struct graf *g)
{
    //fprintf(out, "%d %d\n", );
    for (int x = 0; x < g->cells; x++)
    {
        for (int y = 0; y < g->tab[x]->cells; y++)
        {
            fprintf(out, "\t");
            fprintf(out, " %d :%lf ", g->tab[x]->tab[y]->_do, g->tab[x]->tab[y]->waga);
        }
        fprintf(out, "\n");
    }
}
