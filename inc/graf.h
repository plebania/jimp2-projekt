#ifndef GRAF_H
#define GRAF_H

struct krawedz
{
    double waga;
    unsigned int _do;
};

struct td_krawedz // tablica dynamiczna krawedzi
{
    struct krawedz **tab;
    int size, cells; // size - ilosc przydzielonych komorek pamieci, cells - ilosc urzywanych kommorek
};

struct graf
{
    struct td_krawedz **tab;
    int size, cells;
};

struct krawedz *init_k(unsigned int _od, double waga);

struct td_krawedz *dodaj_k(struct td_krawedz *tab_k, struct krawedz *k);
struct td_krawedz *init_td_krawedz(unsigned int min_size);
void wypisz_td_krawedz(struct td_krawedz *tab_k);
void free_td_krawedz(struct td_krawedz *tab_k);

struct graf *init_graf(unsigned int wierzcholkow);
struct graf *stworz_graf(int w, int h, double min_wag, double max_wag, unsigned int psuc);
void free_graf(struct graf *g);

#endif