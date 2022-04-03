#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "graf.h"
#include "zapisz.h"
#include "graf_fun.h"
#include "arg_pars.h"
int czy_double(char *napis)
{
    if (!isdigit(napis[0]))
        return 0;
    int x;
    for (x = 1; napis[x] != '\0'; x++)
        if (!isdigit(napis[x]) && napis[x] != '.')
            return 0;
    if (x > 0 && napis[x - 1] == '.')
        return 0;
    return 1;
}

int czy_int(char *napis)
{
    for (int x = 0; napis[x] != '\0'; x++)
        if (!isdigit(napis[x]))
            return 0;
    return 1;
}

void zachowanie_make(FILE *plik, int w, int h, double min_wag, double max_wag)
{
    printf("make %d  %d  %f  %f\n", w, h, min_wag, max_wag);
    struct graf *g = stworz_graf(w, h, min_wag, max_wag, 0);
    g->w = w;
    g->h = h;
    zapisz_graf(plik, g);
    free_graf(g);
}

void zachowanie_path(FILE *plik, int from_x, int from_y, int to_x, int to_y)
{
    printf("path %d %d %d %d", from_x, from_y, to_x, to_y);
}

void zachowanie_check(FILE *plik)
{
    printf("check");
}

int arg_parse(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Za mała ilość argumentów, nie mamy jeszcze instrukcji\n");
        return 1;
    }
    FILE *out_or_in;

    if (strcmp(argv[1], "make") == 0)
    {
        int w, h;
        out_or_in = fopen(argv[2], "w");
        if (argc < 5)
        {
            fprintf(stderr, "Niepoprawna ilosc argumnetow\n");
            return 1;
        }

        if (strcmp(argv[1], "make") == 0)
        {
            int poz_par = 0; // poz_par - o ile miejsc przesuniete sa parametry od polecenia
            double min_wag = 0, max_wag = 1;
            if (argc < 5)
            {
                printf("za mało argumentów wywołania\n");
                return 1;
            }
            // Szukam argumentów
            for (int x = 3; x < argc - 1; x++)
            {
                if (strcmp(argv[x], "--weight_min") == 0)
                {
                    if (czy_double(argv[x + 1]))
                    {
                        poz_par += 2;
                        min_wag = atof(argv[x + 1]);
                        x++;
                    }
                    else
                    {
                        printf("Po argumencie --weight_min spodziewana jest wartość\n");
                        return 1;
                    }
                }
                else if (strcmp(argv[x], "--weight_max") == 0)
                {
                    if (czy_double(argv[x + 1]))
                    {
                        poz_par += 2;
                        max_wag = atof(argv[x + 1]);
                        x++;
                    }
                    else
                    {
                        printf("Po argumencie --weight_max spodziewana jest wartość\n");
                        return 1;
                    }
                }
                else
                    break;
            }
            // polecenie postaci graph make plik [arg]... val val
            if (czy_int(argv[3 + poz_par]))
            {
                if (czy_int(argv[4 + poz_par]))
                {
                    w = atoi(argv[3 + poz_par]);
                    h = atoi(argv[4 + poz_par]);
                }
                else
                {
                    fprintf(stderr, "Nie podano parametru height\n");
                    return 1;
                }
            }
            else if (czy_int(argv[4 + poz_par]) && czy_int(argv[6 + poz_par]))
            {
                // polecenie postaci graph make plik [arg]... {w | width} val {h | height} val
                if (strcmp(argv[3 + poz_par], "width") == 0 || strcmp(argv[3 + poz_par], "w") == 0)
                {
                    if ((strcmp(argv[5 + poz_par], "height") == 0 || strcmp(argv[5 + poz_par], "h") == 0))
                    {
                        w = atoi(argv[4 + poz_par]);
                        h = atoi(argv[6 + poz_par]);
                    }
                }
                // polecenie postaci graph make plik [arg]... {h | height} val {w | width} val
                else if (strcmp(argv[5 + poz_par], "width") == 0 || strcmp(argv[5 + poz_par], "w") == 0)
                {
                    if ((strcmp(argv[3 + poz_par], "height") == 0 || strcmp(argv[3 + poz_par], "h") == 0))
                    {
                        w = atoi(argv[4 + poz_par]);
                        h = atoi(argv[6 + poz_par]);
                    }
                }
                else if (argc != 7 + poz_par)
                    printf("Bledne argumenty wywołania, instrukcja\n");
            }
            zachowanie_make(out_or_in, w, h, min_wag, max_wag);
        }
        else if (strcmp(argv[1], "check") == 0)
        {
            out_or_in = fopen(argv[2], "r");
            srand(time(NULL));
            zachowanie_check(out_or_in);
            // struct graf *g = stworz_graf(val1, val2); // jeszcze nie ma zaimplementowanej funkcji wczytaj
        }
    }
    else if (strcmp(argv[1], "path") == 0)
    {
        int from_x, from_y, to_x, to_y;
        out_or_in = fopen(argv[2], "r");
        if (argc == 7)
        {
            if (czy_int(argv[3]) && czy_int(argv[4]) && czy_int(argv[5]) && czy_int(argv[6]))
            {
                from_x = atoi(argv[3]);
                from_y = atoi(argv[4]);
                to_x = atoi(argv[5]);
                to_y = atoi(argv[6]);
            }
            else
            {
                printf("Błędne argumenty wywołania\n");
                return 1;
            }
        }
        else if (argc == 11)
        {
            if (czy_int(argv[4]) && czy_int(argv[6]) && czy_int(argv[8]) && czy_int(argv[10]))
            {
                int byl_from_x = 0, byl_from_y = 0, byl_to_x = 0, byl_to_y = 0;
                for (int x = 3; x < 11; x += 2)
                {
                    if (strcmp(argv[x], "from_x") == 0)
                    {
                        if (byl_from_x)
                        {
                            printf("błąd, wymagane argumenty from_x, from_y, to_x, to_y, bez powtórzeń\n");
                            return 1;
                        }
                        byl_from_x = 1;
                        from_x = atoi(argv[x + 1]);
                    }
                    else if (strcmp(argv[x], "from_y") == 0)
                    {

                        if (byl_from_y)
                        {
                            printf("błąd, wymagane argumenty from_x, from_y, to_x, to_y, bez powtórzeń\n");
                            return 1;
                        }
                        byl_from_y = 1;
                        from_y = atoi(argv[x + 1]);
                    }
                    else if (strcmp(argv[x], "to_x") == 0)
                    {
                        if (byl_to_x)
                        {
                            printf("błąd, wymagane argumenty from_x, from_y, to_x, to_y, bez powtórzeń\n");
                            return 1;
                        }
                        byl_to_x = 1;
                        to_x = atoi(argv[x + 1]);
                    }
                    else if (strcmp(argv[x], "to_y") == 0)
                    {
                        if (byl_to_y)
                        {
                            printf("błąd, wymagane argumenty from_x, from_y, to_x, to_y, bez powtórzeń\n");
                            return 1;
                        }
                        byl_to_y = 1;
                        to_y = atoi(argv[x + 1]);
                    }
                    else
                    {
                        printf("błąd, wymagane argumenty from_x, from_y, to_x, to_y, bez powtórzeń\n");
                        return 1;
                    }
                }
            }
            else
            {
                printf("błąd, po from_x, from_y, to_x, to_y oczekiwana jest watość parametru typu double\n");
                return 1;
            }
        }
        else
        {
            printf("Błędne argumenty, instruckja\n");
            return 1;
        }
        zachowanie_path(out_or_in, from_x, from_y, to_x, to_y);
    }
    else
    {
        fprintf(stderr, "Blad, brak zprecyzowanego dzialania programu\n");
        return 1;
    }
    return 0;
}