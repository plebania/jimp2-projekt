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

struct bfs_out *bfs(struct graf *g, int od);
struct dijkstra_out *dijkstra(struct graf *g, int od);
#endif