/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_CircularDoubleLinkedList.h"
#include "../include/MLCL_DoubleLinkedList.h"



DoubleLinkedCell * circular_double_linked_list_builder(const void * data, CircularDoubleLinkedListDescriptor * descriptor){
    DoubleLinkedCell * dlc;
    if((dlc = double_linked_list_builder(data, descriptor))){
        /* Circular */
        dlc->next = dlc;
        dlc->prev = dlc;
    }
    return dlc;
}

CircularDoubleLinkedListDescriptor * circular_double_linked_list_descriptor(){
    DoubleLinkedListDescriptor * dlld;
    if((dlld = double_linked_list_descriptor())){
        /* Override affected function */
        dlld->prepend = circular_double_linked_list_prepend;
        dlld->append = circular_double_linked_list_append;
        dlld->free = circular_double_linked_list_free;
        /*
        dlld->shift = circular_linked_list_shift;
        dlld->search = circular_linked_list_search;
        dlld->pop = circular_linked_list_pop;
        dlld->print = circular_linked_list_print;
        dlld->fprint = circular_linked_list_fprint;
        dlld->to_dot = circular_linked_list_to_dot;*/
    }
    return dlld;
}

DoubleLinkedCell * new_circular_double_linked_list(const void * data, TypeDescriptor * type_descriptor){
    CircularDoubleLinkedListDescriptor * cdlld;
    if(!type_descriptor) return NULL;
    if((cdlld = circular_double_linked_list_descriptor()))
        cdlld->type_descriptor = type_descriptor;
    return circular_double_linked_list_builder(data, cdlld);
}

int circular_double_linked_list_prepend(CircularDoubleLinkedList * cdll, const void * data){
    DoubleLinkedCell * cell;
    CircularDoubleLinkedList tmp;
    if(!*cdll)
        return 0;
    if(!(cell = double_linked_list_builder(data, (*cdll)->d)))
        return 0;
    /* Save the head */
    tmp = *cdll;
    /* Change the head */
    *cdll = cell;
    /* Link prev save cell to new head */
    tmp->prev->next = cell;
    /* link the head to previous head */
    cell->prev = tmp->prev;
    tmp->prev = cell;
    cell->next = tmp;
    cell->d->length++;
    return 1;
}

int circular_double_linked_list_append(CircularDoubleLinkedList * cdll, const void * data){
    DoubleLinkedCell * cell;
    if(!*cdll)
        return 0;
    if(!(cell = double_linked_list_builder(data, (*cdll)->d)))
        return 0;
    cell->prev = (*cdll)->prev;
    cell->next = *cdll;
    (*cdll)->prev->next = cell;
    (*cdll)->prev = cell;
    cell->d->length++;
    return 1;
}

void circular_double_linked_list_free(CircularDoubleLinkedList * cdll){
    CircularDoubleLinkedList tmp;
    CircularDoubleLinkedList tmp_2;
    if(!*cdll) return;
    tmp = (*cdll)->next;
    while(tmp != *cdll){
        tmp_2 = tmp->next;
        tmp->d->type_descriptor->free_data(&tmp->data);
        free(tmp);
        tmp = tmp_2;
    }
    (*cdll)->d->type_descriptor->free_data(&(*cdll)->data);
    double_linked_list_descriptor_free(&(*cdll)->d);
    free(*cdll);
    *cdll = NULL;
}