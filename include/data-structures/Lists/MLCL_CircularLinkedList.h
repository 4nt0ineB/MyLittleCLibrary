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
void circular_linked_list_node_fprint(const LinkedListNode *self, FILE *stream, void (data_fprint) (FILE *, const void *));
void circular_linked_list_node_print(const LinkedListNode *self, void (data_fprint) (FILE *, const void *));
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
void * circular_linked_list_search(const LinkedList *self, int (*filter) (const void *));
void circular_linked_list_fprint(const LinkedList *self, FILE *stream);
void circular_linked_list_print(const LinkedList *self);
void circular_linked_list_to_dot_(LinkedList *self, FILE *stream);
void circular_linked_list_to_dot(LinkedList *self, const char *path);
void circular_linked_list_clear(LinkedList *self, void (*data_free) (void *data));
void circular_linked_list_free(LinkedList **self, void (*data_free) (void *data));

/*
    @Todo: remove, remove_all, append_sorted
 */

/*
    int circular_linked_list_remove(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
    int circular_linked_list_remove_all(LinkedList *self, int (*filter) (const void *), void (*data_free) (void *data));
    int linked_list_append_sorted(LinkedList *self, const void *, int (*ordering) (const void *, const void *));
 */

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H */
