#ifndef GRAF_FUN_H
#define GRAF_FUN_H

#include "graf.h"
struct stos
{
    int *tab, cells, size;
};

void bfs(struct graf *g, int od);
#endif