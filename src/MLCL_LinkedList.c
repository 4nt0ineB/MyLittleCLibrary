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
#include <stdlib.h>

LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor){
    LinkedCell * cell;
    cell = (LinkedCell *) calloc(1, sizeof(LinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    cell->data = calloc(1, descriptor->type_descriptor->data_size);
    if(!cell->data && descriptor->type_descriptor->data_size) return NULL;
    memcpy(cell->data, data, descriptor->type_descriptor->data_size);
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
    ll_descriptor->filter = ll_filter;
    ll_descriptor->print = ll_print;
    ll_descriptor->free_cell = ll_free_cell;
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


int ll_prepend(LinkedList * ll, const void * data){
    LinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = ll_builder(data, (*ll)->d))) return 0;
    cell->next = *ll;
    *ll = cell;
    (*ll)->d->length++;
    return 1;
}

int ll_append(LinkedList * ll, const void * data){
    LinkedCell * cell;
    if(!*ll) return 0;
    if((*ll)->next)
        return (*ll)->d->append(&(*ll)->next, data);
    if(!(cell = ll_builder(data, (*ll)->d)))
        return 0;
    (*ll)->next = cell;
    (*ll)->d->length++;
    return 1;
}

int ll_search(LinkedList ll, const void * data){
    if(!ll) return 0;
    if(!ll->d->type_descriptor->cmp(ll->data, data))
        return 1;
    return ll->d->search(ll->next, data);
}

int ll_del(LinkedList * ll, const void * data){
    LinkedList tmp;
    if(!*ll) return 0;
    if(!(*ll)->d->type_descriptor->cmp((*ll)->data, data)){
        tmp = *ll;
        *ll = tmp->next;
        tmp->next = NULL;
        tmp->d->free(&tmp);
        return 1;
    }
    return (*ll)->d->del(&(*ll)->next, data);
}

void * ll_shift(LinkedList * ll){
    LinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    tmp = *ll;
    data = tmp->data;
    *ll = tmp->next;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0)
        ll_free_descriptor(&tmp->d);
    free(tmp);
    return data;
}

void * ll_pop(LinkedList * ll){
    LinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    if((*ll)->next)
        return (*ll)->d->pop(&(*ll)->next);
    tmp = *ll;
    data = tmp->data;
    *ll = NULL;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0)
        ll_free_descriptor(&tmp->d);
    free(tmp);
    return data;
}

LinkedList * ll_filter(LinkedList * ll, int (* f) (const void *)){

    return NULL;
}

void ll_free_descriptor(LinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void ll_free_cell(LinkedCell ** ll){
    if(!*ll) return;
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* Decrease the length of the list from the descriptor it was linked to. */
    (*ll)->d->length--;
    free(*ll);
    *ll = NULL;
}

void ll_free(LinkedList * ll){
    if(!*ll) return;
    (*ll)->d->free(&(*ll)->next);
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* The linked list will decrease of 1 elem. */
    (*ll)->d->length--;
    /* After that, the list may be empty. Thus, the descriptor could no longer exist. */
    if((*ll)->d->length == 0)
        ll_free_descriptor(&(*ll)->d);
    free(*ll);
    *ll = NULL;
}

void ll_print(LinkedList ll){
    if(!ll) return;
    ll->d->type_descriptor->print(ll->data);
    printf(", ");
    ll->d->print(ll->next);
}


