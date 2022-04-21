#ifndef ARG_PARS_H
#define ARG_PARS_H

int czy_double(char *napis);
int czy_int(char *napis);
void zachowanie_make(FILE *plik, int w, int h, double min_wag, double max_wag, unsigned int psuc);
void zachowanie_path(FILE *plik, int from, int to);
void zachowanie_check(FILE *plik);

int arg_parse(int argc, char *argv[]);
#endif