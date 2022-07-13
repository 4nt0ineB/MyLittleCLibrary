/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_DOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_DOUBLELINKEDLIST_H

#include <stdlib.h>
#include "../include/MLCL_TypeDescriptor.h"

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
 * The list - the cells - refers to a linked list descriptor,
 * gathering implemented functions of the DoubleLinkedList type, including
 * a TypeDescriptor allowing manipulation of the data, and the list length.
 */
typedef struct s_double_linked_list_descriptor {
    TypeDescriptor * type_descriptor;
    int length; /*<! Linked list length */
    int (*prepend) (DoubleLinkedList *, const void *);
    int (*append) (DoubleLinkedList *, const void *);
    int (*insert) (DoubleLinkedList *, const void *);
    int (*search) (DoubleLinkedList, const void *);
    void * (*extract) (DoubleLinkedCell **);
    int (*remove) (DoubleLinkedList *, const void *);
    void * (*shift) (DoubleLinkedList *);
    void * (*pop) (DoubleLinkedList *);
    DoubleLinkedList * (*filter) (DoubleLinkedList *, int (* f) (const void *));
    void (*cell_free) (DoubleLinkedCell **);
    void (*free) (DoubleLinkedList *);
    void (*print) (DoubleLinkedList);
    void (*fprint) (FILE *, DoubleLinkedList);
    void (*cell_fprint) (FILE *, DoubleLinkedCell *);
    void (*to_dot) (DoubleLinkedList, const char * path);
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
DoubleLinkedCell * new_double_linked_list(const void * data, TypeDescriptor * typeDescriptor);

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
int double_linked_list_search(DoubleLinkedList dll, const void * data);

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
 * @brief Create new linked list by filtering given linked list and filtering function.
 * Do not alter given linked list.
 * @param l
 * @param filter filtering function.
 * @return LinkedList of filtered cells.
 */
DoubleLinkedList * double_linked_list_filter(DoubleLinkedList * dll, int (* f) (const void *));

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
 * @brief Print the list on stdout
 * @param l
 */
void double_linked_list_print(DoubleLinkedList dll);

/**
 * @brief Print the data of the double linked cell on given stream
 * @param file
 * @param dlc
 */
void double_linked_list_cell_fprint(FILE * file, DoubleLinkedCell * dlc);

/**
 * @brief Print the list on give stream
 * @param file
 * @param dll
 */
void double_linked_list_fprint(FILE * file, DoubleLinkedList dll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param ll
 * @param dest_path
 */
void double_linked_list_to_dot(DoubleLinkedList ll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
