#include <stdio.h>
#include "graf.h"


struct graf *wczytaj_graf(FILE *in)
{
    struct graf *g = NULL;
    fscanf(in, "%d %d", &g->w, &g->h);
    g = init_graf(g->w * g->h);
    for (int x = 0; x < g->w * g->h; x++)
        g->tab[x] = init_td_krawedz(1);

    char tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
    int krawedz_od = 0;
    int krawedz_do = 0;
    double waga = 0;

    while(!feof(in)) 
    {
        fscanf(in, "%c%c", &tmp1, &tmp2);
        if(tmp2 == '\n') 
        {
            krawedz_do++;
            continue;
        }
        struct krawedz *k = NULL;
        fscanf(in, "%d%c%c%lf", &krawedz_do, &tmp3, &tmp4, &waga);
        k = init_k(krawedz_do, waga);
        
        g->tab[krawedz_do] = dodaj_k(g->tab, k);
    }
    return g;
}


