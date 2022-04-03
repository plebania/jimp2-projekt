#include "graf.h"
#include <stdlib.h>
#include <stdio.h>
#define INIT_K_SIZE 4
#define BRAK_KR_PR 26.34 // szansa na nie stworzenie krawedzi w funkcji stworz graf przy parametrze psuc =1
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
    struct td_krawedz *tab_k = malloc(sizeof(struct td_krawedz));
    tab_k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    tab_k->size = size;
    tab_k->tab = malloc(sizeof(struct krawedz) * size);
    return tab_k;
}

void wypisz_td_krawedz(struct td_krawedz *tab_k)
{
    printf("[");
    for (int x = 0; x < tab_k->cells - 1; x++)
        printf("(%lf, %d),", tab_k->tab[x]->waga, tab_k->tab[x]->_do);
    printf("(%lf, %d)]", tab_k->tab[tab_k->cells - 1]->waga, tab_k->tab[tab_k->cells - 1]->_do);
}

void free_td_krawedz(struct td_krawedz *tab_k)
{
    for (int x = 0; x < tab_k->cells; x++)
        free(tab_k->tab[x]);
    free(tab_k);
}

struct graf *init_graf(unsigned int wierzcholkow)
{

    struct graf *g = NULL;
    g = malloc(sizeof(struct graf));
    g->tab = malloc(sizeof(struct td_krawedz) * wierzcholkow);
    unsigned int pom = 1;
    while (pom < wierzcholkow)
        pom *= 2;
    g->size = pom;
    g->cells = 0;
    g->w = 0;
    g->h = 0;
    return g;
}

struct td_krawedz **graf_dodaj_k(struct td_krawedz **tab, int x1, int x2, double waga, unsigned int psuc)
{
    if (psuc && (double)rand() / ((double)RAND_MAX + 1) * 100 < BRAK_KR_PR)
        return tab;
    tab[x1] = dodaj_k(tab[x1], init_k(x2, waga));
    tab[x2] = dodaj_k(tab[x2], init_k(x1, waga));
    return tab;
}

struct graf *stworz_graf(int w, int h, double min_wag, double max_wag, unsigned int psuc)
{
#define RAND_WAG min_wag + (double)rand() / ((double)RAND_MAX + 1) * (max_wag - min_wag)
    struct graf *g = NULL;
    if (w < 1 || h < 1)
        return g;
    g = init_graf(w * h);
    for (int x = 0; x < w * h; x++)
        g->tab[x] = init_td_krawedz(1);
    g->cells = w * h;
    if (w == 1 || h == 1)
    {
        for (int x = 0; x < w * h - 1; x++)
            g->tab = graf_dodaj_k(g->tab, x, x + 1, RAND_WAG, psuc);
        return g;
    }

    for (int x = 0; x < w - 1; x++)
    {
        for (int y = 0; y < h - 1; y++)
        {
            g->tab = graf_dodaj_k(g->tab, y * w + x, y * w + x + 1, RAND_WAG, psuc);
            g->tab = graf_dodaj_k(g->tab, y * w + x, (y + 1) * w + x, RAND_WAG, psuc);
        }
        g->tab = graf_dodaj_k(g->tab, (h - 1) * w + x, (h - 1) * w + x + 1, RAND_WAG, psuc);
    }
    for (int y = 0; y < h - 1; y++)
        g->tab = graf_dodaj_k(g->tab, (y + 1) * w - 1, (y + 2) * w - 1, RAND_WAG, psuc);

    return g;
}

void free_graf(struct graf *g)
{
    for (int x = 0; x < g->size; x++)
        if (g->tab[x] != NULL)
            free_td_krawedz(g->tab[x]);
    free(g->tab);
}