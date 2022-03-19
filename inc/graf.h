#ifndef GRAF_H
#define GRAF_H

struct graf
{
    struct tablica_dynamiczna_w *wierzcholki;
};

struct krawedz
{
    double waga;
    struct wierzcholek *_do;
};

struct wierzcholek
{
    unsigned int nr;
    struct tablica_dynamiczna_k *krawedzie;
};

struct tablica_dynamiczna_w
{
    struct wierzcholek **tab;
    int size, cells;
};

struct tablica_dynamiczna_k
{
    struct krawedz **tab;
    int size, cells;
};

struct wierzcholek *init_w();

struct tablica_dynamiczna_w *dodaj_w(struct tablica_dynamiczna_w *tab_w, struct wierzcholek *w);
struct tablica_dynamiczna_w *init_tab_w();
void wypisz_tab_w(struct tablica_dynamiczna_w *tab_w);

struct krawedz *init_k(struct wierzcholek *w, double waga);

struct tablica_dynamiczna_k *dodaj_k(struct tablica_dynamiczna_k *tab_k, struct krawedz *k);
struct tablica_dynamiczna_k *init_tab_k();
void wypisz_tab_k(struct tablica_dynamiczna_k *tab_k);

#endif