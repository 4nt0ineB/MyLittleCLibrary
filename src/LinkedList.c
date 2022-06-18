

#include "../include/LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

int int_cmp(const void * x, const void * y){
    return (x == y) ? 0 : (x < y) ? -1 :  1;
}

void int_print(void * x){
    printf("%d", (int) *x);
}

LinkedCell * ll_new_cell(void * data, size_t size, LinkedListFunctions * f){
    LinkedCell * cell = (LinkedCell *) malloc(sizeof LinkedCell);
    if(!cell)
        return NULL;
    cell->data = (void *) malloc(size);
    if(!cell->data && size)
        return NULL;
    memcpy(cell->data, data, 1);
    return cell;
}

LinkedListFunctions * ll_functions(){
    LinkedListFunctions * f = (LinkedListFunctions *) malloc(sizeof LinkedListFunctions);
    f->ll_append = ll_append;
    f->ll_prepend = ll_prepend;
    f->ll_append = ll_append;
    f->ll_search = ll_search;
    f->ll_del = ll_del;
    f->ll_shift = ll_shift;
    f->ll_pop = ll_pop;

    /* int by default */
    f->cmp = int_cmp;
    f->ll_print = int_print;

    return f;
}

LinkedCell * ll_new_cell(void * data, size_t size, LinkedListFunctions * f){
    Lin
}