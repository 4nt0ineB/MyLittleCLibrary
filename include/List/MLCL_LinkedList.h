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
    int length; /*<! Linked list length */
    int (*add_) (LinkedList *, const void *, int (*cmp) (const void *, const void *));
    int (*ordered_add) (LinkedList *, const void *);
    int (*reverse_ordered_add) (LinkedList *, const void *);
    int (*prepend) (LinkedList *, const void *);
    int (*append) (LinkedList *, const void *);
    int (*insert) (LinkedList *, const void *);
    LinkedList (*search) (LinkedList, const void *);
    int (*remove) (LinkedList *, const void *);
    void * (*shift) (LinkedList *);
    void * (*pop) (LinkedList *);
    LinkedList * (*filter) (LinkedList *, int (* f) (const void *));
    void (*cell_free) (LinkedCell **);
    void (*free) (LinkedList *);
    void (*print) (LinkedList);
    void (*cell_print) (LinkedCell *);
    void (*fprint) (FILE *, LinkedList);
    void (*cell_fprint) (FILE *, LinkedCell *);
    void (*to_dot) (LinkedList, const char *);
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
 * @param ll
 * @param data
 * @param cmp comparison function returning 1 or 0, to check if the have to be inserted
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
void linked_list_cell_fprint(FILE * file, LinkedCell * lc);

/**
 * @brief Print the list on give stream
 * @param file
 * @param ll
 */
void linked_list_fprint(FILE * file, LinkedList ll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param ll
 * @param dest_path
 */
void linked_list_to_dot(LinkedList ll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
