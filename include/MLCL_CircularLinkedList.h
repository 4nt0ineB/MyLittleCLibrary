/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H

#include "MLCL_LinkedList.h"
#include <assert.h>
typedef LinkedList CircularLinkedList;


CircularLinkedList new_circular_linked_list(const void * data, TypeDescriptor * type_descriptor);

/**
 * @brief Insert data to circular linked to list's head.
 * @param cll
 * @param data
 * @return
 */
int circular_linked_list_prepend(CircularLinkedList * cll, const void * data);

/**
 * @brief Insert data to circular linked list's tail.
 * @param cll
 * @param data
 * @return
 */
int circular_linked_list_append(CircularLinkedList * ll, const void * data);

/**
 * @brief Short-hand search. Look for equality with TypeDescriptor comparison function.
 * @param cll
 * @param data
 * @return cell's address if found or NULL.
 */
CircularLinkedList circular_linked_list_search(CircularLinkedList ll, const void * data);

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param cll
 * @return
 */
void * circular_linked_list_shift(CircularLinkedList * cll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param cll
 * @return
 */
void * circular_linked_list_pop(LinkedList * cll);

/**
 * Iterative free of all cells (everything) in the list.
 * free the descriptor at last cell deletion.
 * @param cll
 */
void circular_linked_list_free(CircularLinkedList * cll);

/**
 * @brief Print the list on stdout
 * @param cll
 */
void circular_linked_list_print(CircularLinkedList cll);


#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H */
