#include "graf_fun.h"
#include <stdlib.h>
#define INFTY 999999
#include "stdio.h"

struct stos
{
    int *tab, cells, size;
};

struct stos *dodaj_w(struct stos *s, int w)
{
    if (s->cells >= s->size)
    {
        s->size *= 2;
        s->tab = realloc(s->tab, sizeof(int) * s->size);
    }
    s->tab[s->cells] = w;
    s->cells++;
    return s;
}

int zdejmij_w(struct stos *s)
{
    if (s->cells)
    {
        s->cells--;
        return s->tab[s->cells];
    }
    return -1;
}

struct stos *init_stos(unsigned int min_size)
{
    struct stos *s = malloc(sizeof(struct stos));
    s->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    s->size = size;
    s->tab = malloc(sizeof(int) * size);
    return s;
}

void free_stos(struct stos *s)
{
    free(s->tab);
}

struct bfs_out *bfs(struct graf *g, int od)
{
    struct stos *s = init_stos(g->cells);
    struct bfs_out *out = NULL;
    if (od >= g->cells)
        return out;
    out = malloc(sizeof(struct bfs_out));
    out->poprzednik = malloc(sizeof(int) * (g->cells));
    out->odleglosc = malloc(sizeof(int) * (g->cells));
    out->zwiedzone = malloc(sizeof(int) * (g->cells));
    for (int x = 0; x < g->cells; x++)
    {
        out->odleglosc[x] = INFTY;
        out->poprzednik[x] = 0;
        out->zwiedzone[x] = 0;
    }
    out->odleglosc[od] = 0;
    s = dodaj_w(s, od);
    int w, v;
    while (s->cells)
    {
        w = zdejmij_w(s);
        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            if (out->zwiedzone[v] == 0)
            {
                out->zwiedzone[v] = 1;
                out->odleglosc[v] = out->odleglosc[w] + 1;
                out->poprzednik[v] = w;
                s = dodaj_w(s, v);
            }
        }
        out->zwiedzone[w] = 2;
    }
    free_stos(s);
    free(s);
    return out;
}
/*
struct kopiec
{
    int *from, *to;
    double *droga;
    int size, cells;
};

struct kopiec *init_kopiec(int min_size)
{
    struct kopiec *k = malloc(sizeof(struct kopiec));
    k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    k->size = size;
    k->from = malloc(sizeof(int) * size);
    k->to = malloc(sizeof(int) * size);
    k->droga = malloc(sizeof(double) * size);
    return k;
}

struct kopiec *min_heapyfy(struct kopiec *k)
{
    for (int x = 1; x < k->cells; x++)
    {
        int pom = x;
        while (k->droga[pom] > k->droga[(pom - 1) / 2])
        {

            int pom1 = k->droga[pom];
            k->droga[pom] = k->droga[(pom - 1) / 2];
            k->droga[(pom - 1) / 2] = pom1;
            pom = (pom - 1) / 2;
        }
    }
    return k;
}

struct kopiec *kopiec_dodaj(struct kopiec *k, int from, int to, double droga)
{
    if (k->cells >= k->size)
    {
        k->size *= 2;
        k->from = realloc(k->from, sizeof(int) * k->size);
        k->to = realloc(k->to, sizeof(int) * k->size);
        k->droga = realloc(k->droga, sizeof(double) * k->size);
    }
    k->from[k->cells] = from;
    k->to[k->cells] = to;
    k->droga[k->cells] = droga;
    k->cells++;
    for (int x = k->cells - 1; x > 0;)
    {
        int pom = (x - 1) / 2;
        if (k->droga[x] < k->droga[pom])
        {
            int pom_from, pom_to;
            double pom_droga;

            pom_from = k->from[pom];
            pom_to = k->to[pom];
            pom_droga = k->droga[pom];

            k->from[pom] = k->from[x];
            k->to[pom] = k->to[x];
            k->droga[pom] = k->droga[x];

            k->from[x] = pom_from;
            k->to[x] = pom_to;
            k->droga[x] = pom_droga;
        }
        else
            break;
        x = pom;
    }
    return k;
}

struct kopiec *kopiec_zdejmij(struct kopiec *k)
{
    int old_root = k->droga[0];
    k->droga[0] = k->droga[k->cells - 1];
    k->cells--;
    for (int x = 0; x < k->cells - 1;)
    {
        int pom1 = x * 2 + 1;
        int pom = k->droga[pom1];
        if (pom1 < k->cells - 1)
            if (k->droga[pom1 + 1] < pom)
            {
                pom1++;
                pom = k->droga[pom1];
            }

        if (k->droga[x] > pom)
        {
            int pom2 = k->droga[x];
            k->droga[x] = pom;
            k->droga[pom1] = pom2;
        }
        x = pom1;
    }
    return k;
    // return old_root;
}

struct dijkstra_out
{
    int *od;
    double *droga;
};

struct dijkstra_out *dijkstra(struct graf *g, int od)
{
    struct kopiec *k = init_kopiec(g->cells);
    struct dijkstra_out *out = NULL;
    if (od >= g->cells)
        return out;
    out->od = malloc(sizeof(int) * g->cells);
    out->droga = malloc(sizeof(double) * g->cells);
    for (int x = 0; x < g->cells; x++)
        out->droga = INFTY;
    k = kopiec_dodaj(k, 0, 0, 0);
    int w, v;
    double waga;
    while (k->cells)
    {
        w = k->from[0];
        k = kopiec_zdejmij(k);

        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            waga = g->tab[w]->tab[y]->waga;
            if (out->droga[w] + waga < out->droga[v])
            {
                out->droga[v] = out->droga[w] + waga;
                out->od[v] = w;
                k = kopiec_dodaj(k, w, v, waga);
            }
        }
    }
    return out;
}*/