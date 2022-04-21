#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "graf.h"
#include "io.h"
#include "graf_fun.h"
#include "arg_pars.h"
#include "testy.h"
#define ANSI_KOLOR_CZERWONY "\x1b[31m"
#define ANSI_KOLOR_ZIELONY "\x1b[32m"
#define ANSI_KOLOR_RESET "\x1b[0m"

void instrukcja()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "INSTRUKCJA:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Streszczenie:\n");
    fprintf(stderr, "\tgraph make file_out {{width | w} | val1} {{height | h} val2  | val2} --weight_min val --weight_max val\n");
    fprintf(stderr, "\tgraph check file_in\n");
    fprintf(stderr, "\tgraph path file_in from_x val from_y val to_x val to_y val\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "graph make file_out width height [args]...\n");
    fprintf(stderr, "\tpolecenie tworzące graf o zadanych parametrach, zapisujące go do pliku file_out\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "graph check file_in\n");
    fprintf(stderr, "\tpolecenie zwraca logiczną wartość 1 jeśli graf w pliku wejściowym file_in jest koherentny i 0 jeśli nie jest\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "graph path file_in {from_x val1 from_y val2 to_x val3 to_y val4 | val1 val2 val3 val4}\n");
    fprintf(stderr, "\tpolecenie wypisujące najkrtótszą ścieżkę między podanymi w parametrach wierzchołkami grafu\n");
    fprintf(stderr, "\n");
}

int czy_double(char *napis)
{
    if (!isdigit(napis[0]) && napis[0] != '-')
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

void zachowanie_make(FILE *plik, int w, int h, double min_wag, double max_wag, unsigned int psuc)
{
    struct graf *g = stworz_graf(w, h, min_wag, max_wag, psuc);
    g->w = w;
    g->h = h;
    zapisz_graf(plik, g);
    free_graf(g);
}

void zachowanie_path(FILE *plik, int from, int to)
{
    struct graf *g = wczytaj_graf(plik);
    if (g == NULL)
        return;

    struct dijkstra_out *out = dijkstra(g, from);
    printf("Długość: %lf\nDroga: %d", out->droga[to], to);

    for (int x = to; x != from; x = out->od[x])
        printf("<-%d", out->od[x]);
    printf("\n");

    free_graf(g);
    free(out->droga);
    free(out->od);
    free(out);
}

void zachowanie_check(FILE *plik)
{
    struct graf *g = wczytaj_graf(plik);
    if (g == NULL)
        return;
    struct bfs_out *out;
    out = bfs(g, 0);

    for (int x = 0; x < g->cells; x++)
        if (out->zwiedzone[x] != 2)
        {
            printf("Graf niespojny\n");
            free_graf(g);
            return;
        }
    printf("Graf spojny\n");
    free_graf(g);
    free_bfs_out(out);
}

int parse_argumenty_make(int argc, char *argv[], int od, double *min_wag, double *max_wag, unsigned int *psuc)
{

    if (argc >= od + 3)
    {
        if (czy_double(argv[od + 1]) && czy_double(argv[od + 2]))
        {
            *min_wag = atof(argv[od + 1]);
            *max_wag = atof(argv[od + 2]);
            if (min_wag > max_wag)
            {
                double pom = *min_wag;
                *min_wag = *max_wag;
                *max_wag = pom;
            }
            if (argc > od + 3 && czy_int(argv[od + 3]))
                *psuc = atoi(argv[od + 3]);
        }
        else
        {
            for (int x = od + 1; x < argc; x += 2)
            {
                if (strcmp(argv[x], "-w_min") == 0 || strcmp(argv[x], "--weight_min") == 0)
                {
                    if (czy_double(argv[x + 1]))
                        *min_wag = atof(argv[x + 1]);
                    else
                    {
                        printf("błąd, po %s wymagana wartość parametru typu double", argv[x]);
                        return 1;
                    }
                }
                else if (strcmp(argv[x], "-w_max") == 0 || strcmp(argv[x], "--weight_max") == 0)
                {
                    if (czy_double(argv[x + 1]))
                        *max_wag = atof(argv[x + 1]);
                    else
                    {
                        printf("błąd, po %s wymagana wartość parametru typu double", argv[x]);
                        return 1;
                    }
                }
                else if (strcmp(argv[x], "-p") == 0 || strcmp(argv[x], "--psuc") == 0)
                {
                    *psuc = 1;
                    x--;
                }
                else
                {
                    printf("błąd, nieznany argument\n");
                    return 1;
                }
            }
        }
    }
    else if (argc > od + 1 && (strcmp(argv[od + 1], "--psuc") == 0 || strcmp(argv[od + 1], "-p") == 0))
        *psuc = 1;
    return 0;
}

int parse_make(int argc, char *argv[])
{
    int w, h;

    if (argc < 5)
    {
        fprintf(stderr, "Niepoprawna ilosc argumnetow\n");
        instrukcja();
        return 1;
    }
    FILE *out = NULL;
    out = fopen(argv[2], "w");
    if (!out)
    {
        fprintf(stderr, "Nie udało się utworzyć pliku wyjściowego\n");
        return 1;
    }
    double min_wag = 0, max_wag = 1;
    unsigned int psuc = 0;
    // polecenie postaci graph make plik [arg]... val val
    if (czy_int(argv[3]))
    {
        if (czy_int(argv[4]))
        {
            w = atoi(argv[3]);
            h = atoi(argv[4]);
            parse_argumenty_make(argc, argv, 4, &min_wag, &max_wag, &psuc);
        }
        else
        {
            fprintf(stderr, "Nie podano parametru height\n");

            fclose(out);
            instrukcja();
            return 1;
        }
    }
    else if (czy_int(argv[4]) && czy_int(argv[6]))
    {
        // polecenie postaci graph make plik [arg]... {w | width} val {h | height} val
        if (strcmp(argv[3], "width") == 0 || strcmp(argv[3], "w") == 0)
        {
            if ((strcmp(argv[5], "height") == 0 || strcmp(argv[5], "h") == 0))
            {
                w = atoi(argv[4]);
                h = atoi(argv[6]);
                parse_argumenty_make(argc, argv, 6, &min_wag, &max_wag, &psuc);
            }
            else
            {
                printf("Bledne argumenty wywołania, instrukcja\n");
                fclose(out);
                instrukcja();
                return 1;
            }
        }
        // polecenie postaci graph make plik [arg]... {h | height} val {w | width} val
        else if (strcmp(argv[5], "width") == 0 || strcmp(argv[5], "w") == 0)
        {
            if ((strcmp(argv[3], "height") == 0 || strcmp(argv[3], "h") == 0))
            {
                w = atoi(argv[4]);
                h = atoi(argv[6]);
                parse_argumenty_make(argc, argv, 6, &min_wag, &max_wag, &psuc);
            }
            else
            {
                printf("Bledne argumenty wywołania, instrukcja\n");
                fclose(out);
                instrukcja();
                return 1;
            }
        }
        else
        {
            printf("Bledne argumenty wywołania, instrukcja\n");
            fclose(out);
            instrukcja();
            return 1;
        }
    }
    else
    {
        printf("Bledne argumenty wywołania, instrukcja\n");
        fclose(out);
        instrukcja();
        return 1;
    }
    zachowanie_make(out, w, h, min_wag, max_wag, psuc);
    fclose(out);
    return 0;
}

int parse_check(char *argv[])
{
    FILE *in = fopen(argv[2], "r");
    if (!in)
    {
        fprintf(stderr, "nie udało się wczytać pliku wejściowego\n");
        return 1;
    }
    zachowanie_check(in);
    fclose(in);
    return 0;
}

int parse_path(int argc, char *argv[])
{
    int from, to;
    FILE *in = fopen(argv[2], "r");
    if (!in)
    {
        fprintf(stderr, "nie udało się wczytać pliku wejściowego\n");
        return 1;
    }
    if (argc == 5)
    {
        if (czy_int(argv[3]) && czy_int(argv[4]))
        {
            from = atoi(argv[3]);
            to = atoi(argv[4]);
        }
        else
        {
            printf("Błędne argumenty wywołania\n");
            fclose(in);
            instrukcja();
            return 1;
        }
    }
    else if (argc == 7)
    {
        if (czy_int(argv[4]) && czy_int(argv[6]))
        {
            if (strcmp(argv[3], "from") == 0 && strcmp(argv[5], "to") == 0)
            {
                from = atoi(argv[4]);
                to = atoi(argv[6]);
            }
            else if (strcmp(argv[3], "to") == 0 && strcmp(argv[5], "from") == 0)
            {
                to = atoi(argv[4]);
                from = atoi(argv[6]);
            }
            else
            {
                printf("błąd, niepoprawne parametry wywołania\n");
                fclose(in);
                instrukcja();
                return 1;
            }
        }
        else
        {
            printf("błąd, po from_x, from_y, to_x, to_y oczekiwana jest watość parametru typu double\n");
            fclose(in);
            instrukcja();
            return 1;
        }
    }
    else
    {
        printf("Błędne argumenty\n");
        fclose(in);
        instrukcja();
        return 1;
    }
    zachowanie_path(in, from, to);
    fclose(in);
    return 0;
}

int parse_test(int argc, char *argv[])
{
    for (int x = 2; x < argc; x++)
    {
        if (strcmp(argv[x], "--kopiec") == 0)
        {
            if (x + 3 >= argc)
            {
                printf("Błąd przy teście kopca wymagane są argumenty int ile, double od, double _od\n");
                instrukcja();
                return 1;
            }
            if (czy_int(argv[x + 1]) && czy_double(argv[x + 2]) && czy_double(argv[x + 2]))
                printf("%s\n", test1_kopiec(atoi(argv[x + 1]), atof(argv[x + 2]), atof(argv[x + 3])) == 0 ? ANSI_KOLOR_ZIELONY "OK" ANSI_KOLOR_RESET : ANSI_KOLOR_CZERWONY "BŁĄD" ANSI_KOLOR_RESET);
            else
            {
                printf("Błąd przy teście kopca wymagane są argumenty int ile, double od, double _od\n");
                instrukcja();
                return 1;
            }
            x += 3;
        }
        else if (strcmp(argv[x], "--kolejka") == 0)
        {
            if (x + 1 >= argc)
            {
                printf("Błąd przy teście kolejki wymagane są argumenty int ile\n");
                instrukcja();
                return 1;
            }
            if (czy_int(argv[x + 1]))
                printf("%s\n", test1_kolejka(atoi(argv[x + 1])) == 0 ? ANSI_KOLOR_ZIELONY "OK" ANSI_KOLOR_RESET : ANSI_KOLOR_CZERWONY "BŁĄD" ANSI_KOLOR_RESET);
            else
            {
                printf("Błąd przy teście kolejki wymagane są argumenty int ile\n");
                instrukcja();
                return 1;
            }
            x++;
        }
        else
        {
            instrukcja();
            return 1;
        }
    }
    return 0;
}

int arg_parse(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Za mała ilość argumentów\n");
        instrukcja();
        return 1;
    }

    if (strcmp(argv[1], "make") == 0)
        return parse_make(argc, argv);
    if (strcmp(argv[1], "check") == 0)
        return parse_check(argv);
    if (strcmp(argv[1], "path") == 0)
        return parse_path(argc, argv);
    if (strcmp(argv[1], "test") == 0)
        return parse_test(argc, argv);

    fprintf(stderr, "Błąd, brak zprecyzowanego dzialania programu\n");
    instrukcja();
    return 1;
}
