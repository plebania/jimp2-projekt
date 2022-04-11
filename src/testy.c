#include "graf_fun.h"
#include <stdlib.h>
#include <stdio.h>
// TODO kolejka, bfs, dijkstra

int test1_kopiec(int ile, double od, double _do)
{
    struct kopiec *k;
    k = init_kopiec(ile);
    for (int x = 0; x < ile; x++)
        k = kopiec_dodaj(k, rand() % 100, od + rand() / RAND_MAX / (_do - od));
    double pom = 0;
    while (k->cells)
    {
        pom = k->od[0];
        k = kopiec_zdejmij(k);
        if (k->od[0] < pom)
        {
            free_kopiec(k);
            return EXIT_FAILURE;
        }
    }
    free_kopiec(k);
    free(k);
    return EXIT_SUCCESS;
}

// void test1_kolejka(int ile)
// {
//     struct kolejka *k;
//     k = init_kolejka();

//     for (int x = 0; x < ile; x++)
//     {
//         k = dodaj_w(k, x);
//     }

//     while (k)
//     {
//         k = zdejmij_w(k);
//         printf
//     }
//     free(k);
// }

void test1_kolejka(int ile)
{
    struct kolejka *k;
    k = init_kolejka();

    for (int x = 0; x < ile; x++)
    {
        k = dodaj_w(k, x);
        k->w = x;
    }
    while (k)
    {
        printf("%d\n", k->w);
        k = zdejmij_w(k);
    }
    free_kolejka(k);
}