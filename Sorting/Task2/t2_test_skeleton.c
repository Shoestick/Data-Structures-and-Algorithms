#include "t1.h"
#include "t2.h"
#include <stdio.h>

#define size 29

int main()
{
    int woutdup[size];
    fill_without_duplicates(woutdup, size);
    printArray(woutdup, size);

    insertionSort(woutdup, size);
    //quickSort(woutdup, size);

    printArray(woutdup, size);
    return 0;
}