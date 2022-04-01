#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "graf.h"
#include "zapisz.h"
#include "graf_fun.h"
#include "arg_pars.h"

int main(int argc, char *argv[])
{

    srand(time(NULL));
    arg_parse(argc, argv);
    struct graf *g = stworz_graf(3, 3, -1, 1, 1);
    for (int x = 0; x < g->cells; x++)
    {
        printf(" ");
        for (int y = 0; y < g->tab[x]->cells; y++)
            printf("[%d-%lf->%d]\n", x, g->tab[x]->tab[y]->waga, g->tab[x]->tab[y]->_do);
        printf(" \n");
    }

    // double w_min = argc > 4 ? atof(argv[5]) : 0.0;
    // double w_max = argc > 5 ? atof(argv[6]) : 1.0;

    // printf("%s %s %s\n", argv[0], argv[1], argv[2]);
    // int q = strcmp(argv[1], "make") == 0 ? 1 : 2;
    // printf("%d", q);
}