/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
  */

#include "../../include/Lists/MLCL_DoubleLinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

DoubleLinkedCell * double_linked_list_builder(const void * data, DoubleLinkedListDescriptor * descriptor){
    DoubleLinkedCell * cell;
    cell = (DoubleLinkedCell *) calloc(1, sizeof(DoubleLinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    if(!(cell->data = descriptor->type_descriptor->copy(data))
       && descriptor->type_descriptor->data_size)
        return NULL;
    cell->d = descriptor;
    cell->next = cell->prev = NULL;
    return cell;
}

DoubleLinkedListDescriptor * double_linked_list_descriptor(){
    DoubleLinkedListDescriptor * ll_descriptor;
    ll_descriptor = (DoubleLinkedListDescriptor *) malloc(sizeof(DoubleLinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->add_ = double_linked_list_add_;
    ll_descriptor->ordered_add = double_linked_list_ordered_add;
    ll_descriptor->reverse_ordered_add = double_linked_list_reverse_ordered_add;
    ll_descriptor->append = double_linked_list_append;
    ll_descriptor->prepend = double_linked_list_prepend;
    ll_descriptor->append = double_linked_list_append;
    ll_descriptor->insert = double_linked_list_insert;
    ll_descriptor->search = double_linked_list_search;
    ll_descriptor->extract = double_linked_list_extract;
    ll_descriptor->remove = double_linked_list_remove;
    ll_descriptor->shift = double_linked_list_shift;
    ll_descriptor->pop = double_linked_list_pop;
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

DoubleLinkedCell * new_double_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *)){
    DoubleLinkedListDescriptor * lld;
    if(!type_manifest) return NULL;
    lld = double_linked_list_descriptor();
    if(!lld) return NULL;
    /* Define list type */
    lld->type_descriptor = new_type_descriptor(type_manifest);
    return double_linked_list_builder(data, lld);
}

int double_linked_list_add_(DoubleLinkedList * dll, const void * data, int (*cmp) (const void *, const void *)){
    DoubleLinkedCell * new_cell;
    /* End of list OR Inside the list but inferior to the current cell */
    if(!*dll) return 0;
    if(cmp(data, (*dll)->data)){
        if(!(new_cell = double_linked_list_builder(data, (*dll)->d)))
            return 0;
        new_cell->next = *dll;
        (*dll)->prev = new_cell;
        (*dll) = new_cell;
        (*dll)->d->length++;
        return 1;
    }else if(!(*dll)->next){
        if(!(new_cell = double_linked_list_builder(data, (*dll)->d)))
            return 0;
        (*dll)->next = new_cell;
        new_cell->prev = *dll;
        (*dll)->d->length++;
        return 1;
    }
    return (*dll)->d->add_(&(*dll)->next, data, cmp);
}

int double_linked_list_ordered_add(DoubleLinkedList * dll, const void * data){
    if(!*dll) return 0;
    return (*dll)->d->add_(dll,  data, (*dll)->d->type_descriptor->lt);
}

int double_linked_list_reverse_ordered_add(DoubleLinkedList * dll, const void * data){
    if(!*dll) return 0;
    return (*dll)->d->add_(dll,  data, (*dll)->d->type_descriptor->ge);
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
    if(dlc) dlc->d->cell_fprint(stdout, dlc);
}

void double_linked_list_print(DoubleLinkedList dll){
    if(dll) dll->d->fprint(stdout, dll);
}

void double_linked_list_cell_fprint(FILE * stream, DoubleLinkedCell * dlc){
    if(dlc) dlc->d->type_descriptor->fprint(stream, dlc->data);
}
void double_linked_list_fprint(FILE * stream, DoubleLinkedList dll){
    if(!dll) return;
    dll->d->cell_fprint(stream, dll);
    printf(", ");
    dll->d->fprint(stream, dll->next);
}

static void _double_linked_list_to_dot(DoubleLinkedList ll, FILE * stream){
    while(ll){
        fprintf(stream, "  n%p [label=\"", (void *) ll);
        ll->d->cell_fprint(stream, ll);
        fprintf(stream, "\"]\n");
        if(ll->next){
            fprintf(stream, " n%p -> n%p\n", (void *) ll, (void *) ll->next);
            fprintf(stream, " n%p -> n%p\n", (void *) ll->next, (void *) ll);
        }
        ll = ll->next;
    }
}

void double_linked_list_to_dot(DoubleLinkedList ll, const char * dest_path){
    FILE * stream;
    if(!ll) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    _double_linked_list_to_dot(ll, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}

