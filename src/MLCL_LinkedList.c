

#include "../include/MLCL_LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor){
    LinkedCell * cell = (LinkedCell *) malloc(sizeof(LinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    cell->data = (void *) malloc(descriptor->type_descriptor->data_size);
    if(!cell->data && descriptor->type_descriptor->data_size) return NULL;
    memcpy(cell->data, data, 1);
    cell->d = descriptor;
    cell->next = NULL;
    return cell;
}

LinkedListDescriptor * ll_descriptor(){
    LinkedListDescriptor * ll_descriptor = (LinkedListDescriptor *) malloc(sizeof(LinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->append = ll_append;
    ll_descriptor->prepend = ll_prepend;
    ll_descriptor->append = ll_append;
    ll_descriptor->search = ll_search;
    ll_descriptor->del = ll_del;
    ll_descriptor->shift = ll_shift;
    ll_descriptor->pop = ll_pop;
    ll_descriptor->print = ll_print;
    /* int by default */
    ll_descriptor->type_descriptor = new_t_desrciptor(int_manifest);
    if(!ll_descriptor->type_descriptor) return NULL;
    return ll_descriptor;
}

LinkedCell * new_ll(const void * data){
    return ll_builder(data, ll_descriptor());
}

int ll_prepend(LinkedList * l, const void * data){
    LinkedCell * cell;
    if(!*l) return 0;
    cell = ll_builder(data, (*l)->d);
    cell->next = *l;
    *l = cell;
    return 1;
}
int ll_append(LinkedList * l, const void * data){
    return 1;
}
int ll_search(LinkedList l, const void * data, LinkedCell * cell){
    return 1;
}
int ll_del(LinkedList * l, const void * data){
    return 1;
}
int ll_shift(LinkedList * l, LinkedCell * cell){
    return 1;
}
int ll_pop(LinkedList * l, LinkedCell * cell){
    return 1;
}

void ll_print(LinkedList l){
    if(!l) return;
    l->d->type_descriptor->print(l->data);
    printf(", ");
    l->d->print(l->next);
}


