/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H

#include "MLCL_LinkedList.h"
#include <assert.h>

/**
 * @brief CircularLinkedList implement LinkedList
 */
typedef LinkedList CircularLinkedList;

/***************************************************
 * CircularLinkedListNode
 ***************************************************/
LinkedListNode * new_circular_linked_list_node(void *data);
void circular_linked_list_node_fprint(const LinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *));
void circular_linked_list_node_print(const LinkedListNode *self, void (data_fprint) (const void *, FILE *));
void circular_linked_list_node_free(LinkedListNode **self, void (*data_free) (void *data));

/***************************************************
 * CircularLinkedList
 ***************************************************/
LinkedList * new_circular_linked_list(void (*type_manifest) (TypeDescriptor *td));
int circular_linked_list_append(LinkedList *self, void *data);
int circular_linked_list_prepend(LinkedList *self, void *data);
void circular_linked_list_merge_sort(LinkedList *self, int (*ordering) (const void *, const void *));
void * circular_linked_list_shift(LinkedList *self);
void * circular_linked_list_pop(LinkedList *self);
void * circular_linked_list_search(const LinkedList *self, const void *data, int (*filter) (const void *, const void *));
void circular_linked_list_fprint(const LinkedList *self, FILE *stream);
void circular_linked_list_print(const LinkedList *self);
void circular_linked_list_to_dot_(LinkedList *self, FILE *stream);
void circular_linked_list_to_dot(LinkedList *self, const char *path);
void circular_linked_list_clear(LinkedList *self, void (*data_free) (void *data));
void circular_linked_list_free(LinkedList **self);

/*
    @Todo: remove, remove_all, append_sorted
 */

/*
    int circular_linked_list_remove(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
    int circular_linked_list_remove_all(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
    int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
 */

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H */
