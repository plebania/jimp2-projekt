#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "graf.h"
#include "zapisz.h"
#include "graf_fun.h"

int main(int argc, char *argv[])
{
    FILE *out_or_in = strcmp(argv[1], "make") == 0 ? fopen(argv[2], "w") : fopen(argv[2], "r");
    int val1 = atoi(argv[3]);
    int val2 = atoi(argv[4]);
    // double w_min = argc > 4 ? atof(argv[5]) : 0.0;
    // double w_max = argc > 5 ? atof(argv[6]) : 1.0;

    printf("%s %s %s\n", argv[0],argv[1],argv[2]);
    int q = strcmp(argv[1], "make") == 0 ? 1 : 2;
    printf("%d", q );

    if (val1 <= 0 || val2 <= 0)
    {
        fprintf(stderr, "Parametry na szerokosc i wysokosc nie moga byc ujmne\n");
        return 1;
    }

    if(strcmp(argv[1], "make") == 0 || strcmp(argv[1], "path") == 0 || strcmp(argv[1], "check") == 0)
    {
        if(strcmp(argv[1], "make") == 0)
        {
            if (argc > 0 && argc < 5)
            {
                fprintf(stderr, "Niepoprawna ilosc argumnetow\n");
                return 1;
            }

            if (argc >= 5)
            {
                srand(time(NULL));
                struct graf *g = stworz_graf(val1, val2);
                zapisz_graf(out_or_in, g);

                /*for (int x = 0; x < g->cells; x++)
                {
                    printf(" ");
                    for (int y = 0; y < g->tab[x]->cells; y++)
                        printf("[%d-%lf->%d]\n", x, g->tab[x]->tab[y]->waga, g->tab[x]->tab[y]->_do);
                    printf(" \n");
                }*/
                return 0;
            }
        }

        if(strcmp(argv[1], "path") == 0)
        {
            srand(time(NULL));
            struct graf *g = stworz_graf(val1, val2); // jeszcze nie ma zaimplementowanej funkcji wczytaj
            bfs(g, 0);
        }

    } else {
        fprintf(stderr, "Blad, brak zprecyzowanego dzialania programu\n");
        return 1;
    }


}
