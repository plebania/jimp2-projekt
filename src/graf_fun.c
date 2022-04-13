#include "graf_fun.h"
#include <stdlib.h>
#include <math.h>
#include "stdio.h"

struct kolejka *dodaj_w(struct kolejka *k, int w)
{
    struct node *n = malloc(sizeof(struct node));
    if (!k->pierwszy)
    {
        k->pierwszy = n;
        k->pierwszy->nastepny = NULL;
        k->pierwszy->poprzedni = NULL;
        k->pierwszy->w = w;
        return k;
    }
    else if (!k->ostatni)
    {
        k->ostatni = n;
        k->ostatni->poprzedni = k->pierwszy;
        k->ostatni->nastepny = NULL;
        k->pierwszy->nastepny = k->ostatni;
        k->ostatni->w = w;
        return k;
    }
    n->nastepny = NULL;
    n->poprzedni = k->ostatni;
    n->w = w;
    k->ostatni->nastepny = n;
    k->ostatni = n;
    return k;
}

struct kolejka *zdejmij_w(struct kolejka *k)
{
    if (!k)
        return NULL;
    if (!k->pierwszy)
        return k;
    struct node *pom = NULL;
    pom = k->pierwszy->nastepny;
    free(k->pierwszy);

    k->pierwszy = pom;
    if (k->pierwszy)
        k->pierwszy->poprzedni = NULL;
    return k;
}

struct kolejka *init_kolejka()
{
    struct kolejka *k = malloc(sizeof(struct kolejka));
    k->pierwszy = NULL;
    k->ostatni = NULL;
    return k;
}

void wypisz_kolejka(struct kolejka *k)
{
    struct node *pom = k->pierwszy;
    while (pom)
    {
        printf("%d ", pom->w);
        pom = pom->nastepny;
    }
}

void free_kolejka(struct kolejka *k)
{
    struct node *pom = NULL;
    if (k)
    {
        while (k->pierwszy)
        {
            pom = k->pierwszy->nastepny;
            free(k->pierwszy);
            k->pierwszy = pom;
        }
        free(k);
    }
}

struct bfs_out *init_bfs_out(int cells)
{
    struct bfs_out *b = malloc(sizeof(struct bfs_out));
    b->poprzednik = malloc(sizeof(int) * cells);
    b->zwiedzone = malloc(sizeof(int) * cells);
    return b;
}

void free_bfs_out(struct bfs_out *b)
{
    if (!b)
        return;
    if (b->poprzednik)
        free(b->poprzednik);
    if (b->zwiedzone)
        free(b->zwiedzone);
}

struct bfs_out *bfs(struct graf *g, int od)
{
    struct kolejka *k = init_kolejka();
    struct bfs_out *out = NULL;
    if (od >= g->cells)
        return out;
    out = init_bfs_out(g->cells);
    for (int x = 0; x < g->cells; x++)
    {
        // out->odleglosc[x] = INFINITY;
        out->poprzednik[x] = 0;
        out->zwiedzone[x] = 0;
    }
    // out->odleglosc[od] = 0;
    k = dodaj_w(k, od);
    int w, v;
    while (k->pierwszy)
    {
        w = k->pierwszy->w;
        k = zdejmij_w(k);

        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            if (out->zwiedzone[v] == 0)
            {
                out->zwiedzone[v] = 1;
                // out->odleglosc[v] = out->odleglosc[w] + 1;
                out->poprzednik[v] = w;
                k = dodaj_w(k, v);
            }
        }
        out->zwiedzone[w] = 2;
    }
    free_kolejka(k);
    return out;
}

struct kopiec *init_kopiec(unsigned int min_size)
{
    struct kopiec *k = malloc(sizeof(struct kopiec));
    k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    k->size = size;
    k->od = malloc(sizeof(int) * size);
    k->droga = malloc(sizeof(double) * size);
    return k;
}

struct kopiec *kopiec_dodaj(struct kopiec *k, int od, double waga)
{
    int i, j;
    i = k->cells;
    k->cells++;
    if (k->cells >= k->size)
    {
        k->size *= 2;
        k->droga = realloc(k->droga, k->size);
        k->od = realloc(k->od, k->size);
    }
    j = (i - 1) / 2;
    while (i > 0 && k->droga[j] > waga)
    {
        k->droga[i] = k->droga[j];
        k->od[i] = k->od[j];
        i = j;
        j = (i - 1) / 2;
    }
    k->droga[i] = waga;
    k->od[i] = od;
    return k;
}

struct kopiec *kopiec_zdejmij(struct kopiec *k)
{
    int i = 0, j = 1, pom;
    double v;
    if (k->cells)
    {
        k->cells--;
        v = k->droga[k->cells];
        pom = k->od[k->cells];
        while (j < k->cells)
        {
            if (j + 1 < k->cells && k->droga[j + 1] < k->droga[j])
                j++;
            if (v <= k->droga[j])
                break;
            k->droga[i] = k->droga[j];
            k->od[i] = k->od[j];
            i = j;
            j = j * 2 + 1;
        }
        k->droga[i] = v;
        k->od[i] = pom;
    }

    return k;
}

void wypisz_kopiec(struct kopiec *k)
{
    printf("cells:%d\n", k->cells);
    for (int x = 0; x < k->cells; x++)
        printf("%lf ", k->droga[x]);
}

void free_kopiec(struct kopiec *k)
{
    if (!k)
        return;
    if (k->od)
        free(k->od);
    if (k->droga)
        free(k->droga);
    free(k);
}

struct dijkstra_out *init_dijkstra_out(int cells)
{
    struct dijkstra_out *d = malloc(sizeof(struct dijkstra_out));
    d->od = malloc(sizeof(int) * cells);
    d->droga = malloc(sizeof(double) * cells);
    return d;
}

void free_dijkstra_out(struct dijkstra_out *d)
{
    if (!d)
        return;
    if (d->od)
        free(d->od);
    if (d->droga)
        free(d->droga);
    free(d);
}

struct dijkstra_out *dijkstra(struct graf *g, int od)
{

    struct kopiec *k = init_kopiec(g->cells);
    struct dijkstra_out *out = NULL;

    if (od >= g->cells)
        return out;

    out = init_dijkstra_out(g->cells);

    out->cells = g->cells; // TODO sprawdz czy ma sens dla grafow nie spojnych
    for (int x = 0; x < g->cells; x++)
        out->droga[x] = INFINITY;

    k = kopiec_dodaj(k, od, 0);
    out->od[od] = od;
    out->droga[od] = 0;
    int w, v;
    double waga;

    while (k->cells)
    {
        w = k->od[0];
        k = kopiec_zdejmij(k);
        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            waga = g->tab[w]->tab[y]->waga;
            if (out->droga[w] + waga < out->droga[v])
            {
                out->droga[v] = out->droga[w] + waga;
                out->od[v] = w;
                k = kopiec_dodaj(k, v, out->droga[v]);
            }
        }
    }
    free_kopiec(k);
    return out;
}