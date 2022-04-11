#ifndef IO_H_
#define IO_H_

#include <stdio.h>
#include "graf.h"

void zapisz_graf(FILE *out, struct graf *g);
struct graf *wczytaj_graf(FILE *in);
#endif