/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Lists/MLCL_CircularDoubleLinkedList.h"
#include "../../../include/data-structures/Lists/MLCL_DoubleLinkedList.h"
#include <string.h>

/***************************************************
 * DoubleLinkedListNode
 ***************************************************/



DoubleLinkedListNode * new_circular_double_linked_list_node(void *data){
    DoubleLinkedListNode *node;
    node = new_double_linked_list_node(data);
    if(!node) return NULL;
    node->prev = node->next = node;
    return node;
}
int circular_double_linked_list_node_insert(DoubleLinkedListNode **self, void *data){
    return double_linked_list_node_insert(self, data);
}
void * circular_double_linked_list_node_extract(DoubleLinkedListNode **self){
    return double_linked_list_node_extract(self);
}
void circular_double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *)){
    double_linked_list_node_fprint(self, stream, data_fprint);
}
void circular_double_linked_list_node_print(const DoubleLinkedListNode *self, void (data_fprint) (const void *, FILE *)){
    circular_double_linked_list_node_fprint(self, stdout, data_fprint);
}
void circular_double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data)){
    double_linked_list_node_free(self, data_free_f);
}

/***************************************************
 * CircularDoubleLinkedList
 ***************************************************/


CircularDoubleLinkedList * new_circular_double_linked_list(void (*type_manifest) (TypeDescriptor *td)){
    CircularDoubleLinkedList *list;
    if(!type_manifest) return NULL;
    list = (CircularDoubleLinkedList *) malloc(sizeof(CircularDoubleLinkedList));
    if(!list) return NULL;
    list->head = NULL;
    list->length = 0;
    list->td = new_type_descriptor(type_manifest);
    strcpy(list->separator, ", ");
    if(!list->td) return NULL;
    return list;
}

static int circular_double_linked_list_append_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    node = new_circular_double_linked_list_node(data);
    if(!node) return 0;
    if(!*self){
        *self = node;
        return 1;
    }
    node->prev = (*self)->prev;
    node->next = *self;
    (*self)->prev->next = node;
    (*self)->prev = node;
    return 1;
}
int circular_double_linked_list_append(DoubleLinkedList *self, void *data){
    if(!self || !data) return 0;
    return circular_double_linked_list_append_(&self->head, data) && ++self->length;
}
/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/
static int circular_double_linked_list_prepend_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node, *tmp;

    node = new_circular_double_linked_list_node(data);
    if(!node) return 0;
    /* Save the head */
    tmp = *self;
    /* Change the head */
    *self = node;
    if(tmp){
        if((*self)->prev){
            /* Link prev save cell to new head */
            tmp->prev->next = node;
        }
        /* link the head to previous head */
        node->prev = tmp->prev;
        tmp->prev = node;
    }
    node->next = tmp;
    return 1;
}
int circular_double_linked_list_prepend(DoubleLinkedList *self, void *data){
    if(!self || !data) return 0;
    return circular_double_linked_list_prepend_(&self->head, data) && ++self->length;
}

/*static void * circular_double_linked_list_shift_(DoubleLinkedListNode **self){
    *//*DoubleLinkedListNode *tmp;
    void *data;
    if(!*self) return NULL;
    data = (*self)->data;
    tmp = *self;
    (*self)->next->prev = (*self)->prev;
    (*self)->prev->next = (*self)->next;
    *self = (*self)->next;*//*

    return NULL;
}*/
void * circular_double_linked_list_shift(DoubleLinkedList *self){
    if(!self || !self->head) return NULL;
    self->head = self->head->next;
    return circular_double_linked_list_pop(self);
    /*void *tmp;
    if(!self || !self->head) return NULL;
    tmp = circular_double_linked_list_shift_(&self->head);
    if(tmp)
        --self->head;

    return tmp;*/
}

static void * circular_double_linked_list_pop_(DoubleLinkedListNode **self){
    if(!*self) return NULL;
    return circular_double_linked_list_node_extract(&(*self)->prev);
}

void * circular_double_linked_list_pop(DoubleLinkedList *self){
    void *tmp;
    if(!self || !self->head) return NULL;
    tmp = circular_double_linked_list_pop_(&self->head);
    if(tmp) --self->length;
    return  tmp;
}
static void * circular_double_linked_list_search_(const DoubleLinkedListNode *self, const void *data, int (*filter) (const void *, const void *)){
    DoubleLinkedListNode *tmp;
    if(!self) return 0;
    if(filter(self->data, data))
        return self->data;

    tmp = self->next;
    while(tmp->next != self){
        if(filter(tmp->data, data))
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
void * circular_double_linked_list_search(const DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *)){
    if(!self || !self->head || !filter) return NULL;
    return circular_double_linked_list_search_(self->head, data, filter);
}

void circular_double_linked_list_fprint(const CircularDoubleLinkedList *self, FILE * stream){
    DoubleLinkedListNode *tmp;
    if(!self || !self->head || !stream) return;
    tmp = self->head;

    while(tmp->next != self->head){
        circular_double_linked_list_node_fprint(tmp, stream, self->td->fprint);
        fprintf(stream, "%s", self->separator);
        tmp = tmp->next;
    }
    circular_double_linked_list_node_fprint(tmp, stream, self->td->fprint);
}

void circular_double_linked_list_print(const CircularDoubleLinkedList *self){
    circular_double_linked_list_fprint(self, stdout);
}

void circular_double_linked_list_to_dot_(CircularDoubleLinkedList *self, FILE *stream){
    DoubleLinkedListNode *tmp;
    if(!self || !self->head || !stream) return;
    tmp = self->head;
    while(tmp->next != self->head){
        fprintf(stream, "  n%p [label=\"", (void *) tmp);
        circular_double_linked_list_node_fprint(tmp, stream, self->td->fprint);
        fprintf(stream, "\"]\n");
        fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
        fprintf(stream, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
        tmp = tmp->next;
    }
    fprintf(stream, "  n%p [label=\"", (void *) tmp);
    circular_double_linked_list_node_fprint(tmp, stream, self->td->fprint);
    fprintf(stream, "\"]\n");
    fprintf(stream, " n%p -> n%p\n", (void *) tmp, (void *) tmp->next);
    fprintf(stream, " n%p -> n%p\n", (void *) tmp->next, (void *) tmp);
}

void circular_double_linked_list_to_dot(CircularDoubleLinkedList *self, const char * path){
    FILE * stream;
    if(!self || !path) return;
    stream =fopen(path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                    "rankdir=\"LR\";\n"
                    "node [shape=square , height=.1, rank = same, color=\"#918d8d\"]\n"
    );
    circular_double_linked_list_to_dot_(self, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}

void circular_double_linked_list_clear(DoubleLinkedList *self, void (*data_free) (void *data)){
    DoubleLinkedListNode *tmp, *tmp_2;
    if(!self || !self->head) return;
    tmp = self->head->next;
    while(tmp != self->head){
        tmp_2 = tmp->next;
        circular_double_linked_list_node_free(&tmp, data_free);
        free(tmp);
        tmp = tmp_2;
    }
    circular_double_linked_list_node_free(&self->head, data_free);
    self->length = 0;
}
void circular_double_linked_list_free(DoubleLinkedList **self){
    if(!*self || !(*self)->head) return;
    circular_double_linked_list_clear(*self, (*self)->td->data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

/****************************************************************
 ****************************************************************/

/*int circular_double_linked_list_add_(CircularDoubleLinkedList * cll, const void *data, int (*cmp) (const void *, const void *)){
    DoubleLinkedListNode * new_cell;
    DoubleLinkedListNode * tmp;
    if(!*cll) return 0;
    *//* Prepend *//*
    if(cmp(data, (*cll)->data))
        return (*cll)->d->prepend(cll, data);
    *//* Insert *//*
    if(!(new_cell = double_linked_list_builder(data, (*cll)->d)))
        return 0;
    tmp = (*cll)->next;
    while(tmp != *cll){
        if(cmp(data, (*cll)->data)){
            new_cell->next = tmp->next;
            tmp->next->prev = new_cell;
            tmp->next = new_cell;
            (*cll)->d->length++;
            return 1;
        }
        tmp = tmp->next;
    }
    *//* after "last" cell *//*
    new_cell->next = tmp->next;
    tmp->next->prev = new_cell;
    tmp->next = new_cell;
    (*cll)->d->length++;
    return 1;
}*/


/*

    static int circular_double_linked_list_remove_(DoubleLinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
    static int circular_double_linked_list_remove_all_(DoubleLinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));

 */