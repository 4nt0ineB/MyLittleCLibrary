/*
  Created by antoine on 21/05/2022.
*/

#ifndef MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_LINKEDLIST_H

#include <stdlib.h>
#include "../include/MLCL_Types.h"

typedef struct s_linked_cell {
    void * data;
    struct s_linked_list_descriptor * d;
    struct s_linked_cell * next;
} LinkedCell, * LinkedList;

typedef struct s_linked_list_descriptor {
    TypeDescriptor * type_descriptor;

    /* LinkedCell * (*ll_new_cell) (void * data, size_t size, struct LinkedListDescriptor * f); */
    int (*prepend) (LinkedList * l, const void * data);
    int (*append) (LinkedList * l, const void * data);
    int (*search) (LinkedList l, const void * data, LinkedCell * cell);
    int (*del) (LinkedList * l, const void * data);
    int (*shift) (LinkedList * l, LinkedCell * cell);
    int (*pop) (LinkedList * l, LinkedCell * cell);
    void (*print) (LinkedList l);
} LinkedListDescriptor;

LinkedListDescriptor * ll_descriptor();
LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor);
LinkedCell * new_ll(const void * data);
int ll_prepend(LinkedList * l, const void * data);
int ll_append(LinkedList * l, const void * data);
int ll_search(LinkedList l, const void * data, LinkedCell * cell);
int ll_del(LinkedList * l, const void * data);
int ll_shift(LinkedList * l, LinkedCell * cell);
int ll_pop(LinkedList * l, LinkedCell * cell);
void ll_print(LinkedList l);


/*
 * unshift ->        <- push
 * <-- shift         --> pop
 *
*/



#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
