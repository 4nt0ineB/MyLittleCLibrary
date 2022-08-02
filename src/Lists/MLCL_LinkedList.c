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

#include "../../include/Lists/MLCL_LinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

LinkedCell * linked_list_builder(const void * data, LinkedListDescriptor * descriptor){
    LinkedCell * cell;
    cell = (LinkedCell *) calloc(1, sizeof(LinkedCell));
    assert(descriptor);
    if(!cell) return NULL;
    if(!(cell->data = descriptor->type_descriptor->copy(data))
        && descriptor->type_descriptor->data_size)
        return NULL;
    cell->d = descriptor;
    cell->next = NULL;
    return cell;
}

LinkedListDescriptor * linked_list_descriptor(){
    LinkedListDescriptor * ll_descriptor;
    ll_descriptor = (LinkedListDescriptor *) malloc(sizeof(LinkedListDescriptor));
    if(!ll_descriptor) return NULL;
    ll_descriptor->add_ = linked_list_add_;
    ll_descriptor->ordered_add = linked_list_ordered_add;
    ll_descriptor->reverse_ordered_add = linked_list_reverse_ordered_add;
    ll_descriptor->append = linked_list_append;
    ll_descriptor->prepend = linked_list_prepend;
    ll_descriptor->append = linked_list_append;
    ll_descriptor->insert = linked_list_insert;
    ll_descriptor->search = linked_list_search;
    ll_descriptor->remove = linked_list_remove;
    ll_descriptor->shift = linked_list_shift;
    ll_descriptor->pop = linked_list_pop;
    ll_descriptor->cell_print = linked_list_cell_print;
    ll_descriptor->print = linked_list_print;
    ll_descriptor->cell_fprint = linked_list_cell_fprint;
    ll_descriptor->fprint = linked_list_fprint;
    ll_descriptor->cell_free = linked_list_cell_free;
    ll_descriptor->free = linked_list_free;
    ll_descriptor->to_dot = linked_list_to_dot;
    /* Held type */
    ll_descriptor->type_descriptor = NULL;
    /* ... */
    ll_descriptor->length = 1; /*<! For the descriptor to exists at least one cell exists */
    return ll_descriptor;
}

LinkedCell * new_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *)){
    LinkedListDescriptor * lld;
    if(!type_manifest) return NULL;
    lld = linked_list_descriptor();
    if(!lld) return NULL;
    lld->type_descriptor = new_type_descriptor(type_manifest);
    return linked_list_builder(data, lld);
}

int linked_list_add_(LinkedList * ll, const void * data, int (*cmp) (const void *, const void *)){
    LinkedCell * new_cell;
    /* End of list OR Inside the list but inferior to the current cell */
    if(!*ll) return 0;
    if(cmp(data, (*ll)->data)){
        if(!(new_cell = linked_list_builder(data, (*ll)->d)))
            return 0;
        new_cell->next = *ll;
        (*ll) = new_cell;
        (*ll)->d->length++;
        return 1;
    }else if(!(*ll)->next){
        if(!(new_cell = linked_list_builder(data, (*ll)->d)))
            return 0;
        (*ll)->next = new_cell;
        (*ll)->d->length++;
        return 1;
    }
    return (*ll)->d->add_(&(*ll)->next, data, cmp);
}

int linked_list_ordered_add(LinkedList * ll, const void * data){
    if(!*ll) return 0;
    return (*ll)->d->add_(ll,  data, (*ll)->d->type_descriptor->lt);
}

int linked_list_reverse_ordered_add(LinkedList * ll, const void * data){
    if(!*ll) return 0;
    return (*ll)->d->add_(ll,  data, (*ll)->d->type_descriptor->ge);
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

int linked_list_remove(LinkedList * ll, const void * data){
    LinkedList tmp;
    if(!*ll) return 0;
    if((*ll)->d->type_descriptor->eq((*ll)->data, data)){
        tmp = *ll;
        *ll = tmp->next;
        tmp->next = NULL;
        tmp->d->free(&tmp);
        return 1;
    }
    return (*ll)->d->remove(&(*ll)->next, data);
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
        linked_list_descriptor_free(&tmp->d);
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
        linked_list_descriptor_free(&tmp->d);
        *ll = NULL;
    }
    free(tmp);
    return data;
}

void linked_list_descriptor_free(LinkedListDescriptor ** lld){
    if(!*lld) return;
    type_descriptor_free(&((*lld)->type_descriptor));
    free(*lld);
    *lld = NULL;
}

void linked_list_cell_free(LinkedCell ** ll){
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
        linked_list_descriptor_free(&(*ll)->d);
    free(*ll);
    *ll = NULL;
}

void linked_list_cell_print(LinkedCell * lc){
    if(lc) lc->d->cell_fprint(stdout, lc);
}

void linked_list_print(LinkedList ll){
    if(ll) ll->d->fprint(stdout, ll);
}

void linked_list_cell_fprint(FILE * stream, LinkedCell * lc){
    if(lc) lc->d->type_descriptor->fprint(stream, lc->data);
}

void linked_list_fprint(FILE * stream, LinkedList ll){
    if(!ll) return;
    ll->d->cell_fprint(stream, ll);
    printf(", ");
    ll->d->fprint(stream, ll->next);
}

static void _linked_list_to_dot(LinkedList ll, FILE * stream){
    while(ll){
        fprintf(stream, "  n%p [label=\"", (void *) ll);
        ll->d->cell_fprint(stream, ll);
        fprintf(stream, "\" color=\"#918d8d\"]\n");
        if(ll->next)
            fprintf(stream, " n%p -> n%p\n", (void *) ll, (void *) ll->next);
        ll = ll->next;
    }
}

void linked_list_to_dot(LinkedList ll, const char * dest_path){
    FILE * stream;
    if(!ll) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same]\n"
    );
    _linked_list_to_dot(ll, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}
