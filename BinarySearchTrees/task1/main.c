#include<stdio.h>
#include<stdlib.h>
#include "bst.h"

int main(){
    char *data = "jndbajdfbierbakaerjhb\0";

    printf("he;lp");
    tree_print_sorted(create_bst(data));


    return 0;
}
