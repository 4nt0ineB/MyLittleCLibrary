/*
  Created by antoine on 21/05/2022.
*/

#ifndef MYLITTLECLIBRARY_MLCL_LINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_LINKEDLIST_H

#include <stdlib.h>
#include "../include/MLCL_Types.h"

/**
 * A generic linked list \n
 * The list - the cells - refers to a linked list descriptor,
 * gathering implemented functions of the LinkedList type, including
 * a TypeDescriptor allowing manipulation of the data, shared across all cells.
 *
 *
 */
typedef struct s_linked_cell {
    void * data; /*!< Generic data */
    struct s_linked_list_descriptor * d; /*!< Descriptor of the LinkedList */
    struct s_linked_cell * next; /*!< Next cell */
} LinkedCell, * LinkedList;

typedef struct s_linked_list_descriptor {
    TypeDescriptor * type_descriptor;
    int (*prepend) (LinkedList * l, const void * data);
    int (*append) (LinkedList * l, const void * data);
    int (*search) (LinkedList l, const void * data);
    int (*del) (LinkedList * l, const void * data);
    LinkedCell* (*shift) (LinkedList * l);
    LinkedCell * (*pop) (LinkedList * l);
    void (*free) (LinkedList * l);
    void (*print) (LinkedList l);
} LinkedListDescriptor;

/**
 * Allocate and return a default
 * linked list descriptor for int data
 * @return
 */
LinkedListDescriptor * ll_descriptor();

/**
 * A detailed constructor for the first cell of a linked list
 * @param data First cell's data
 * @param descriptor The linked list descriptor
 * @return
 */
LinkedCell * ll_builder(const void * data, LinkedListDescriptor * descriptor);

/**
 * Short-hand linked list constructor
 * @param data
 * @return
 */
LinkedCell * new_ll(const void * data);

/**
 * Insert data to linked list head
 * @param l
 * @param data
 * @return
 */
int ll_prepend(LinkedList * l, const void * data);

/**
 * Insert data to linked list tail
 * @param l
 * @param data
 * @return
 */
int ll_append(LinkedList * l, const void * data);

/**
 * Short-hand search. Look for equality from TypeDescriptor comparison function
 * @param l
 * @param data
 * @param cell Pointer to the first cell containing equal data to the given one. Set to NULL if not required
 * @return 1 if found or 0
 */
int ll_search(LinkedList l, const void * data);

/**
 * Delete the first occurrence of the cell containing equal data to the given one, from the linked list.
 * Uses linked list descriptor search function.
 * @param l
 * @param data
 * @return
 */
int ll_del(LinkedList * l, const void * data);

/**
 * Create new linked list by filtering given linked list and filtering function.
 * Do not alter given linked list.
 * @param l
 * @param filter filtering function
 * @return LinkedList of filtered cells
 */
LinkedList * ll_filter(LinkedList l, int (* f) (const void *));

/**
 * Apply given modification function to all data of the linked list.
 * @param l
 * @param filter filtering function
 * @return LinkedList of filtered cells
 */
LinkedList * ll_map(LinkedList l, int (* f) (const void *));

/**
 * Remove and return head's cell
 * @param l
 * @param cell
 * @return
 */
LinkedCell * ll_shift(LinkedList * l);

/**
 * Remove and return tail's cell
 * @param l
 * @param cell
 * @return
 */
LinkedCell * ll_pop(LinkedList * l);

/**
 *
 * @param l
 */
void ll_free(LinkedList * l);

/**
 * Print the list on stdout
 * @param l
 */
void ll_print(LinkedList l);

#endif /* MYLITTLECLIBRARY_MLCL_LINKEDLIST_H */
