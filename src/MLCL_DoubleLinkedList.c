/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_DoubleLinkedList.h"

/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_DoubleLinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

DoubleLinkedCell * ll_builder(const void * data, DoubleLinkedListDescriptor * descriptor){
    DoubleLinkedCell * cell;
    cell = (DoubleLinkedCell *) calloc(1, sizeof(DoubleLinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    cell->data = calloc(1, descriptor->type_descriptor->data_size);
    if(!cell->data && descriptor->type_descriptor->data_size) return NULL;
    memcpy(cell->data, data, descriptor->type_descriptor->data_size);
    cell->d = descriptor;
    cell->next = NULL;
    cell->prev = NULL;
    return cell;
}

DoubleLinkedListDescriptor * ll_descriptor(){
    DoubleLinkedListDescriptor * ll_descriptor;
    ll_descriptor = (DoubleLinkedListDescriptor *) malloc(sizeof(DoubleLinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->append = dll_append;
    ll_descriptor->prepend = dll_prepend;
    ll_descriptor->append = dll_append;
    ll_descriptor->insert = dll_insert;
    ll_descriptor->search = dll_search;
    ll_descriptor->del = dll_del;
    ll_descriptor->shift = dll_shift;
    ll_descriptor->pop = dll_pop;
    ll_descriptor->filter = dll_filter;
    ll_descriptor->print = dll_print;
    ll_descriptor->free_cell = dll_free_cell;
    ll_descriptor->free = dll_free;
    /* Held type */
    ll_descriptor->type_descriptor = NULL;
    /* ... */
    ll_descriptor->length = 1; /*<! For the descriptor to exists at least one cell exists */
    return ll_descriptor;
}

DoubleLinkedCell * new_dll(const void * data, TypeDescriptor * type_descriptor){
    DoubleLinkedListDescriptor * lld;
    if(!type_descriptor) return NULL;
    lld = dll_descriptor();
    if(!lld) return NULL;
    lld->type_descriptor = type_descriptor;
    return dll_builder(data, lld);
}

int dll_prepend(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = ll_builder(data, (*ll)->d))) return 0;
    cell->next = *ll;
    *ll = cell;
    cell->next->prev = *ll;
    (*ll)->d->length++;
    return 1;
}

int dll_append(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if((*ll)->next)
        return (*ll)->d->append(&(*ll)->next, data);
    if(!(cell = ll_builder(data, (*ll)->d)))
        return 0;
    (*ll)->next = cell;
    cell->prev = *ll;
    (*ll)->d->length++;
    return 1;
}

int dll_insert(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = ll_builder(data, (*ll)->d))) return 0;
    cell->next = (*ll)->next;
    cell->next->prev = cell;
    cell->prev = *ll;
    (*ll)->next = cell;
    (*ll)->d->length++;
    return 1;
}

int dll_search(DoubleLinkedList ll, const void * data){
    if(!ll) return 0;
    if(!ll->d->type_descriptor->cmp(ll->data, data))
        return 1;
    return ll->d->search(ll->next, data);
}

int dll_del(DoubleLinkedList * ll, const void * data){
    DoubleLinkedList tmp;
    if(!*ll) return 0;
    if(!(*ll)->d->type_descriptor->cmp((*ll)->data, data)){
        tmp = *ll;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        tmp->next = tmp->prev = NULL;
        tmp->d->free(&tmp);
        return 1;
    }
    return (*ll)->d->del(&(*ll)->next, data);
}

void * dll_shift(DoubleLinkedList * ll){
    DoubleLinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    tmp = *ll;
    data = tmp->data;
    *ll = tmp->next;
    tmp->next->prev = NULL;
    tmp->next = tmp->prev = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        dll_free_descriptor(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

void * dll_pop(DoubleLinkedList * ll){
    DoubleLinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    if((*ll)->next)
        return (*ll)->d->pop(&(*ll)->next);
    tmp = *ll;
    data = tmp->data;
    tmp->prev->next = NULL;
    *ll = tmp->next;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        dll_free_descriptor(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

DoubleLinkedList * dll_filter(DoubleLinkedList * ll, int (* f) (const void *)){
    /* @Todo dll_filter definition */
    return NULL;
}

void dll_free_descriptor(DoubleLinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void dll_free_cell(DoubleLinkedCell ** ll){
    if(!*ll) return;
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* Decrease the length of the list from the descriptor it was linked to. */
    (*ll)->d->length--;
    free(*ll);
    *ll = NULL;
}

void dll_free(DoubleLinkedList * ll){
    if(!*ll) return;
    (*ll)->d->free(&(*ll)->next);
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* The linked list will decrease of 1 elem. */
    (*ll)->d->length--;
    /* After that, the list may be empty. Thus, the descriptor could no longer exist. */
    if((*ll)->d->length == 0)
        dll_free_descriptor(&(*ll)->d);
    free(*ll);
    *ll = NULL;
}

void dll_print(DoubleLinkedList ll){
    if(!ll) return;
    ll->d->type_descriptor->print(ll->data);
    printf(", ");
    ll->d->print(ll->next);
}


