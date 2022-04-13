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
    return EXIT_SUCCESS;
}

int test1_kolejka(int ile)
{
    int _max = 100, _min = 0;
    struct kolejka *k;
    int *tab = malloc(sizeof(int) * ile);
    k = init_kolejka();

    for (int x = 0; x < ile; x++)
    {
        tab[x] = rand() % (_max - _min) + _min;
        k = dodaj_w(k, tab[x]);
    }
    int x = 0;
    while (k->pierwszy)
    {
        if (k->pierwszy->w != tab[x])
        {
            free(tab);
            free_kolejka(k);
            return EXIT_FAILURE;
        }
        k = zdejmij_w(k);
        x++;
    }
    free(tab);
    free_kolejka(k);
    return EXIT_SUCCESS;
}