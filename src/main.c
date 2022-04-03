#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "graf.h"
#include "zapisz.h"
#include "graf_fun.h"
#include "arg_pars.h"

int main(int argc, char *argv[])
{

    srand(time(NULL));
    return arg_parse(argc, argv);
}