#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graf.h"
#include "zapisz.h"
//#include "zapisz.h"
int main(int argc, char *argv[])
{
    FILE *out = fopen(argv[1], "w");

    srand(time(NULL));
    struct graf *g = stworz_graf(5, 10);
    printf("huj");
    zapisz_graf(out, g); 
    //for (int x = 0; x < g->cells; x++)
    //{
    //    printf(" ");
    //    for (int y = 0; y < g->tab[x]->cells; y++)
    //        printf("[%d-%lf->%d]\n", x, g->tab[x]->tab[y]->waga, g->tab[x]->tab[y]->_do);
    //    printf(" \n");
    //}
    // free_graf(g);
    return 0;
}
