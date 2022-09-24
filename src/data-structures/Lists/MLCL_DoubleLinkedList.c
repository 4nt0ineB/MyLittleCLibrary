/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
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

/* --- Print --- */

void double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (*data_fprint) (const void *, FILE *)){
    if(!self || !stream || !data_fprint) return;
    data_fprint(self->data, stream);
}

void double_linked_list_node_print(const DoubleLinkedListNode *self, void (*data_fprint) (const void *, FILE *)){
    if(!self || !data_fprint) return;
    double_linked_list_node_fprint(self, stdout, data_fprint);
}

/* --- Free --- */

void double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data)){
    if(!*self) return;
    if(data_free_f)
        data_free_f((*self)->data);
    free(*self);
    *self = NULL;
}

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

/* --- Prepend --- */

static int double_linked_list_prepend_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    node = new_double_linked_list_node(data);
    if(!node) return 0;
    node->next = *self;
    *self = node;
    if(node->next)
        node->next->prev = *self;
    return 1;
}
int double_linked_list_prepend(DoubleLinkedList *self, void *data){
    return double_linked_list_prepend_(&self->head, data) && ++self->length;
}

/* --- Append --- */

static int double_linked_list_append_(DoubleLinkedListNode **self, void *data){
    DoubleLinkedListNode *node;
    if(!*self){
        node = new_double_linked_list_node(data);
        if(!node) return 0;
        *self = node;
        return 1;
    }

    return double_linked_list_append_(&(*self)->next, data);
}

int double_linked_list_append(DoubleLinkedList *self, void *data){
    return double_linked_list_append_(&self->head, data) && ++self->length;
}

/* --- Search --- */

static void * double_linked_list_search_(const DoubleLinkedListNode *self, Filter *filter){
    if(!self) return NULL;
    if(filter->evaluate(filter, self->data)) return self->data;
    return double_linked_list_search_(self->next, filter);
}

void * double_linked_list_search(const DoubleLinkedList *self, Filter *filter){
    if(!self || !self->head || !filter) return NULL;
    return double_linked_list_search_(self->head, filter);
}

/* --- Extract --- */

static void * double_linked_list_extract_(DoubleLinkedListNode **self, Filter *filter){
    if(!*self || !filter) return NULL;
    if(filter->evaluate(filter, (*self)->data))
        return double_linked_list_node_extract(self);
    return double_linked_list_extract_(&(*self)->next, filter);
}

void * double_linked_list_extract(DoubleLinkedList *self, Filter *filter){
    void *data;
    if(!self || !filter) return NULL;
    data = double_linked_list_extract_(&self->head, filter);
    if(data) --self->length;
    return data;
}

/* --- Extract all --- */

int double_linked_list_extract_all_(DoubleLinkedListNode **self, Filter *filter, DoubleLinkedList *extracted){
    DoubleLinkedListNode *next;
    if(!*self || !filter || !extracted) return 0;
    next = (*self)->next;
    printf("%d vs %d\n", 6, *(int*) (*self)->data);
    if(filter->evaluate(filter, (*self)->data)){
        double_linked_list_append(extracted, double_linked_list_node_extract(self));
    }
    double_linked_list_extract_all_(&next, filter, extracted);
    return 1;
}

DoubleLinkedList * double_linked_list_extract_all(DoubleLinkedList *self, Filter *filter){
    DoubleLinkedList *extracted_data;
    if(!self || !filter) return NULL;
    extracted_data = new_double_linked_list(self->td->manifest);
    if(extracted_data) self->length -= extracted_data->length;
    double_linked_list_extract_all_(&self->head, filter, extracted_data);
    return extracted_data;
}

/* --- Remove --- */

int double_linked_list_remove_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data)){
    void *data;
    if(!self || !self->head || !filter) return 0;
    data = double_linked_list_extract(self, filter);
    if(data_free) data_free(data);
    return data != NULL;
}

int double_linked_list_remove(DoubleLinkedList *self, Filter *filter){
    if(!self || !filter) return 0;
    return double_linked_list_remove_w(self, filter, self->td->data_free);
}

/* --- Remove all --- */

int double_linked_list_remove_all_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data)){
    DoubleLinkedList *extracted;
    int i;
    if(!self || !self->head || !filter) return 0;
    extracted = double_linked_list_extract_all(self, filter);
    i = 0;
    if(extracted){
        i = extracted->length;
        double_linked_list_free_w(&extracted, data_free);
    }
    return i;
}

int double_linked_list_remove_all(DoubleLinkedList *self, Filter *filter){
    if(!self || !self->head || !filter) return 0;
    return double_linked_list_remove_all_w(self, filter, self->td->data_free);
}

/* --- Shift--- */

void * double_linked_list_shift_(DoubleLinkedListNode **self){
    DoubleLinkedListNode * tmp;
    void *data;
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

/* --- Pop--- */

static void * double_linked_list_pop_(DoubleLinkedListNode **self){
    DoubleLinkedListNode * tmp;
    void *data;
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

/* --- Clear --- */

void double_linked_list_clear_w(DoubleLinkedList *self, void (*data_free) (void *data)){
    DoubleLinkedListNode *tmp,  *tmp_2;
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

void double_linked_list_clear(DoubleLinkedList *self){
    if(self)
        double_linked_list_clear_w(self, self->td->data_free);
}

/* --- Free --- */

void double_linked_list_free_w(DoubleLinkedList **self, void (data_free) (void *)){
    if(!*self) return;
    double_linked_list_clear_w(*self, data_free);
    type_descriptor_free(&(*self)->td);
    free(*self);
    *self = NULL;
}

void double_linked_list_free(DoubleLinkedList **self){
    if(*self)
        double_linked_list_free_w(self, (*self)->td->data_free);
}

/* --- Print --- */

void double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream){
    DoubleLinkedListNode *tmp;
    if(!self || !self->head) return;
    double_linked_list_node_fprint(self->head, stream, self->td->fprint);
    tmp = self->head->next;
    while(tmp){
        fprintf(stream, "%s", self->separator);
        double_linked_list_node_fprint(tmp, stream, self->td->fprint);
        tmp = tmp->next;
    }
}

void double_linked_list_print(const DoubleLinkedList *self){
    if(!self || !self->head) return;
    double_linked_list_fprint(self, stdout);
}

/* --- Dot --- */

void double_linked_list_to_dot_(DoubleLinkedList *self, FILE * stream){
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

void double_linked_list_to_dot(DoubleLinkedList *self, const char * dest_path){
    FILE * stream;
    if(!self) return;
    stream =fopen(dest_path, "w");
    if(!stream)
        printf("File can't be opened\n");
    fprintf(stream, "digraph {\n"
                  "rankdir=\"LR\";\n"
                  "splines=ortho;\n"
                  "node [shape=square , height=.1, rank = same, color=\"#000000\"]\n"
    );
    double_linked_list_to_dot_(self, stream);
    fprintf(stream, "}\n");
    fclose(stream);
}
