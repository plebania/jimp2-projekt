#include "graf_fun.h"
#include <stdlib.h>
#define INFTY 9999 //w math.h jest zdefiniowana
#include "stdio.h"

struct kolejka
{
struct kolejka *next;
int w;
};

struct kolejka *dodaj_w(struct kolejka *k, int w)
{
struct kolejka *n_k=malloc(sizeof(struct kolejka));
n_k->next=k;
n_k->w=w;
return n_k;
}

struct kolejka *zdejmij_w(struct kolejka *k)
    {
    struct kolejka *pom=NULL;
    if (!k)
        return pom;
    pom=k->next;
    free(k);
    k=pom;
    return k;
    }



struct kolejka *init_kolejka()
{
    struct kolejka *k = malloc(sizeof(struct kolejka));
    k->next=NULL;
    k->w=-1;
    return k;
}

void free_kolejka(struct kolejka *k)
{
    struct kolejka *pom=NULL;
    if (k)
        {
        while(k->next)
            {
            pom=k->next;
            free(k);
            k=pom;
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
    out->odleglosc = malloc(sizeof(int) * (g->cells));
    out->zwiedzone = malloc(sizeof(int) * (g->cells));
    for (int x = 0; x < g->cells; x++)
    {
        out->odleglosc[x] = INFTY;
        out->poprzednik[x] = 0;
        out->zwiedzone[x] = 0;
    }
    out->odleglosc[od] = 0;
    k ->w= od;
    int w, v;
    while (k)
    {
        w=k->w;
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

struct kopiec
{
    int *od;
    double *droga;
    int size, cells;
};

struct kopiec *init_kopiec(int min_size)
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

struct kopiec *kopiec_dodaj(struct kopiec *k, int od, double droga)
{
    if (k->cells >= k->size)
    {
        k->size *= 2;
        k->od = realloc(k->od, sizeof(int) * k->size);
        k->droga = realloc(k->droga, sizeof(double) * k->size);
    }
    k->od[k->cells] = od;
    k->droga[k->cells] = droga;
    k->cells++;
    for (int x = k->cells - 1; x > 0;)
    {
        int pom = (x - 1) / 2;
        if (k->droga[x] < k->droga[pom])
        {
            int pom_od;
            double pom_droga;

            pom_od = k->od[pom];
            pom_droga = k->droga[pom];

            k->od[pom] = k->od[x];
            k->droga[pom] = k->droga[x];

            k->od[x] = pom_od;
            k->droga[x] = pom_droga;
        }
        else
            break;
        x = pom;
    }
    return k;
}

struct kopiec *kopiec_zdejmij(struct kopiec *k)
{
    double old_root = k->droga[0];
    k->droga[0] = k->droga[k->cells - 1];
    k->cells--;
    for (int x = 0; x < k->cells - 1;)
    {
        int pom1 = x * 2 + 1;
        double pom = k->droga[pom1];
        if (pom1 < k->cells - 1)
            if (k->droga[pom1 + 1] < pom)
            {
                pom1++;
                pom = k->droga[pom1];
            }

        if (k->droga[x] > pom)
        {
            double pom2 = k->droga[x];
            k->droga[x] = pom;
            k->droga[pom1] = pom2;
        }
        x = pom1;
    }
    return k;
    // return old_root;
}

void wypisz_kopiec(struct kopiec* k)
    {
    for (int x=0; x<k->cells; x++)
        {
            printf("%lf ", k->droga[x]);
            /*
        for (int y=x; y<x+x+1|| y<k->cells; y++)
            printf("%lf ", k->droga[y]);
        printf("\n");*/
        }
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
    
    out=malloc(sizeof(struct dijkstra_out));
    out->od = malloc(sizeof(int) * g->cells);
    out->droga = malloc(sizeof(double) * g->cells);
    out->odwiedzone=malloc(sizeof(unsigned short int)*g->cells);
    
    out->cells=g->cells; //TODO sprawdz czy ma sens dla grafow nie spojnych
    for (int x = 0; x < g->cells; x++)
        {
        out->droga[x] = INFTY;
        out->odwiedzone[x]=0;
        }
    k = kopiec_dodaj(k, od, 0);
    out->od[od] = 0;
    out->droga[od]=0;
    int w, v;
    double waga;
    
    while (k->cells)
    {
        w = k->od[0];
        k = kopiec_zdejmij(k);

        for (int y = 0; y < g->tab[w]->cells; y++)
        {
            v = g->tab[w]->tab[y]->_do;
            waga = g->tab[w]->tab[y]->waga;
            if ( out->droga[w] + waga < out->droga[v])  //TODO odwiedzone
            {
                out->droga[v] = out->droga[w] + waga;
                out->od[v] = w;
                out->odwiedzone[w]=2;
                out->odwiedzone[v]=1;
                k = kopiec_dodaj(k, v, waga);
            }
        }
    }
    free_kopiec(k);
    free(k);
    return out;
}