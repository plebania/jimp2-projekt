#include "graf.h"
#include <stdlib.h>
#include <stdio.h>
#define INIT_K_SIZE 4
unsigned int ostatni_w = 0;

struct krawedz *init_k(unsigned int _do, double waga)
{
    struct krawedz *k = malloc(sizeof(struct krawedz));
    k->waga = waga;
    k->_do = _do;
    return k;
}

struct td_krawedz *dodaj_k(struct td_krawedz *tab_k, struct krawedz *k)
{
    if (tab_k->cells >= tab_k->size)
    {
        tab_k->size *= 2;
        tab_k->tab = realloc(tab_k->tab, sizeof(struct krawedz) * tab_k->size);
    }
    tab_k->tab[tab_k->cells] = k;
    tab_k->cells++;
    return tab_k;
}

struct td_krawedz *init_td_krawedz(unsigned int min_size)
{
    struct td_krawedz *tab_k = malloc(sizeof(struct td_krawedz *));
    tab_k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    tab_k->size = size;
    tab_k->tab = malloc(sizeof(struct krawedz *) * size);
    return tab_k;
}

void wypisz_td_krawedz(struct td_krawedz *tab_k)
{
    printf("[");
    for (int x = 0; x < tab_k->cells - 1; x++)
        printf("(%lf, %d),", tab_k->tab[x]->waga, tab_k->tab[x]->_do);
    printf("(%lf, %d)]", tab_k->tab[tab_k->cells - 1]->waga, tab_k->tab[tab_k->cells - 1]->_do);
}

// void free_td_krawedz(struct td_krawedz *tab_k)
// {
//     for (int x = 0; x < tab_k->cells; x++)
//         free(tab_k->tab[x]);
//     free(tab_k);
// }

struct graf *init_graf(unsigned int wierzcholkow)
{

    struct graf *g = NULL;
    g = malloc(sizeof(struct graf));
    g->tab = malloc(sizeof(struct td_krawedz *) * wierzcholkow);
    unsigned int pom = 1;
    while (pom < wierzcholkow)
        pom *= 2;
    g->size = pom;
    g->cells = 0;
    return g;
}

struct graf *stworz_graf(int w, int h)
{

    struct graf *g = NULL;
    if (w < 1 || h < 1)
        return g;
    g = init_graf(w * h);
    for (int x = 0; x < w * h; x++)
        g->tab[x] = init_td_krawedz(1);
    g->cells = w * h;
    if (w == 1 || h == 1)
    {
        for (int x = 1; x < w * h - 1; x++)
        {
            g->tab[x] = dodaj_k(g->tab[x], init_k(x - 1, rand()));
            g->tab[x] = dodaj_k(g->tab[x], init_k(x + 1, rand()));
        }
        g->tab[0] = dodaj_k(g->tab[0], init_k(1, rand()));
        g->tab[w * h - 1] = dodaj_k(g->tab[0], init_k(w * h - 2, rand()));
        return g;
    }

    g->tab[0] = dodaj_k(g->tab[0], init_k(1, rand()));
    g->tab[0] = dodaj_k(g->tab[0], init_k(w, rand()));

    g->tab[w - 1] = dodaj_k(g->tab[w - 1], init_k(w - 2, rand()));
    g->tab[w - 1] = dodaj_k(g->tab[w - 1], init_k(2 * w - 1, rand()));

    g->tab[(h - 1) * w] = dodaj_k(g->tab[(h - 1) * w], init_k((h - 1) * w + 1, rand()));
    g->tab[(h - 1) * w] = dodaj_k(g->tab[(h - 1) * w], init_k((h - 2) * w, rand()));

    g->tab[h * w - 1] = dodaj_k(g->tab[h * w - 1], init_k(h * w - 2, rand()));
    g->tab[h * w - 1] = dodaj_k(g->tab[h * w - 1], init_k((h - 1) * w - 1, rand()));
    for (int x = 1; x < w - 1; x++)
    {
        g->tab[x] = dodaj_k(g->tab[x], init_k(x + 1, rand()));
        g->tab[x] = dodaj_k(g->tab[x], init_k(x - 1, rand()));
        g->tab[x] = dodaj_k(g->tab[x], init_k(x + w, rand()));

        g->tab[x + (h - 1) * w] = dodaj_k(g->tab[x + (h - 1) * w], init_k(x + (h - 1) * w - 1, rand()));
        g->tab[x + (h - 1) * w] = dodaj_k(g->tab[x + (h - 1) * w], init_k(x + (h - 1) * w + 1, rand()));
        g->tab[x + (h - 1) * w] = dodaj_k(g->tab[x + (h - 1) * w], init_k(x + (h - 2) * w, rand()));

        for (int y = 1; y < h - 1; y++)
        {
            g->tab[y * w + x] = dodaj_k(g->tab[y * w + x], init_k(y * w + x + 1, rand()));
            g->tab[y * w + x] = dodaj_k(g->tab[y * w + x], init_k(y * w + x - 1, rand()));
            g->tab[y * w + x] = dodaj_k(g->tab[y * w + x], init_k(y * w + x + w, rand()));
            g->tab[y * w + x] = dodaj_k(g->tab[y * w + x], init_k(y * w + x - w, rand()));
        }
    }
    for (int y = 1; y < h - 1; y++)
    {
        g->tab[y * w] = dodaj_k(g->tab[y * w], init_k(y * w + 1, rand()));
        g->tab[y * w] = dodaj_k(g->tab[y * w], init_k((y + 1) * w, rand()));
        g->tab[y * w] = dodaj_k(g->tab[y * w], init_k((y - 1) * w, rand()));

        g->tab[(y + 1) * w - 1] = dodaj_k(g->tab[(y + 1) * w - 1], init_k((y + 1) * w - 2, rand()));
        g->tab[(y + 1) * w - 1] = dodaj_k(g->tab[(y + 1) * w - 1], init_k((y + 2) * w - 1, rand()));
        g->tab[(y + 1) * w - 1] = dodaj_k(g->tab[(y + 1) * w - 1], init_k(y * w - 1, rand()));
    }

    return g;
}

// void free_graf(struct graf *g)
// {
//     for (int x = 0; x < g->size; x++)
//         if (g->tab[x] != NULL)
//             free_td_krawedz(g->tab[x]);
//     // free_tablica_dynamicza_w(g->wierzcholki);
//     free(g->tab);
// }