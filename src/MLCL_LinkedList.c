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

LinkedCell * linked_list_builder(const void * data, LinkedListDescriptor * descriptor){
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

LinkedListDescriptor * linked_list_descriptor(){
    LinkedListDescriptor * ll_descriptor;
    ll_descriptor = (LinkedListDescriptor *) malloc(sizeof(LinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->append = linked_list_append;
    ll_descriptor->prepend = linked_list_prepend;
    ll_descriptor->append = linked_list_append;
    ll_descriptor->insert = linked_list_insert;
    ll_descriptor->search = linked_list_search;
    ll_descriptor->del = linked_list_del;
    ll_descriptor->shift = linked_list_shift;
    ll_descriptor->pop = linked_list_pop;
    ll_descriptor->filter = linked_list_filter;
    ll_descriptor->print_cell = linked_list_print_cell;
    ll_descriptor->print = linked_list_print;
    ll_descriptor->fprint_cell = linked_list_fprint_cell;
    ll_descriptor->fprint = linked_list_fprint;
    ll_descriptor->free_cell = linked_list_free_cell;
    ll_descriptor->free = linked_list_free;
    /* Held type */
    ll_descriptor->type_descriptor = NULL;
    /* ... */
    ll_descriptor->length = 1; /*<! For the descriptor to exists at least one cell exists */
    return ll_descriptor;
}

LinkedCell * new_linked_list(const void * data, TypeDescriptor * type_descriptor){
    LinkedListDescriptor * lld;
    if(!type_descriptor) return NULL;
    lld = linked_list_descriptor();
    if(!lld) return NULL;
    lld->type_descriptor = type_descriptor;
    return linked_list_builder(data, lld);
}


int linked_list_prepend(LinkedList * ll, const void * data){
    LinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = linked_list_builder(data, (*ll)->d))) return 0;
    cell->next = *ll;
    *ll = cell;
    (*ll)->d->length++;
    return 1;
}

int linked_list_append(LinkedList * ll, const void * data){
    LinkedCell * cell;
    if(!*ll) return 0;
    if((*ll)->next)
        return (*ll)->d->append(&(*ll)->next, data);
    if(!(cell = linked_list_builder(data, (*ll)->d)))
        return 0;
    (*ll)->next = cell;
    (*ll)->d->length++;
    return 1;
}

int linked_list_insert(LinkedList * ll, const void * data){
    LinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = linked_list_builder(data, (*ll)->d))) return 0;
    cell->next = (*ll)->next;
    (*ll)->next = cell;
    (*ll)->d->length++;
    return 1;
}


LinkedList linked_list_search(LinkedList ll, const void * data){
    if(!ll) return 0;
    if(!ll->d->type_descriptor->cmp(ll->data, data))
        return ll;
    return ll->d->search(ll->next, data);
}

int linked_list_del(LinkedList * ll, const void * data){
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

void * linked_list_shift(LinkedList * ll){
    LinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    tmp = *ll;
    data = tmp->data;
    *ll = tmp->next;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        linked_list_free_descriptor(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

void * linked_list_pop(LinkedList * ll){
    LinkedCell * tmp;
    void * data;
    if(!*ll) return NULL;
    if((*ll)->next)
        return (*ll)->d->pop(&(*ll)->next);
    tmp = *ll;
    data = tmp->data;
    *ll = tmp->next;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        linked_list_free_descriptor(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

LinkedList * linked_list_filter(LinkedList * ll, int (* f) (const void *)){
    /* @Todo ll_filter definition */
    return NULL;
}

void linked_list_free_descriptor(LinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void linked_list_free_cell(LinkedCell ** ll){
    if(!*ll) return;
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* Decrease the length of the list from the descriptor it was linked to. */
    (*ll)->d->length--;
    free(*ll);
    *ll = NULL;
}

void linked_list_free(LinkedList * ll){
    if(!*ll) return;
    (*ll)->d->free(&(*ll)->next);
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* The linked list will decrease of 1 elem. */
    (*ll)->d->length--;
    /* After that, the list may be empty. Thus, the descriptor could no longer exist. */
    if((*ll)->d->length == 0)
        linked_list_free_descriptor(&(*ll)->d);
    free(*ll);
    *ll = NULL;
}

void linked_list_print_cell(LinkedCell * lc){
    if(!lc) return;
    lc->d->type_descriptor->print(lc->data);
}

void linked_list_print(LinkedList ll){
    if(!ll) return;
    ll->d->print_cell(ll);
    printf(", ");
    ll->d->print(ll->next);
}

void linked_list_fprint_cell(FILE * file, LinkedCell * lc){
    if(!lc) return;
    lc->d->type_descriptor->fprint(file, lc->data);
}

void linked_list_fprint(FILE * file, LinkedList ll){
    if(!ll) return;
    ll->d->fprint_cell(file, ll);
    printf(", ");
    ll->d->fprint(file, ll->next);
}
