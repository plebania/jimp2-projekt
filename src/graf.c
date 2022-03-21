#include "graf.h"
#include <stdlib.h>
#include <stdio.h>
#define INIT_K_SIZE 4
unsigned int ostatni_w = 0;

struct wierzcholek *init_w()
{
    struct wierzcholek *w = malloc(sizeof(struct wierzcholek *));
    w->krawedzie = init_tab_k(INIT_K_SIZE);
    w->nr = ostatni_w++;
    return w;
}

struct wierzcholek *w_dodaj_k(struct wierzcholek *od, struct wierzcholek *_do, double waga)
{
    od->krawedzie = dodaj_k(od->krawedzie, init_k(_do, waga));
    return od;
}

struct tablica_dynamiczna_w *dodaj_w(struct tablica_dynamiczna_w *tab_w, struct wierzcholek *w)
{
    if (tab_w->cells >= tab_w->size)
    {
        tab_w->size *= 2;
        tab_w->tab = realloc(tab_w->tab, sizeof(struct wierzcholek *) * tab_w->size);
    }
    tab_w->tab[tab_w->cells] = w;
    tab_w->cells++;
    return tab_w;
}

struct tablica_dynamiczna_w *dodaj_n_w(struct tablica_dynamiczna_w *tab_w, int n) // dodaj n wierzcholkow
{
    for (int x = 0; x < n; x++)
    {
        if (tab_w->cells >= tab_w->size)
        {
            tab_w->size *= 2;
            tab_w->tab = realloc(tab_w->tab, sizeof(struct wierzcholek *) * tab_w->size);
        }
        tab_w->tab[tab_w->cells] = init_w();
        tab_w->cells++;
    }
    return tab_w;
}

struct tablica_dynamiczna_w *init_tab_w(unsigned int min_size)
{
    struct tablica_dynamiczna_w *tab_w = malloc(sizeof(struct tablica_dynamiczna_w *));
    tab_w->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    tab_w->size = size;
    printf("%d\n", size);
    tab_w->tab = malloc(sizeof(struct wierzcholek *) * size);
    return tab_w;
}

void wypisz_tab_w(struct tablica_dynamiczna_w *tab_w)
{
    printf("[");
    for (int x = 0; x < tab_w->cells - 1; x++)
        printf("%d,", tab_w->tab[x]->nr);
    printf("%d]", tab_w->tab[tab_w->cells - 1]->nr);
}

struct krawedz *init_k(struct wierzcholek *w, double waga)
{
    struct krawedz *k = malloc(sizeof(struct krawedz *));
    k->waga = waga;
    k->_do = w;
    return k;
}

struct tablica_dynamiczna_k *dodaj_k(struct tablica_dynamiczna_k *tab_k, struct krawedz *k)
{
    if (tab_k->cells >= tab_k->size)
    {
        tab_k->size *= 2;
        tab_k->tab = realloc(tab_k->tab, sizeof(struct krawedz *) * tab_k->size);
    }
    tab_k->tab[tab_k->cells] = k;
    tab_k->cells++;
    return tab_k;
}

struct tablica_dynamiczna_k *init_tab_k(unsigned int min_size)
{
    struct tablica_dynamiczna_k *tab_k = malloc(sizeof(struct tablica_dynamiczna_k *));
    tab_k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    tab_k->size = size;
    tab_k->tab = malloc(sizeof(struct krawedz *) * size);
    return tab_k;
}

void wypisz_tab_k(struct tablica_dynamiczna_k *tab_k)
{
    printf("[");
    for (int x = 0; x < tab_k->cells - 1; x++)
        printf("(%lf, %d),", tab_k->tab[x]->waga, tab_k->tab[x]->_do->nr);
    printf("(%lf, %d)]", tab_k->tab[tab_k->cells - 1]->waga, tab_k->tab[tab_k->cells - 1]->_do->nr);
}

// TODO 1x1
struct graf *stworz_graf(int w, int h)
{
    struct graf *g = NULL;
    if (w < 1 || h < 1)
        return g;
    g = malloc(sizeof(struct graf *));
    g->wierzcholki = init_tab_w(w * h);
    g->wierzcholki = dodaj_n_w(g->wierzcholki, w * h);
    if (w == 1 || h == 1)
    {
        for (int x = 1; x < w * h - 2; x++)
        {
            g->wierzcholki->tab[x]->krawedzie = dodaj_k(g->wierzcholki->tab[x]->krawedzie, init_k(g->wierzcholki->tab[x - 1], rand()));
            g->wierzcholki->tab[x]->krawedzie = dodaj_k(g->wierzcholki->tab[x]->krawedzie, init_k(g->wierzcholki->tab[x + 1], rand()));
        }
        g->wierzcholki->tab[0]->krawedzie = dodaj_k(g->wierzcholki->tab[0]->krawedzie, init_k(g->wierzcholki->tab[1], rand()));
        g->wierzcholki->tab[w * h - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[0]->krawedzie, init_k(g->wierzcholki->tab[w * h - 2], rand()));
        return g;
    }

    g->wierzcholki->tab[0]->krawedzie = dodaj_k(g->wierzcholki->tab[0]->krawedzie, init_k(g->wierzcholki->tab[1], rand()));
    g->wierzcholki->tab[0]->krawedzie = dodaj_k(g->wierzcholki->tab[0]->krawedzie, init_k(g->wierzcholki->tab[w], rand()));

    g->wierzcholki->tab[w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[w - 1]->krawedzie, init_k(g->wierzcholki->tab[w - 2], rand()));
    g->wierzcholki->tab[w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[w - 1]->krawedzie, init_k(g->wierzcholki->tab[2 * w - 1], rand()));

    g->wierzcholki->tab[(h - 1) * w]->krawedzie = dodaj_k(g->wierzcholki->tab[(h - 1) * w]->krawedzie, init_k(g->wierzcholki->tab[(h - 1) * w + 1], rand()));
    g->wierzcholki->tab[(h - 1) * w]->krawedzie = dodaj_k(g->wierzcholki->tab[(h - 1) * w]->krawedzie, init_k(g->wierzcholki->tab[(h - 2) * w], rand()));

    g->wierzcholki->tab[h * w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[h * w - 1]->krawedzie, init_k(g->wierzcholki->tab[h * w - 2], rand()));
    g->wierzcholki->tab[h * w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[h * w - 1]->krawedzie, init_k(g->wierzcholki->tab[(h - 1) * w - 1], rand()));
    for (int x = 1; x < w - 1; x++)
    {
        g->wierzcholki->tab[x]->krawedzie = dodaj_k(g->wierzcholki->tab[x]->krawedzie, init_k(g->wierzcholki->tab[x + 1], rand()));
        g->wierzcholki->tab[x]->krawedzie = dodaj_k(g->wierzcholki->tab[x]->krawedzie, init_k(g->wierzcholki->tab[x - 1], rand()));
        g->wierzcholki->tab[x]->krawedzie = dodaj_k(g->wierzcholki->tab[x]->krawedzie, init_k(g->wierzcholki->tab[x + w], rand()));

        g->wierzcholki->tab[x + (h - 1) * w]->krawedzie = dodaj_k(g->wierzcholki->tab[x + (h - 1) * w]->krawedzie, init_k(g->wierzcholki->tab[x + (h - 1) * w - 1], rand()));
        g->wierzcholki->tab[x + (h - 1) * w]->krawedzie = dodaj_k(g->wierzcholki->tab[x + (h - 1) * w]->krawedzie, init_k(g->wierzcholki->tab[x + (h - 1) * w + 1], rand()));
        g->wierzcholki->tab[x + (h - 1) * w]->krawedzie = dodaj_k(g->wierzcholki->tab[x + (h - 1) * w]->krawedzie, init_k(g->wierzcholki->tab[x + (h - 2) * w], rand()));

        for (int y = 1; y < h - 1; y++)
        {
            g->wierzcholki->tab[y * w + x]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w + x]->krawedzie, init_k(g->wierzcholki->tab[y * w + x + 1], rand()));
            g->wierzcholki->tab[y * w + x]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w + x]->krawedzie, init_k(g->wierzcholki->tab[y * w + x - 1], rand()));
            g->wierzcholki->tab[y * w + x]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w + x]->krawedzie, init_k(g->wierzcholki->tab[y * w + x + w], rand()));
            g->wierzcholki->tab[y * w + x]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w + x]->krawedzie, init_k(g->wierzcholki->tab[y * w + x - w], rand()));
        }
    }
    for (int y = 1; y < h - 1; y++)
    {
        g->wierzcholki->tab[y * w]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w]->krawedzie, init_k(g->wierzcholki->tab[y * w + 1], rand()));
        g->wierzcholki->tab[y * w]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w]->krawedzie, init_k(g->wierzcholki->tab[(y + 1) * w], rand()));
        g->wierzcholki->tab[y * w]->krawedzie = dodaj_k(g->wierzcholki->tab[y * w]->krawedzie, init_k(g->wierzcholki->tab[(y - 1) * w], rand()));

        g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie, init_k(g->wierzcholki->tab[(y + 1) * w - 2], rand()));
        g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie, init_k(g->wierzcholki->tab[(y + 2) * w - 1], rand()));
        g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie = dodaj_k(g->wierzcholki->tab[(y + 1) * w - 1]->krawedzie, init_k(g->wierzcholki->tab[y * w - 1], rand()));
    }
    return g;
}