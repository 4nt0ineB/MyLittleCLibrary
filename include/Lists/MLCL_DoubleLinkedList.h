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
#include "../MLCL_TypeDescriptor.h"

/**
 * @brief A generic Double linked list \n
 */
typedef struct s_double_linked_cell {
    void * data; /*!< Generic data */
    struct s_double_linked_list_descriptor * d; /*!< Descriptor of the LinkedList */
    struct s_double_linked_cell * next; /*!< Next cell */
    struct s_double_linked_cell * prev; /*!< Previous cell */
} DoubleLinkedCell, * DoubleLinkedList;

/**
 * @brief Descriptor of the linked list
 * The list - the cells - refers to a double linked list descriptor,
 * gathering implemented functions of the DoubleLinkedList type, including
 * a TypeDescriptor allowing manipulation of the data, and the list length.
 */
typedef struct s_double_linked_list_descriptor {
    int length; /*<! Linked list length */
    TypeDescriptor * type_descriptor;
    int (*add_) (DoubleLinkedList *, const void *, int (*cmp) (const void *, const void *));  /**< ordered add depending on given function. Must return 1 or 0 */
    int (*ordered_add) (DoubleLinkedList *, const void *); /**< Ascending add */
    int (*reverse_ordered_add) (DoubleLinkedList *, const void *); /**< Descending add*/
    int (*prepend) (DoubleLinkedList *, const void *); /**< Add data to the head */
    int (*append) (DoubleLinkedList *, const void *); /**< Add data to the tail*/
    int (*insert) (DoubleLinkedList *, const void *); /**< Insert given data right next to the given cell */
    DoubleLinkedCell * (*search) (DoubleLinkedList, const void *); /**< Search and return a pointer to the first found occurrence of the given data */
    void * (*extract) (DoubleLinkedCell **);
    int (*remove) (DoubleLinkedList *, const void *); /**< Search and remove first occurrence of the given data */
    /* @Todo filter_remove */
    /* @Todo cell_remove */
    void * (*shift) (DoubleLinkedList *); /**< Remove head's cell and return the pointer to its data */
    void * (*pop) (DoubleLinkedList *); /**< Remove tail's cell and return the pointer to its data */
    void (*cell_free) (DoubleLinkedCell **); /**< Free the given cell */
    void (*free) (DoubleLinkedList *); /**< Free the list */
    void (*cell_print) (DoubleLinkedList); /**< Print the given cell on stdout */
    void (*cell_fprint) (FILE *, DoubleLinkedCell *); /**< Print the given cell on given stream */
    void (*print) (DoubleLinkedList); /**< Print the list on stdout */
    void (*fprint) (FILE *, DoubleLinkedList); /**< Print the list on the given stream*/
    void (*to_dot) (DoubleLinkedList, const char * path); /**< Make a formatted dot file of the struct */
    /* .- -. - --- .. -. . / -... .- ... - --- ... */
} DoubleLinkedListDescriptor;

/**
 * @brief Allocate and return a default
 * linked list descriptor for int data.
 * @return
 */
DoubleLinkedListDescriptor * double_linked_list_descriptor();

/**
 * @brief A detailed constructor for the cells of a linked list.
 * @param data First cell's data.
 * @param descriptor The linked list descriptor.
 * @return
 */
DoubleLinkedCell * double_linked_list_builder(const void * data, DoubleLinkedListDescriptor * descriptor);

/**
 * @brief The linked list constructor.
 * @param data
 * @param typeDescriptor
 * @return
 */
DoubleLinkedCell * new_double_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Add data to the list depending on the given comparison function. To have like an ordered list.
 * @param dll
 * @param data
 * @param cmp comparison function returning 1 or 0, to check if the have to be inserted
 * @return
 */
int double_linked_list_add_(DoubleLinkedList * dll, const void * data, int (*cmp) (const void *, const void *));

/**
 * @brief Add item considering the list is sorted with an ascending order
 * Shorthand of double_linked_list_add_(), passing the lt function of the TypeDescriptor.
 * @param dll
 * @param data
 * @return
 */
int double_linked_list_ordered_add(DoubleLinkedList * dll, const void * data);

/**
 * @brief Add item considering the list is sorted with a descending order
 * Shorthand of double_linked_list_add_(), passing the ge function of the TypeDescriptor.
 * @param ll
 * @param data
 * @return
 */
int double_linked_list_reverse_ordered_add(DoubleLinkedList * ll, const void * data);

/**
 * @brief Insert data to linked list head.
 * @param l
 * @param data
 * @return
 */
int double_linked_list_prepend(DoubleLinkedList * dll, const void * data);

/**
 * @brief Insert data to linked list's tail.
 * @param l
 * @param data
 * @return
 */
int double_linked_list_append(DoubleLinkedList * dll, const void * data);

/**
 * Insert data in new cell just after the given cell (aka given LinkedList's head)
 * @param ll
 * @param data
 * @return
 */
int double_linked_list_insert(DoubleLinkedList * dll, const void * data);

/**
 * @brief Short-hand search. Look for equality from TypeDescriptor comparison function.
 * @param l
 * @param data
 * @param cell Pointer to the first cell containing equal data to the given one. Set to NULL if not required.
 * @return 1 if found or 0.
 */
DoubleLinkedCell * double_linked_list_search(DoubleLinkedList dll, const void * data);

/**
 * Extract a double linked cell from its list, the data pointer is returned and the cell freed.
 * @param dlc
 * @return
 */
void * double_linked_list_extract(DoubleLinkedCell ** dlc);

/**
 * @brief Remove the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int double_linked_list_remove(DoubleLinkedList * dll, const void * data);

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * double_linked_list_shift(DoubleLinkedList * dll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * double_linked_list_pop(DoubleLinkedList * dll);

/**
 * @brief
 * @param lld
 */
void double_linked_list_descriptor_free(DoubleLinkedListDescriptor ** lld);

/**
 * Just to free a unique cell.
 * Does free its carried value trough the type descriptor.
 * @param l
 */
void double_linked_list_cell_free(DoubleLinkedCell ** dlc);

/**
 * Recursive free of all cells (everything) in the list.
 * free the descriptor at last cell freed.
 * @param l
 */
void double_linked_list_free(DoubleLinkedList * dll);

/**
 * @brief Print the data of the given double linked cell
 * @param dlc
 */
void double_linked_list_cell_print(DoubleLinkedCell * dlc);

/**
 * @brief Print the list on stdout
 * @param l
 */
void double_linked_list_print(DoubleLinkedList dll);

/**
 * @brief Print the data of the double linked cell on given stream
 * @param file
 * @param dlc
 */
void double_linked_list_cell_fprint(FILE * stream, DoubleLinkedCell * dlc);

/**
 * @brief Print the list on give stream
 * @param file
 * @param dll
 */
void double_linked_list_fprint(FILE * stream, DoubleLinkedList dll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param ll
 * @param dest_path
 */
void double_linked_list_to_dot(DoubleLinkedList ll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
