/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H

#include "MLCL_DoubleLinkedList.h"

/**
 * @brief CircularDoubleLinkedList extends DoubleLinkedList
 */
typedef DoubleLinkedList CircularDoubleLinkedList;

/***************************************************
 * DoubleLinkedListNode
 ***************************************************/

void * extract(DoubleLinkedListNode **self);

DoubleLinkedListNode * new_circular_double_linked_list_node(void *data);
int circular_double_linked_list_node_insert(DoubleLinkedListNode **self, void *data);
void * circular_double_linked_list_node_extract(DoubleLinkedListNode **self);
void circular_double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *));
void circular_double_linked_list_node_print(const DoubleLinkedListNode *self, void (data_fprint) (const void *, FILE *));
void circular_double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data));

/***************************************************
 * DoubleLinkedList
 ***************************************************/


CircularDoubleLinkedList * new_circular_double_linked_list(void (*type_manifest) (TypeDescriptor *td));
int circular_double_linked_list_append(DoubleLinkedList *self, void *data);
/*
int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
*/
int circular_double_linked_list_prepend(DoubleLinkedList *self, void *data);
void * circular_double_linked_list_shift(DoubleLinkedList *self);
void * circular_double_linked_list_pop(DoubleLinkedList *self);
void * circular_double_linked_list_search(const DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *));
int circular_double_linked_list_remove(DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *), void (*data_free) (void *data));
int circular_double_linked_list_remove_all(DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *), void (*data_free) (void *data));
void circular_double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream);
void circular_double_linked_list_print(const DoubleLinkedList *self);
void circular_double_linked_list_to_dot_(DoubleLinkedList *self, FILE *stream);
void circular_double_linked_list_to_dot(DoubleLinkedList *self, const char *path);
void circular_double_linked_list_clear(DoubleLinkedList *self, void (*data_free) (void *data));
void circular_double_linked_list_free(DoubleLinkedList **self);

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H */
