/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
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

#ifndef MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_LINKEDLIST_H

#include "../../core/MLCL_TypeDescriptor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A generic linked list node \n
 */
typedef struct s_linked_list_node {
    void *data;
    struct s_linked_list_node *next;
} LinkedListNode;

/**
 * @brief A generic linked list \n
 */
typedef struct {
    LinkedListNode *head;
    TypeDescriptor *td;
    unsigned long int length;
    char separator[MLCL_SEPARATOR_LEN];
} LinkedList;

/***************************************************
 * LinkedListNode
 ***************************************************/
LinkedListNode * new_linked_list_node(void *data);
int linked_list_node_insert(LinkedListNode **self, void *data);
void linked_list_node_fprint(const LinkedListNode *self, FILE *stream, void (fprint_fct) (FILE *, const void *));
void linked_list_node_print(const LinkedListNode *self, void (fprint_fct) (FILE *, const void *));
void linked_list_node_free(LinkedListNode *self, void (*data_free_f) (void *data));

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
void * linked_list_search(const LinkedList *self, int (*filter) (const void *));
int linked_list_remove(LinkedList *self, int (*filter) (const void *), void (*data_free_f) (void *data));
int linked_list_remove_all(LinkedList *self, int (*filter) (const void *), void (*data_free_f) (void *data));
void linked_list_fprint(const LinkedList *self, FILE *stream); /**< Print the list on the given stream*/
void linked_list_print(const LinkedList *self); /**< Print the list on stdout */
void linked_list_to_dot_(LinkedList *self, FILE *stream);
void linked_list_to_dot(LinkedList *self, const char *path); /**< Make a formatted dot file of the struct */
void linked_list_clear(LinkedList *self, void (*data_free_f) (void *data));
void linked_list_free(LinkedList *self, void (*data_free_f) (void *data));

#endif MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
