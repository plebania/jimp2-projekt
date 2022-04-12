#include "graf_fun.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "stdio.h"

struct kolejka *dodaj_w(struct kolejka *k, int w)
{
    struct kolejka *n_k = malloc(sizeof(struct kolejka));
    n_k->next = k;
    n_k->w = w;
    return n_k;
}

struct kolejka *zdejmij_w(struct kolejka *k)
{
    struct kolejka *pom = NULL;
    if (!k)
        return pom;
    pom = k->next;
    free(k);
    k = pom;
    return k;
}

struct kolejka *init_kolejka()
{
    struct kolejka *k = malloc(sizeof(struct kolejka));
    k->next = NULL;
    k->w = -1;
    return k;
}

void free_kolejka(struct kolejka *k)
{
    struct kolejka *pom = NULL;
    if (k)
    {
        while (k->next)
        {
            pom = k->next;
            free(k);
            k = pom;
        }
        free(k);
    }
}

struct bfs_out *bfs(struct graf *g, int od)
{
    struct kolejka *k = init_kolejka();
    struct bfs_out *out = NULL;
    if (od >= g->cells) 
        return out;
    out = malloc(sizeof(struct bfs_out));
    out->poprzednik = malloc(sizeof(int) * (g->cells));
    out->odleglosc = malloc(sizeof(double) * (g->cells));
    out->zwiedzone = malloc(sizeof(int) * (g->cells));
    for (int x = 0; x < g->cells; x++)
    {
        out->odleglosc[x] = __DBL_MAX__;
        out->poprzednik[x] = 0;
        out->zwiedzone[x] = 0;
    }
    out->odleglosc[od] = 0;
    k->w = od;
    int w, v;
    while (k)
    {
        w = k->w;
        k = zdejmij_w(k);

        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            if (out->zwiedzone[v] == 0)
            {
                out->zwiedzone[v] = 1;
                out->odleglosc[v] = out->odleglosc[w] + 1;
                out->poprzednik[v] = w;
                k = dodaj_w(k, v);
            }
        }
        out->zwiedzone[w] = 2;
    }
    free_kolejka(k);
    return out;
}

struct kopiec *init_kopiec(unsigned int min_size)
{
    struct kopiec *k = malloc(sizeof(struct kopiec));
    k->cells = 0;
    unsigned int size = 1;
    while (size < min_size)
        size *= 2;
    k->size = size;
    k->od = malloc(sizeof(int) * size);
    k->droga = malloc(sizeof(double) * size);
    return k;
}

struct kopiec * kopiec_dodaj(struct kopiec *k, int od, double waga)
    {
    int i, j;
    i=k->cells;
    k->cells++;
    j=(i-1)/2;
    while (i>0 && k->droga[j]>waga)
        {
        k->droga[i]=k->droga[j];
        k->od[i]=k->od[j];
        i=j;
        j=(i-1)/2;
        }
    k->droga[i]=waga;
    k->od[i]=od;
    return k;
    }

struct kopiec* kopiec_zdejmij(struct kopiec *k)
    {
    int i=0,j=1, pom;
    double v;
    if (k->cells)
        {
        
        k->cells--;
        v=k->droga[k->cells];
        pom=k->od[k->cells];
        while (j<k->cells)
            {
            if (j+1<k->cells && k->droga[j+1]<k->droga[j])j++;
            if (v<=k->droga[j])break;
            k->droga[i]=k->droga[j];
            k->od[i]=k->od[j];
            i=j;
            j=j*2+1;
            }
            k->droga[i]=v;
            k->od[i]=pom;
        }
    
    return k;
    }


void wypisz_kopiec(struct kopiec *k)
{
    printf("cells:%d\n", k->cells);
    for (int x = 0; x < k->cells; x++)
        printf("%lf ", k->droga[x]);
}

void free_kopiec(struct kopiec *k)
{
    free(k->od);
    free(k->droga);
}

struct dijkstra_out *dijkstra(struct graf *g, int od)
{

    struct kopiec *k = init_kopiec(g->cells);
    struct dijkstra_out *out = NULL;

    if (od >= g->cells)
        return out;

    out = malloc(sizeof(struct dijkstra_out));
    out->od = malloc(sizeof(int) * g->cells);
    out->droga = malloc(sizeof(double) * g->cells);
    out->odwiedzone = malloc(sizeof(unsigned short int) * g->cells);

    out->cells = g->cells; // TODO sprawdz czy ma sens dla grafow nie spojnych
    for (int x = 0; x < g->cells; x++)
    {
        out->droga[x] = __DBL_MAX__;
        out->odwiedzone[x] = 0;
    }
    k = kopiec_dodaj(k, od, 0);
    out->od[od] = od;
    out->droga[od] = 0;
    int w, v;
    double waga;

    while (k->cells)
    {
        w = k->od[0];
        k = kopiec_zdejmij(k);
        // wypisz_kopiec(k);
        // printf("\nw %d\n", w);
        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            // printf("%d", v);
            waga = g->tab[w]->tab[y]->waga;
            if (out->droga[w] + waga < out->droga[v]) // TODO odwiedzone
            {
                out->droga[v] = out->droga[w] + waga;
                out->od[v] = w;
                out->odwiedzone[w] = 2;
                out->odwiedzone[v] = 1;
                k = kopiec_dodaj(k, v, waga);
            }
        }
    }
    free_kopiec(k);
    free(k);
    return out;
}