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
#include <stdio.h>

/**
 * @brief A generic linked list \n
 * The list - the cells - refers to a linked list descriptor,
 * gathering implemented functions of the LinkedList type, including
 * a TypeDescriptor allowing manipulation of the data.
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
    LinkedList (*search) (LinkedList, const void *);
    int (*del) (LinkedList *, const void *);
    void * (*shift) (LinkedList *);
    void * (*pop) (LinkedList *);
    LinkedList * (*filter) (LinkedList *, int (* f) (const void *));
    void (*free_cell) (LinkedCell **);
    void (*free) (LinkedList *);
    void (*print) (LinkedList);
    void (*print_cell) (LinkedCell *);
    void (*fprint) (FILE *, LinkedList);
    void (*fprint_cell) (FILE *, LinkedCell *);
} LinkedListDescriptor;

/**
 * @brief Allocate and return a default
 * linked list descriptor for int data.
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
 * @param typeDescriptor
 * @return
 */
LinkedCell * new_linked_list(const void * data, TypeDescriptor * typeDescriptor);

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
 * @brief Delete the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int linked_list_del(LinkedList * ll, const void * data);

/**
 * @brief Create new linked list by filtering given linked list and filtering function.
 * Do not alter given linked list.
 * @param l
 * @param filter filtering function.
 * @return LinkedList of filtered cells.
 */
LinkedList * linked_list_filter(LinkedList * ll, int (* f) (const void *));

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

void linked_list_free_descriptor(LinkedListDescriptor ** lld);

/**
 * @brief Just to free a unique cell.
 * Does free its carried value trough the type descriptor.
 * @param l
 */
void linked_list_free_cell(LinkedCell ** ll);

/**
 * @breif Recursive free of all cells (everything) in the list.
 * free the descriptor at last cell deletion.
 * @param l
 */
void linked_list_free(LinkedList * ll);

/**
 * @brief Print the data of the given linked cell
 * @param lc
 */
void linked_list_print_cell(LinkedCell * lc);

/**
 * @brief Print the list on stdout
 * @param l
 */
void linked_list_print(LinkedList ll);

/**
 * @brief Print the data of the given linked cell
 * @param lc
 * @param file
 */
void linked_list_fprint_cell(FILE * file, LinkedCell * lc);

/**
 * @brief Print the list on stdout
 * @param l
 * @param file
 */
void linked_list_fprint(FILE * file, LinkedList ll);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
