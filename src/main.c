#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graf.h"
int main(int argc, char *argv[])
{
    srand(time(NULL));
    struct tablica_dynamiczna_w *tab_w;
    struct tablica_dynamiczna_k *tab_k;
    tab_w = init_tab_w();
    for (int x = 0; x < 170; x++)
        tab_w = dodaj_w(tab_w, init_w());

    tab_k = init_tab_k();
    for (int x = 0; x < 100; x++)
        tab_k = dodaj_k(tab_k, init_k(tab_w->tab[x], rand()));
    wypisz_tab_k(tab_k);
    return 0;
}