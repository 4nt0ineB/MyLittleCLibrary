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
    cll->d->shift = cll_shift;
    cll->d->pop = cll_pop;
    cll->d->free = cll_free;
    cll->d->print = cll_print;
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

void * cll_shift(CircularLinkedList * ll){
    LinkedCell * tmp;
    LinkedCell * tmp_2;
    void * data;
    if(!*ll) return NULL;
    data = (*ll)->data;
    tmp = *ll;
    tmp_2 = (*ll)->next;
    **ll = *tmp_2;
    tmp->d->length--;
    if(tmp->d->length == 0){
        ll_free_descriptor(&tmp->d);
        *ll = NULL;
    }
    free(tmp_2);
    return data;
}

void * cll_pop(LinkedList * cll){
    LinkedCell * tmp;
    void * data;
    if(!*cll) return NULL;
    tmp = (*cll)->next;
    while(tmp->next != *cll)
        tmp = tmp->next;
    tmp = *cll;
    data = tmp->data;
    *cll = tmp->next;
    tmp->next = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        ll_free_descriptor(&tmp->d);
        *cll = NULL;
    }
    free(tmp);
    return data;
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

void cll_print(CircularLinkedList cll){
    CircularLinkedList tmp;
    if(!cll) return;
    tmp = cll->next;
    cll->d->print_cell(cll);printf(", ");
    while(tmp != cll){
        tmp->d->print_cell(tmp);printf(", ");
        tmp = tmp->next;
    }
}
