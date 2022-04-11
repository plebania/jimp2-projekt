#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "graf.h"
//#include "io.h"
//#include "graf_fun.h"
//#include "testy.h"
#include "arg_pars.h"

int main(int argc, char *argv[])
{
    // FILE *in = fopen(argv[1], "r");
    // FILE *out = fopen(argv[2], "w");
    srand(time(NULL));
    return arg_parse(argc, argv);

    // struct graf *g = wczytaj_graf(in);

    // zapisz_graf(out, g);
    // fclose(in);

    // int x = test1_kopiec(10, 2.0, 5.0);
    // printf("%d\n", x);

    // test1_kolejka(5);
}