/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_CircularLinkedList.h"
#include <stdio.h>

CircularLinkedList new_cll(const void * data, TypeDescriptor * type_descriptor){
    LinkedListDescriptor * lld;
    CircularLinkedList cll;
    if(!type_descriptor) return NULL;
    lld = ll_descriptor();
    lld->type_descriptor = type_descriptor;
    cll = ll_builder(data, lld);
    if(!cll) return NULL;
    /* Circular */
    cll->next = cll;
    /* Override affected function */
    cll->d->append = cll_append;
    cll->d->free = cll_free;
    return cll;
}

int cll_append(LinkedList * cll, const void * data){
    LinkedCell * cell;
    LinkedCell * tmp;
    if(!*cll) return 0;
    tmp = (*cll)->next;
    while(tmp->next != *cll)
        tmp = tmp->next;
    if(!(cell = ll_builder(data, (*cll)->d)))
        return 0;
    cell->next = tmp->next;
    tmp->next = cell;
    (*cll)->d->length++;
    return 1;
}

void cll_free(CircularLinkedList * cll){
    CircularLinkedList tmp;
    CircularLinkedList tmp_2;
    if(!*cll) return;
    tmp = (*cll)->next;
    while(tmp != *cll){
        tmp_2 = tmp->next;
        tmp->d->type_descriptor->free_data(&tmp->data);
        free(tmp);
        tmp = tmp_2;
    }
    (*cll)->d->type_descriptor->free_data(&(*cll)->data);
    ll_free_descriptor(&(*cll)->d);
    free(*cll);
    *cll = NULL;
}
