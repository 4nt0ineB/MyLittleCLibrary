/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_LINKEDLIST_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../../core/Filter/MLCL_Filter.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A generic linked list node \n
 */
typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
} LinkedListNode;

/**
 * @brief A generic linked list \n
 */
typedef struct {
    LinkedListNode *head;
    TypeDescriptor *td;
    int length;
    char separator[MLCL_SEPARATOR_LEN];
} LinkedList;

/***************************************************
 * LinkedListNode
 ***************************************************/
LinkedListNode * new_linked_list_node(void *data);
int linked_list_node_insert(LinkedListNode **self, void *data);
void linked_list_node_fprint(const LinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *));
void linked_list_node_print(const LinkedListNode *self, void (*data_fprint) (const void *, FILE *));
void linked_list_node_free(LinkedListNode **self, void (*data_free) (void *));

/***************************************************
 * LinkedList
 ***************************************************/

LinkedList * new_linked_list(void (*type_manifest) (TypeDescriptor *td));
int linked_list_append(LinkedList *self, void *data);
/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/
int linked_list_prepend(LinkedList *self, void *data);
void linked_list_merge_sort(LinkedList *self, int (*ordering) (const void *, const void *));
void * linked_list_shift(LinkedList *self);
void * linked_list_pop(LinkedList *self);

void * linked_list_search(const LinkedList *self, Filter *filter);
LinkedList * linked_list_search_all(const LinkedList *self, Filter *filter);

void * linked_list_extract(LinkedList *self, Filter *filter);
LinkedList * linked_list_extract_all(LinkedList *self, Filter *filter);

int linked_list_remove_w(LinkedList *self, Filter *filter, void (*data_free) (void *));
int linked_list_remove(LinkedList *self, Filter *filter);

int linked_list_remove_all_w(LinkedList *self, Filter *filter, void (*data_free) (void *));
int linked_list_remove_all(LinkedList *self, Filter *filter);

void linked_list_fprint(const LinkedList *self, FILE *stream);
void linked_list_print(const LinkedList *self);
void linked_list_to_dot_(LinkedList *self, FILE *stream);
void linked_list_to_dot(LinkedList *self, const char *path);

void linked_list_clear_w(LinkedList *self, void (*data_free) (void *data));
void linked_list_clear(LinkedList *self);

void linked_list_free_w(LinkedList **self, void (*data_free) (void *));
void linked_list_free(LinkedList **self);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
