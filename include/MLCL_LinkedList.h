/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_LINKEDLIST_H

#include <stdlib.h>
#include "../include/MLCL_TypeDescriptor.h"

/**
 * @brief A generic linked list \n
 * The list - the cells - refers to a linked list descriptor,
 * gathering implemented functions of the LinkedList type, including
 * a TypeDescriptor allowing manipulation of the data, shared across all cells.
 */
typedef struct s_linked_cell {
    void * data; /*!< Generic data */
    struct s_linked_list_descriptor * d; /*!< Descriptor of the LinkedList */
    struct s_linked_cell * next; /*!< Next cell */
} LinkedCell, * LinkedList;

typedef struct s_linked_list_descriptor {
    TypeDescriptor * type_descriptor;
    int length; /*<! Linked list length */
    int (*prepend) (LinkedList *, const void *);
    int (*append) (LinkedList *, const void *);
    int (*insert) (LinkedList *, const void *);
    int (*search) (LinkedList, const void *);
    int (*del) (LinkedList *, const void *);
    void * (*shift) (LinkedList *);
    void * (*pop) (LinkedList *);
    LinkedList * (*filter) (LinkedList *, int (* f) (const void *));
    void (*free_cell) (LinkedCell **);
    void (*free) (LinkedList *);
    void (*print) (LinkedList);
} LinkedListDescriptor;

/**
 * @brief Allocate and return a default
 * linked list descriptor for int data.
 * @return
 */
LinkedListDescriptor * ll_descriptor();

/**
 * @brief A detailed constructor for the cells of a linked list.
 * @param data First cell's data.
 * @param descriptor The linked list descriptor.
 * @return
 */
LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor);

/**
 * @brief The linked list constructor.
 * @param data
 * @return
 */
LinkedCell * new_ll(const void * data, TypeDescriptor * typeDescriptor);

/**
 * @brief Insert data to linked list head.
 * @param l
 * @param data
 * @return
 */
int ll_prepend(LinkedList * ll, const void * data);

/**
 * @brief Insert data to linked list's tail.
 * @param l
 * @param data
 * @return
 */
int ll_append(LinkedList * ll, const void * data);

/**
 * Insert data in new cell just after the given cell (aka given LinkedList's head)
 * @param ll
 * @param data
 * @return
 */
int ll_insert(LinkedList * ll, const void * data);

/**
 * @brief Short-hand search. Look for equality from TypeDescriptor comparison function.
 * @param l
 * @param data
 * @param cell Pointer to the first cell containing equal data to the given one. Set to NULL if not required.
 * @return 1 if found or 0.
 */
int ll_search(LinkedList ll, const void * data);

/**
 * @brief Delete the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int ll_del(LinkedList * ll, const void * data);

/**
 * @brief Create new linked list by filtering given linked list and filtering function.
 * Do not alter given linked list.
 * @param l
 * @param filter filtering function.
 * @return LinkedList of filtered cells.
 */
LinkedList * ll_filter(LinkedList * ll, int (* f) (const void *));

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * ll_shift(LinkedList * ll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * ll_pop(LinkedList *ll);

void ll_free_descriptor(LinkedListDescriptor ** lld);

/**
 * Just to free a unique cell.
 * Does free its carried value trough the type descriptor.
 * @param l
 */
void ll_free_cell(LinkedCell ** ll);

/**
 * Recursive free of all cells (everything) in the list.
 * free the descriptor at last cell deletion.
 * @param l
 */
void ll_free(LinkedList * ll);

/**
 * @brief Print the list on stdout
 * @param l
 */
void ll_print(LinkedList ll);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
