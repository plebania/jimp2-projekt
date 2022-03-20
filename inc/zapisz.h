#ifndef ZAPISZ_H_
#define ZAPISZ_H_

#include <stdio.h>
#include "graf.h"

//void zapisz_graf(char sciezka[], int rozmiar_sciezki, FILE *out);

void zapisz_graf(FILE * out, struct graf *g);

#endif