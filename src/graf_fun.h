#ifndef GRAF_FUN_H
#define GRAF_FUN_H

#include "graf.h"

struct bfs_out
{
    int *poprzednik, *odleglosc, *zwiedzone;
};

struct dijkstra_out
{
    int *od, cells;
    unsigned short int *odwiedzone;
    double *droga;
};

struct kopiec
{
    int *od;
    double *droga;
    int size, cells;
};

struct kolejka
{
    struct kolejka *next;
    int w;
};

struct kolejka *dodaj_w(struct kolejka *k, int w);
struct kolejka *zdejmij_w(struct kolejka *k);
struct kolejka *init_kolejka();
void free_kolejka(struct kolejka *k);

struct bfs_out *bfs(struct graf *g, int od);

struct kopiec *init_kopiec(unsigned int min_size);
struct kopiec *kopiec_dodaj(struct kopiec *k, int od, double droga);
struct kopiec *kopiec_zdejmij(struct kopiec *k);
void wypisz_kopiec(struct kopiec *k);
void free_kopiec(struct kopiec *k);

struct dijkstra_out *dijkstra(struct graf *g, int od);
#endif