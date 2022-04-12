#include <stdio.h>
#include <stdlib.h>
#include "graf.h"
#include "io.h"

// void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE *out, struct graf *g)
{
    fprintf(out, "%d %d\n", g->w, g->h);
    for (int x = 0; x < g->cells; x++)
    {
        fprintf(out, "\t");
        for (int y = 0; y < g->tab[x]->cells; y++)
        {
            fprintf(out, " %d :%lf ", g->tab[x]->tab[y]->_do, g->tab[x]->tab[y]->waga);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

struct graf *wczytaj_graf(FILE *in)
{

    struct graf *g = NULL;

    if (in == NULL)
    {
        fprintf(stderr, "Plik nie moze być pusty!\n");
        return g;
    }
    int w, h;
    fscanf(in, "%d %d", &w, &h);

    if (w <= 0 || h <= 0)
    {
        fprintf(stderr, "Bledny format pliku wczytywanego!\n");
        return g;
    }

    g = init_graf(w * h);
    g->w = w;
    g->h = h;
    g->cells = w * h;
    for (int x = 0; x < w * h; x++)
        g->tab[x] = init_td_krawedz(1);
    char tmp1, tmp2, tmp3, tmp4;
    int krawedz_do = 0, krawedz_od = 0;
    double waga = 0;
    while (!feof(in))
    {
        fscanf(in, "%c%c", &tmp1, &tmp2);
        if (tmp2 == '\n')
        {
            krawedz_od++;
            continue;
        }
        fscanf(in, "%d%c%c%lf", &krawedz_do, &tmp3, &tmp4, &waga);
        g->tab[krawedz_od] = dodaj_k(g->tab[krawedz_od], init_k(krawedz_do, waga));
    }
    fclose(in);
    return g;
}
