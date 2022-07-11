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
 * The list - the cells - refers to a double linked list descriptor,
 * gathering implemented functions of the DoubleLinkedList type, including
 * a TypeDescriptor allowing manipulation of the data.
 */
typedef struct s_double_linked_cell {
    void * data; /*!< Generic data */
    struct s_double_linked_list_descriptor * d; /*!< Descriptor of the LinkedList */
    struct s_double_linked_cell * next; /*!< Next cell */
    struct s_double_linked_cell * prev; /*!< Previous cell */
} DoubleLinkedCell, * DoubleLinkedList;

typedef struct s_double_linked_list_descriptor {
    TypeDescriptor * type_descriptor;
    int length; /*<! Linked list length */
    int (*prepend) (DoubleLinkedList *, const void *);
    int (*append) (DoubleLinkedList *, const void *);
    int (*insert) (DoubleLinkedList *, const void *);
    int (*search) (DoubleLinkedList, const void *);
    int (*del) (DoubleLinkedList *, const void *);
    void * (*shift) (DoubleLinkedList *);
    void * (*pop) (DoubleLinkedList *);
    DoubleLinkedList * (*filter) (DoubleLinkedList *, int (* f) (const void *));
    void (*free_cell) (DoubleLinkedCell **);
    void (*free) (DoubleLinkedList *);
    void (*print) (DoubleLinkedList);
} DoubleLinkedListDescriptor;

/**
 * @brief Allocate and return a default
 * linked list descriptor for int data.
 * @return
 */
DoubleLinkedListDescriptor * dll_descriptor();

/**
 * @brief A detailed constructor for the cells of a linked list.
 * @param data First cell's data.
 * @param descriptor The linked list descriptor.
 * @return
 */
DoubleLinkedCell * dll_builder(const void * data, DoubleLinkedListDescriptor * descriptor);

/**
 * @brief The linked list constructor.
 * @param data
 * @return
 */
DoubleLinkedCell * new_dll(const void * data, TypeDescriptor * typeDescriptor);

/**
 * @brief Insert data to linked list head.
 * @param l
 * @param data
 * @return
 */
int dll_prepend(DoubleLinkedList * dll, const void * data);

/**
 * @brief Insert data to linked list's tail.
 * @param l
 * @param data
 * @return
 */
int dll_append(DoubleLinkedList * dll, const void * data);

/**
 * Insert data in new cell just after the given cell (aka given LinkedList's head)
 * @param ll
 * @param data
 * @return
 */
int dll_insert(DoubleLinkedList * dll, const void * data);

/**
 * @brief Short-hand search. Look for equality from TypeDescriptor comparison function.
 * @param l
 * @param data
 * @param cell Pointer to the first cell containing equal data to the given one. Set to NULL if not required.
 * @return 1 if found or 0.
 */
int dll_search(DoubleLinkedList dll, const void * data);

/**
 * @brief Delete the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int dll_del(DoubleLinkedList * dll, const void * data);

/**
 * @brief Create new linked list by filtering given linked list and filtering function.
 * Do not alter given linked list.
 * @param l
 * @param filter filtering function.
 * @return LinkedList of filtered cells.
 */
DoubleLinkedList * dll_filter(DoubleLinkedList * dll, int (* f) (const void *));

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * dll_shift(DoubleLinkedList * dll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * dll_pop(DoubleLinkedList * dll);

void dll_free_descriptor(DoubleLinkedListDescriptor ** lld);

/**
 * Just to free a unique cell.
 * Does free its carried value trough the type descriptor.
 * @param l
 */
void dll_free_cell(DoubleLinkedCell ** dlc);

/**
 * Recursive free of all cells (everything) in the list.
 * free the descriptor at last cell deletion.
 * @param l
 */
void dll_free(DoubleLinkedList * dll);

/**
 * @brief Print the list on stdout
 * @param l
 */
void dll_print(DoubleLinkedList dll);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
