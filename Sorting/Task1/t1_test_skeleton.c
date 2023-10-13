#include "t1.h"
#include <stdio.h>

int main()
{
    int ARRAY_SIZE = 30;
    int asc[ARRAY_SIZE];
    fill_ascending(asc, ARRAY_SIZE);
    int des[ARRAY_SIZE];
    fill_descending(des, ARRAY_SIZE);
    int uni[ARRAY_SIZE];
    fill_uniform(uni, ARRAY_SIZE);
    int wdup[ARRAY_SIZE];
    fill_with_duplicates(wdup, ARRAY_SIZE);
    int woutdup[ARRAY_SIZE];
    fill_without_duplicates(woutdup, ARRAY_SIZE);

    return 0;
}