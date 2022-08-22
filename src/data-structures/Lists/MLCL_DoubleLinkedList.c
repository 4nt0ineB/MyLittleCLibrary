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

#include "../../../include/data-structures/Lists/MLCL_DoubleLinkedList.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/***************************************************
 * DoubleLinkedListNode
 ***************************************************/

DoubleLinkedListNode * new_double_linked_list_node(void *data){
    DoubleLinkedListNode *node;
    if(!data) return NULL;
    node = (DoubleLinkedListNode *) malloc(sizeof(DoubleLinkedListNode));
    if(!node) return NULL;
    node->data = data;
    node->prev = node->next = NULL;
    return node;
}

int double_linked_list_node_insert(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    if(!*self || !data) return 0;
    node = new_double_linked_list_node(data);
    if(!node) return 0;
    node->next = (*self)->next;
    node->next->prev = node;
    node->prev = *self;
    (*self)->next = node;
    return 1;
}

void * double_linked_list_node_extract(DoubleLinkedListNode **self){
    DoubleLinkedListNode * tmp;
    void *data;
    if(!self) return NULL;
    tmp = *self;
    data = tmp->data;
    if(!tmp->prev){
        *self = tmp->next;
        if(*self)
            (*self)->prev = NULL;
    }else if(!tmp->next){
        tmp->prev->next = NULL;
    }else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    tmp->next = tmp->prev = NULL;
    free(tmp);
    return data;
}

void double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!self || !stream || !data_fprint) return;
    data_fprint(stream, self->data);
}

void double_linked_list_node_print(const DoubleLinkedListNode *self, void (*data_fprint) (const void *, FILE *)){
    if(!self || !data_fprint) return;
    double_linked_list_node_fprint(self, stdout, data_fprint);
}

void double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data)){
    if(!*self) return;
    if(data_free_f)
        data_free_f((*self)->data);
    free(*self);
    *self = NULL;
}

/*
int double_linked_list_add_(DoubleLinkedList * dll, const void * data, int (*cmp) (const void *, const void *)){
    DoubleLinkedListNode * new_cell;
    *//* End of list OR Inside the list but inferior to the current cell *//*
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
}*/
/*
int double_linked_list_ordered_add(DoubleLinkedList * dll, const void * data){
    if(!*dll) return 0;
    return (*dll)->d->add_(dll,  data, (*dll)->d->type_descriptor->lt);
}

int double_linked_list_reverse_ordered_add(DoubleLinkedList * dll, const void * data){
    if(!*dll) return 0;
    return (*dll)->d->add_(dll,  data, (*dll)->d->type_descriptor->ge);
}*/

/***************************************************
 * DoubleLinkedList
 ***************************************************/

DoubleLinkedList * new_double_linked_list(void (*type_manifest) (TypeDescriptor *td)){
    DoubleLinkedList *list;
    if(!type_manifest) return NULL;
    list = (DoubleLinkedList *) malloc(sizeof(DoubleLinkedList));
    if(!list) return NULL;
    list->head = NULL;
    list->length = 0;
    list->td = new_type_descriptor(type_manifest);
    strcpy(list->separator, ", ");
    if(!list->td) return NULL;
    return list;
}

static int double_linked_list_prepend_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    if(!*self) return 0;
    node = new_double_linked_list_node(data);
    if(!node) return 0;
    node->next = *self;
    *self = node;
    node->next->prev = *self;
    return 1;
}
int double_linked_list_prepend(DoubleLinkedList *self, void *data){
    return double_linked_list_prepend_(&self->head, data) && ++self->length;
}

static int double_linked_list_append_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    if(!*self) return 0;
    if((*self)->next)
        return double_linked_list_append_(&(*self)->next, data);
    node = new_double_linked_list_node(data);
    if(!node) return 0;
    (*self)->next = node;
    node->prev = *self;
    return 1;
}
int double_linked_list_append(DoubleLinkedList *self, void *data){
    return double_linked_list_append_(&self->head, data) && ++self->length;
}

static void * double_linked_list_search_(const DoubleLinkedListNode *self, int (*filter) (const void *)){
    if(!self) return NULL;
    if(filter(self->data)) return self->data;
    return double_linked_list_search_(self->next, filter);
}
void * linked_list_search(const DoubleLinkedList *self, int (*filter) (const void *)){
    if(!self || !self->head || !filter) return NULL;
    return double_linked_list_search_(self->head, filter);
}

static int double_linked_list_remove_(DoubleLinkedListNode **self, int (*filter) (const void *), void (*data_free) (void *data)){
    if(!*self || !filter || !data_free) return 0;
    if(filter((*self)->data)){
        data_free(double_linked_list_node_extract(self));
        return 1;
    }
    return double_linked_list_remove_(&(*self)->next, filter, data_free);
}
int linked_list_remove(DoubleLinkedList *self, int (*filter) (const void *), void (*data_free) (void *data)){
    if(!self || !self->head || !filter || !data_free) return 0;
    return double_linked_list_remove_(&self->head, filter, data_free) && (--self->length || 1);
}

static int double_linked_list_remove_all_(DoubleLinkedListNode **self, int (*filter) (const void *), void (*data_free) (void *data)){
    DoubleLinkedListNode **tmp;
    int i;
    if(!*self || !filter || !data_free) return 0;
    i = 0;
    tmp = self;
    while(*tmp){
        if(filter((*tmp)->data)){
            data_free(double_linked_list_node_extract(self));
            i++;
        }
    }
    return i;
}
int linked_list_remove_all(DoubleLinkedList *self, int (*filter) (const void *), void (*data_free) (void *data)){
    int i;
    if(!self || !self->head || !filter || !data_free) return 0;
    i = double_linked_list_remove_all_(&self->head, filter, data_free);
    self->length -= i;
    return i;
}

void * double_linked_list_shift_(DoubleLinkedListNode **self){
    DoubleLinkedListNode * tmp;
    void * data;
    if(!*self) return NULL;
    tmp = *self;
    data = tmp->data;
    *self = tmp->next;
    tmp->next->prev = NULL;
    tmp->next = tmp->prev = NULL;
    free(tmp);
    return data;
}
void * double_linked_list_shift(DoubleLinkedList *self) {
    void *tmp;
    if(!self || !self->head) return NULL;
    tmp = double_linked_list_shift_(&self->head);
    if(tmp) --self->length;
    return  tmp;
}

static void * double_linked_list_pop_(DoubleLinkedListNode **self){
    DoubleLinkedListNode * tmp;
    void * data;
    if(!*self) return NULL;
    if((*self)->next)
        return double_linked_list_pop_(&(*self)->next);
    tmp = *self;
    data = tmp->data;
    tmp->prev->next = NULL;
    *self = tmp->next;
    tmp->next = NULL;
    free(tmp);
    return data;
}
void * double_linked_list_pop(DoubleLinkedList *self){
    void *tmp;
    if(!self || !self->head) return NULL;
    tmp = double_linked_list_pop_(&self->head);
    if(tmp) --self->length;
    return  tmp;
}

void double_linked_list_clear(DoubleLinkedList *self, void (*data_free) (void *data)){
    DoubleLinkedListNode *tmp, *tmp_2;
    if(!self || !self->head || !data_free) return;
    tmp = self->head;
    while(tmp){
        tmp_2 = tmp->next;
        double_linked_list_node_free(&tmp, data_free);
        self->length--;
        tmp = tmp_2;
    }
    self->head = NULL;
}

void double_linked_list_free(DoubleLinkedList **self){
    if(!*self) return;
    double_linked_list_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

void double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream){
    DoubleLinkedListNode *tmp;
    if(!self || !self->head) return;
    double_linked_list_node_fprint(self->head, stream, self->td->fprint);
    tmp = self->head->next;
    while(tmp){
        fprintf(stream, "%s", self->separator);
        double_linked_list_node_fprint(self->head, stream, self->td->fprint);
        tmp = tmp->next;
    }
}

void double_linked_list_print(const DoubleLinkedList *self){
    if(!self || !self->head) return;
    double_linked_list_fprint(self, stdout);
}

void double_linked_list_node_to_dot_(DoubleLinkedList *self, FILE * stream){
    DoubleLinkedListNode *tmp;
    if(!self) return;
    tmp = self->head;
    while(tmp){
        fprintf(stream, "  n%p [label=\"", (void *) tmp);
        double_linked_list_node_fprint(tmp, stream, self->td->fprint);
        fprintf(stream, "\"]\n");
        if(tmp->next){
            fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
            fprintf(stream, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
        }
        tmp = tmp->next;
    }
}

void double_linked_list_node_to_dot(DoubleLinkedList *self, const char * dest_path){
    FILE * stream;
    if(!self) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    double_linked_list_node_to_dot_(self, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}
