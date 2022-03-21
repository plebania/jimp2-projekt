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
    int size, cells; // size - ilosc przydzielonych komorek pamieci, cells - ilosc urzywanych kommorek
};

struct tablica_dynamiczna_k
{
    struct krawedz **tab;
    int size, cells; // size - ilosc przydzielonych komorek pamieci, cells - ilosc urzywanych kommorek
};

struct wierzcholek *init_w();
void free_wierzcholek(struct wierzcholek *w);

struct tablica_dynamiczna_w *dodaj_w(struct tablica_dynamiczna_w *tab_w, struct wierzcholek *w);
struct tablica_dynamiczna_w *dodaj_n_w(struct tablica_dynamiczna_w *tab_w, int n); // dodaj n wierzcholkow
struct tablica_dynamiczna_w *init_tab_w(unsigned int min_size);
void wypisz_tab_w(struct tablica_dynamiczna_w *tab_w);
void free_tablica_dynamicza_w(struct tablica_dynamiczna_w *tab_w);

struct krawedz *init_k(struct wierzcholek *w, double waga);

struct tablica_dynamiczna_k *dodaj_k(struct tablica_dynamiczna_k *tab_k, struct krawedz *k);
struct tablica_dynamiczna_k *init_tab_k(unsigned int min_size);
void wypisz_tab_k(struct tablica_dynamiczna_k *tab_k);
void free_tablica_dynamiczna_k(struct tablica_dynamiczna_k *tab_k);

struct graf *stworz_graf(int w, int h);
void free_graf(struct graf *g);

#endif