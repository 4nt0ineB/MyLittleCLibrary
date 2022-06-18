/*
  Created by antoine on 21/05/2022.
*/

#ifndef MYLITTLECLIBRARY_LINKEDLIST_H
#define MYLITTLECLIBRARY_LINKEDLIST_H

#include <stdlib.h>

typedef struct s_linked_cell {
    void * data;
    struct s_linked_list_functions * f;
} LinkedCell, * LinkedList;

typedef struct s_linked_list_functions {
    int (* cmp)(const void * x, const void * y);
    LinkedCell * (*ll_new_cell) (void * data, size_t size, struct s_linked_list_functions * f);
    int (*ll_prepend) (LinkedList * l, LinkedCell * cell);
    int (*ll_append) (LinkedList * l, LinkedCell * cell);
    int (*ll_search) (LinkedList * l, void * data);
    int (*ll_del) (LinkedList * l, LinkedCell * cell);
    int (*ll_shift) (LinkedList * l, LinkedCell * cell);
    int (*ll_pop) (LinkedList * l, LinkedCell * cell);
    void (*ll_print) (void *);
} LinkedListFunctions;


LinkedCell * ll_new_cell(void * data, size_t size, LinkedListFunctions * f);
int ll_prepend(LinkedList * l, LinkedCell * cell);
int ll_append(LinkedList * l, LinkedCell * cell);
int ll_search(LinkedList * l, void * data);
int ll_del(LinkedList * l, LinkedCell * cell);
int ll_shift(LinkedList * l, LinkedCell * cell);
int ll_pop(LinkedList * l, LinkedCell * cell);


/*
 * unshift ->        <- push
 * <-- shift         --> pop
 *
*/



#endif /* MYLITTLECLIBRARY_LINKEDLIST_H */
