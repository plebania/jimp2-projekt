#ifndef GRAF_FUN_H
#define GRAF_FUN_H

#include "graf.h"

struct bfs_out
{
    int *poprzednik, *odleglosc, *zwiedzone;
};

struct bfs_out *bfs(struct graf *g, int od);
#endif