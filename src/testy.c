#include "graf_fun.h"
#include "io.h"
#include <stdlib.h>
#include <stdio.h>
// TODO kolejka, bfs, dijkstra

int test1_kopiec(int ile, double od, double _do)
{
    struct kopiec *k;
    k = init_kopiec(ile);
    
    for (int x = 0; x < ile; x++)
        k = kopiec_dodaj(k, rand() % 100, rand() * (_do - od) / RAND_MAX + od);
    double pom = 0;
    while (k->cells)
    {
        pom = k->droga[0];
        k = kopiec_zdejmij(k);

        if (k->droga[0] < pom)
        {
            free_kopiec(k);
            return EXIT_FAILURE;
        }
    }
    free_kopiec(k);
    free(k);
    return EXIT_SUCCESS;
}

int test1_kolejka(int ile)
{
    struct kolejka *k;
    k = init_kolejka();

    for (int x = 0; x < ile; x++)
        k = dodaj_w(k, x);

    int pom;
    while (k)
    {
        pom = k->w;
        k = zdejmij_w(k);
    }

    free_kolejka(k);
    return EXIT_SUCCESS;
}
/*
int test1_make(int ile, double min_wag, double max_wag)
    {
    FILE *in_out=NULL;
    struct graf *g=NULL;
    int w=0,h=0;
    for (int x=0; x<ile; x++)
        {
        in_out=fopen("tmp", 'w');
        w=rand%100;
        h=rand%100;
        zachowanie_make(in_out, w,  h, min_wag, max_wag
        fclose(in_out);
        in_out=fopen("tmp", 'r');
        g=wczytaj_garf(in_out);
        if (g->w!=w ||g->h!=h)
            {
            if (g)
                {
                free_graf(g);
                free(g);
                }
            return EXIT_FAILURE;
            }

        }
        free_graf(g);
                free(g);
    return EXIT_SUCCESS;
    }
*/