#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graf.h"
#include "zapisz.h"
#include "graf_fun.h"

int main(int argc, char *argv[])
{
    FILE *out = fopen(argv[1], "w");
    int val1 = atoi(argv[2]);
    int val2 = atoi(argv[3]);
    // double w_min = argc > 4 ? atof(argv[4]) : 0.0;
    // double w_max = argc > 5 ? atof(argv[5]) : 1.0;

    if (val1 <= 0 || val2 <= 0)
    {
        fprintf(stderr, "Parametry na szerokosc i wysokosc nie moga byc ujmne\n");
        return 1;
    }

    if (argc > 1 && argc < 3)
    {
        fprintf(stderr, "Niepoprawna ilosc argumnetow\n");
        return 1;
    }

    if (argc >= 3)
    {
        srand(time(NULL));
        struct graf *g = stworz_graf(val1, val2);
        zapisz_graf(out, g);

        /*for (int x = 0; x < g->cells; x++)
        {
            printf(" ");
            for (int y = 0; y < g->tab[x]->cells; y++)
                printf("[%d-%lf->%d]\n", x, g->tab[x]->tab[y]->waga, g->tab[x]->tab[y]->_do);
            printf(" \n");
        }*/
        bfs(g, 0);
        return 0;
    }
}
