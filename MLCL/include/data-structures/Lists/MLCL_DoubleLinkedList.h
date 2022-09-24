/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_DOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_DOUBLELINKEDLIST_H

#include <stdlib.h>
#include "../../core/MLCL_TypeDescriptor.h"
#include "../../core/Filter/MLCL_Filter.h"

/**
 * @brief A generic Double linked list \n
 */
typedef struct DoubleLinkedListNode {
    void *data; /*!< Generic data */
    struct DoubleLinkedListNode *next, *prev; /*!< Next cell */
} DoubleLinkedListNode;

typedef struct DoubleLinkedList{
    DoubleLinkedListNode *head;
    TypeDescriptor *td;
    int length;
    char separator[MLCL_SEPARATOR_LEN];
} DoubleLinkedList;

/***************************************************
 * DoubleLinkedListNode
 ***************************************************/

DoubleLinkedListNode * new_double_linked_list_node(void *data);
int double_linked_list_node_insert(DoubleLinkedListNode **self, void *data);
void * double_linked_list_node_extract(DoubleLinkedListNode **self);
void double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *));
void double_linked_list_node_print(const DoubleLinkedListNode *self, void (data_fprint) (const void *, FILE *));
void double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data));

/***************************************************
 * DoubleLinkedList
 ***************************************************/


DoubleLinkedList * new_double_linked_list(void (*type_manifest) (TypeDescriptor *td));
int double_linked_list_append(DoubleLinkedList *self, void *data);
/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/
int double_linked_list_prepend(DoubleLinkedList *self, void *data);
void * double_linked_list_shift(DoubleLinkedList *self);
void * double_linked_list_pop(DoubleLinkedList *self);


void * double_linked_list_search(const DoubleLinkedList *self, Filter *filter);
DoubleLinkedList * double_linked_list_search_all(const DoubleLinkedList *self, Filter *filter);

void * double_linked_list_extract(DoubleLinkedList *self, Filter *filter);
DoubleLinkedList * double_linked_list_extract_all(DoubleLinkedList *self, Filter *filter);

int double_linked_list_remove_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data));
int double_linked_list_remove(DoubleLinkedList *self, Filter *filter);
int double_linked_list_remove_all_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data));
int double_linked_list_remove_all(DoubleLinkedList *self, Filter *filter);


void double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream);
void double_linked_list_print(const DoubleLinkedList *self);
void double_linked_list_to_dot_(DoubleLinkedList *self, FILE *stream);
void double_linked_list_to_dot(DoubleLinkedList *self, const char *path);
void double_linked_list_clear_w(DoubleLinkedList *self, void (*data_free) (void *data));
void double_linked_list_clear(DoubleLinkedList *self);
void double_linked_list_free_w(DoubleLinkedList **self, void (data_free) (void *));
void double_linked_list_free(DoubleLinkedList **self);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
