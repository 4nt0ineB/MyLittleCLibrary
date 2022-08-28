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

#ifndef MYLITTLECLIBRARY_DOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_DOUBLELINKEDLIST_H

#include <stdlib.h>
#include "../../core/MLCL_TypeDescriptor.h"

/**
 * @brief A generic Double linked list \n
 */
typedef struct DoubleLinkedListNode {
    void *data; /*!< Generic data */
    struct DoubleLinkedListNode *next, *prev; /*!< Next cell */
} DoubleLinkedListNode;

typedef struct {
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
void * double_linked_list_search(const DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *));
int double_linked_list_remove(DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *), void (*data_free) (void *data));
int double_linked_list_remove_all(DoubleLinkedList *self, const void *data, int (*filter) (const void *, const void *), void (*data_free) (void *data));
void double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream);
void double_linked_list_print(const DoubleLinkedList *self);
void double_linked_list_to_dot_(DoubleLinkedList *self, FILE *stream);
void double_linked_list_to_dot(DoubleLinkedList *self, const char *path);
void double_linked_list_clear(DoubleLinkedList *self, void (*data_free) (void *data));
void double_linked_list_free(DoubleLinkedList **self);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
