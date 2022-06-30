/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor){
    LinkedCell * cell;
    cell = (LinkedCell *) malloc(sizeof(LinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    cell->data = (void *) calloc(1, descriptor->type_descriptor->data_size);
    if(!cell->data && descriptor->type_descriptor->data_size) return NULL;
    memcpy(cell->data, data, sizeof(descriptor->type_descriptor->data_size));
    cell->d = descriptor;
    cell->next = NULL;
    return cell;
}

LinkedListDescriptor * ll_descriptor(){
    LinkedListDescriptor * ll_descriptor;
    ll_descriptor = (LinkedListDescriptor *) malloc(sizeof(LinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->append = ll_append;
    ll_descriptor->prepend = ll_prepend;
    ll_descriptor->append = ll_append;
    ll_descriptor->search = ll_search;
    ll_descriptor->del = ll_del;
    ll_descriptor->shift = ll_shift;
    ll_descriptor->pop = ll_pop;
    ll_descriptor->print = ll_print;
    ll_descriptor->free = ll_free;
    /* Held type */
    ll_descriptor->type_descriptor = NULL;
    /* ... */
    ll_descriptor->length = 1; /*<! For the descriptor to exists at least one cell exists */
    return ll_descriptor;
}

LinkedCell * new_ll(const void * data, TypeDescriptor * type_descriptor){
    LinkedListDescriptor * lld;
    lld = ll_descriptor();
    lld->type_descriptor = type_descriptor;
    return ll_builder(data, lld);
}


int ll_prepend(LinkedList * l, const void * data){
    LinkedCell * cell;
    if(!*l) return 0;
    if(!(cell = ll_builder(data, (*l)->d))) return 0;
    cell->next = *l;
    *l = cell;
    (*l)->d->length++;
    return 1;
}

int ll_append(LinkedList * l, const void * data){
    LinkedCell * cell;
    if(!*l) return 0;
    if((*l)->next)
        return (*l)->d->append(&(*l)->next, data);
    if(!(cell = ll_builder(data, (*l)->d)))
        return 0;
    (*l)->next = cell;
    (*l)->d->length++;
    return 1;

}

int ll_search(LinkedList l, const void * data){
    if(!l) return 0;
    if(!l->d->type_descriptor->cmp(l->data, data))
        return 1;
    return l->d->search(l->next, data);
}

int ll_del(LinkedList * l, const void * data){
    LinkedList tmp;
    if(!*l) return 0;
    if(!(*l)->d->type_descriptor->cmp((*l)->data, data)){
        tmp = *l;
        *l = tmp->next;
        tmp->next = NULL;
        tmp->d->free(&tmp);
        return 1;
    }
    return (*l)->d->del(&(*l)->next, data);
}

LinkedCell * ll_shift(LinkedList * l){
    return NULL;
}
LinkedCell * ll_pop(LinkedList * l){
    return NULL;
}

void ll_descriptor_free(LinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void ll_free(LinkedList * l){
    if(!*l) return;
    (*l)->d->free(&(*l)->next);
    (*l)->d->type_descriptor->free_data(&(*l)->data);
    /* The linked list will diminish of 1 elem*/
    (*l)->d->length--;
    /* After that, the list may be empty. Thus, the descriptor could no longer exist */
    if((*l)->d->length == 0)
        ll_descriptor_free(&(*l)->d);
    free(*l);
    (*l) = NULL;
}


void ll_print(LinkedList l){
    if(!l) return;
    l->d->type_descriptor->print(l->data);
    printf(", ");
    l->d->print(l->next);
}


