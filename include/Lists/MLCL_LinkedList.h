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

#include "../MLCL_TypeDescriptor.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief A generic linked list \n
 */
typedef struct s_linked_cell {
    void * data; /*!< Generic data */
    struct s_linked_list_descriptor * d; /*!< Descriptor of the LinkedList */
    struct s_linked_cell * next; /*!< Next cell */
} LinkedCell, * LinkedList;

/**
 * @brief Descriptor of the linked list
 * The list - the cells - refers to a linked list descriptor,
 * gathering implemented functions of the LinkedList type, including
 * a TypeDescriptor allowing manipulation of the data, and the list length.
 */
typedef struct s_linked_list_descriptor {
    TypeDescriptor * type_descriptor;
    int length; /**< Linked list length */
    int (*add_) (LinkedList *, const void *, int (*cmp) (const void *, const void *)); /**< ordered add depending on given function Must return 1 or 0 */
    int (*ordered_add) (LinkedList *, const void *); /**< Ascending add */
    int (*reverse_ordered_add) (LinkedList *, const void *); /**< Descending add*/
    LinkedList (*merge_sort) (LinkedList *, int (*cmp) (const void *, const void *));
    int (*prepend) (LinkedList *, const void *); /**< Add data to the head */
    int (*append) (LinkedList *, const void *); /**< Add data to the tail*/
    int (*insert) (LinkedList *, const void *); /**< Insert given data right next to the given cell */
    LinkedList (*search) (LinkedList, const void *); /**< Search and return a pointer to the first found occurrence of the given data */
    int (*remove) (LinkedList *, const void *); /**< Search and remove first occurrence of the given data */
    /* @Todo filter_remove */
    /* @Todo cell_remove */
    void * (*shift) (LinkedList *); /**< Remove head's cell and return the pointer to its data */
    void * (*pop) (LinkedList *); /**< Remove tail's cell and return the pointer to its data */
    void (*cell_free) (LinkedCell **); /**< Free the given cell */
    void (*free) (LinkedList *); /**< Free the list */
    void (*cell_print) (LinkedCell *); /**< Print the given cell on stdout */
    void (*cell_fprint) (FILE *, LinkedCell *); /**< Print the given cell on given stream */
    void (*print) (LinkedList); /**< Print the list on stdout */
    void (*fprint) (FILE *, LinkedList); /**< Print the list on the given stream*/
    void (*to_dot) (LinkedList, const char *); /**< Make a formatted dot file of the struct */
} LinkedListDescriptor;

/**
 * @brief Allocate and return a default
 * linked list descriptor. Type descriptor set to null.
 * @return
 */
LinkedListDescriptor * linked_list_descriptor();

/**
 * @brief A detailed constructor for the cells of a linked list.
 * @param data First cell's data.
 * @param descriptor The linked list descriptor.
 * @return
 */
LinkedCell * linked_list_builder(const void * data, LinkedListDescriptor * descriptor);

/**
 * @brief The linked list constructor.
 * @param data
 * @param type_descriptor
 * @return
 */
LinkedCell * new_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Add data to the list depending on the given comparison function. To have like an ordered list.
 * @param ll A linked list pointer
 * @param data A pointer to a a data of the same carried by the list
 * @param cmp A comparison function returning 1 or 0 (!),
 * to check if the data have to be inserted or not before a value of the list
 * @return
 */
int linked_list_add_(LinkedList * ll, const void * data, int (*cmp) (const void *, const void *));

/**
 * @brief Add item considering the list is sorted with an ascending order
 * Shorthand of linked_list_add_(), passing the lt function of the TypeDescriptor.
 * @param ll
 * @param data
 * @return
 */
int linked_list_ordered_add(LinkedList * ll, const void * data);

/**
 * @brief Add item considering the list is sorted with a descending order
 * Shorthand of linked_list_add_(), passing the ge function of the TypeDescriptor.
 * @param ll
 * @param data
 * @return
 */
int linked_list_reverse_ordered_add(LinkedList * ll, const void * data);

/**
 * @brief
 * @param l
 */
LinkedList linked_list_merge_sort(LinkedList *l, int (*cmp) (const void *, const void *));

/**
 * @brief Insert data to linked list head.
 * @param l
 * @param data
 * @return
 */
int linked_list_prepend(LinkedList * ll, const void * data);

/**
 * @brief Insert data to linked list's tail.
 * @param ll
 * @param data
 * @return
 */
int linked_list_append(LinkedList * ll, const void * data);

/**
 * Insert data in new cell just after the given cell (aka given LinkedList's head)
 * @param ll
 * @param data
 * @return
 */
int linked_list_insert(LinkedList * ll, const void * data);

/**
 * @brief Short-hand search. Look for equality with TypeDescriptor comparison function.
 * @param cll
 * @param data
 * @return cell's address if found or NULL.
 */
LinkedList linked_list_search(LinkedList ll, const void * data);

/**
 * @brief removeete the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int linked_list_remove(LinkedList * ll, const void * data);

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * linked_list_shift(LinkedList * ll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * linked_list_pop(LinkedList *ll);

void linked_list_descriptor_free(LinkedListDescriptor ** lld);

/**
 * @brief Just to free a unique cell.
 * Does free its carried value trough the type descriptor.
 * @param l
 */
void linked_list_cell_free(LinkedCell ** ll);

/**
 * @breif Recursive free of all cells (everything) in the list.
 * free the descriptor at last cell removeetion.
 * @param l
 */
void linked_list_free(LinkedList * ll);

/**
 * @brief Print the data of the given linked cell
 * @param lc
 */
void linked_list_cell_print(LinkedCell * lc);

/**
 * @brief Print the list on stdout
 * @param l
 */
void linked_list_print(LinkedList ll);

/**
 * @brief Print the data of the linked cell on given stream
 * @param file
 * @param lc
 */
void linked_list_cell_fprint(FILE * stream, LinkedCell * lc);

/**
 * @brief Print the list on give stream
 * @param file
 * @param ll
 */
void linked_list_fprint(FILE * stream, LinkedList ll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param ll
 * @param dest_path
 */
void linked_list_to_dot(LinkedList ll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
