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

DoubleLinkedCell * double_linked_list_builder(const void * data, DoubleLinkedListDescriptor * descriptor){
    DoubleLinkedCell * cell;
    cell = (DoubleLinkedCell *) calloc(1, sizeof(DoubleLinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    cell->data = calloc(1, descriptor->type_descriptor->data_size);
    if(!cell->data && descriptor->type_descriptor->data_size) return NULL;
    memcpy(cell->data, data, descriptor->type_descriptor->data_size);
    cell->d = descriptor;
    cell->next = cell->prev = NULL;
    return cell;
}

DoubleLinkedListDescriptor * double_linked_list_descriptor(){
    DoubleLinkedListDescriptor * ll_descriptor;
    ll_descriptor = (DoubleLinkedListDescriptor *) malloc(sizeof(DoubleLinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->append = double_linked_list_append;
    ll_descriptor->prepend = double_linked_list_prepend;
    ll_descriptor->append = double_linked_list_append;
    ll_descriptor->insert = double_linked_list_insert;
    ll_descriptor->search = double_linked_list_search;
    ll_descriptor->extract = double_linked_list_extract;
    ll_descriptor->remove = double_linked_list_remove;
    ll_descriptor->shift = double_linked_list_shift;
    ll_descriptor->pop = double_linked_list_pop;
    ll_descriptor->filter = double_linked_list_filter;
    ll_descriptor->print = double_linked_list_print;
    ll_descriptor->cell_free = double_linked_list_cell_free;
    ll_descriptor->free = double_linked_list_free;
    ll_descriptor->to_dot = double_linked_list_to_dot;
    ll_descriptor->cell_print = double_linked_list_cell_print;
    ll_descriptor->print = double_linked_list_print;
    ll_descriptor->cell_fprint = double_linked_list_cell_fprint;
    ll_descriptor->fprint = double_linked_list_fprint;
    /* Held type */
    ll_descriptor->type_descriptor = NULL;
    /* ... */
    ll_descriptor->length = 1; /*<! For the descriptor to exists at least one cell exists */
    return ll_descriptor;
}

DoubleLinkedCell * new_double_linked_list(const void * data, TypeDescriptor * type_descriptor){
    DoubleLinkedListDescriptor * lld;
    if(!type_descriptor) return NULL;
    lld = double_linked_list_descriptor();
    if(!lld) return NULL;
    /* Define list type */
    lld->type_descriptor = type_descriptor;
    return double_linked_list_builder(data, lld);
}

int double_linked_list_prepend(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = double_linked_list_builder(data, (*ll)->d))) return 0;
    cell->next = *ll;
    *ll = cell;
    cell->next->prev = *ll;
    (*ll)->d->length++;
    return 1;
}

int double_linked_list_append(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if((*ll)->next)
        return (*ll)->d->append(&(*ll)->next, data);
    if(!(cell = double_linked_list_builder(data, (*ll)->d)))
        return 0;
    (*ll)->next = cell;
    cell->prev = *ll;
    (*ll)->d->length++;
    return 1;
}

int double_linked_list_insert(DoubleLinkedList * ll, const void * data){
    DoubleLinkedCell * cell;
    if(!*ll) return 0;
    if(!(cell = double_linked_list_builder(data, (*ll)->d))) return 0;
    cell->next = (*ll)->next;
    cell->next->prev = cell;
    cell->prev = *ll;
    (*ll)->next = cell;
    (*ll)->d->length++;
    return 1;
}

DoubleLinkedCell * double_linked_list_search(DoubleLinkedList ll, const void * data){
    if(!ll) return NULL;
    if(!ll->d->type_descriptor->cmp(ll->data, data))
        return ll;
    return ll->d->search(ll->next, data);
}

void * double_linked_list_extract(DoubleLinkedCell ** dlc){
    DoubleLinkedCell * tmp;
    void * data;
    if(!dlc) return NULL;
    tmp = *dlc;
    data = tmp->data;
    if(!tmp->prev){
        *dlc = tmp->next;
        if(*dlc)
            (*dlc)->prev = NULL;
    }else if(!tmp->next){
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    tmp->next = tmp->prev = NULL;
    tmp->d->length--;
    if(tmp->d->length == 0){
        double_linked_list_descriptor_free(&tmp->d);
        *dlc = NULL;
    }
    free(tmp);
    return data;
}

int double_linked_list_remove(DoubleLinkedList * ll, const void * data){
    if(!*ll) return 0;
    if(!((*ll)->d->type_descriptor->cmp((*ll)->data, data))){
        free((*ll)->d->extract(ll));
        return 1;
    }
    return (*ll)->d->remove(&(*ll)->next, data);
}

void * double_linked_list_shift(DoubleLinkedList * ll){
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
        double_linked_list_descriptor_free(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

void * double_linked_list_pop(DoubleLinkedList * ll){
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
        double_linked_list_descriptor_free(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

DoubleLinkedList * double_linked_list_filter(DoubleLinkedList * ll, int (* f) (const void *)){
    /* @Todo dll_filter definition */
    return NULL;
}

void double_linked_list_descriptor_free(DoubleLinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void double_linked_list_cell_free(DoubleLinkedCell ** ll){
    if(!*ll) return;
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* Decrease the length of the list from the descriptor it was linked to. */
    (*ll)->d->length--;
    free(*ll);
    *ll = NULL;
}

void double_linked_list_free(DoubleLinkedList * ll){
    if(!*ll) return;
    (*ll)->d->free(&(*ll)->next);
    (*ll)->d->type_descriptor->free_data(&(*ll)->data);
    /* The linked list will decrease of 1 elem. */
    (*ll)->d->length--;
    /* After that, the list may be empty. Thus, the descriptor could no longer exist. */
    if((*ll)->d->length == 0)
        double_linked_list_descriptor_free(&(*ll)->d);
    free(*ll);
    *ll = NULL;
}

void double_linked_list_cell_print(DoubleLinkedCell * dlc){
    double_linked_list_cell_fprint(stdout, dlc);
}

void double_linked_list_print(DoubleLinkedList dll){
    double_linked_list_fprint(stdout, dll);
}

void double_linked_list_cell_fprint(FILE * file, DoubleLinkedCell * dlc){
    if(!dlc) return;
    dlc->d->type_descriptor->fprint(file, dlc->data);
}
void double_linked_list_fprint(FILE * file, DoubleLinkedList dll){
    if(!dll) return;
    dll->d->cell_fprint(file, dll);
    printf(", ");
    dll->d->fprint(file, dll->next);
}

static void _double_linked_list_to_dot(DoubleLinkedList ll, FILE * file){
    while(ll){
        fprintf(file, "  n%p [label=\"", (void *) ll);
        ll->d->cell_fprint(file, ll);
        fprintf(file, "\"]\n");
        if(ll->next){
            fprintf(file, " n%p -> n%p\n", (void *) ll, (void *) ll->next);
            fprintf(file, " n%p -> n%p\n", (void *) ll->next, (void *) ll);
        }
        ll = ll->next;
    }
}

void double_linked_list_to_dot(DoubleLinkedList ll, const char * dest_path){
    FILE * file;
    if(!ll) return;
    file = fopen(dest_path, "w");
    if(!file)
        printf("Couldn't open a file\n");
    fprintf(file, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    _double_linked_list_to_dot(ll, file);
    fprintf(file, "}\n");
    fclose(file);
}

