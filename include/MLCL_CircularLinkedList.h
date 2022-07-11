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


CircularLinkedList new_cll(const void * data, TypeDescriptor * type_descriptor);

/**
 * @brief Insert data to circular linked list's tail.
 * @param l
 * @param data
 * @return
 */
int cll_append(LinkedList * ll, const void * data);

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * cll_shift(CircularLinkedList * ll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param l
 * @param cell
 * @return
 */
void * cll_pop(LinkedList * cll);

/**
 * Iterative free of all cells (everything) in the list.
 * free the descriptor at last cell deletion.
 * @param l
 */
void cll_free(CircularLinkedList * ll);

/**
 * @brief Print the list on stdout
 * @param l
 */
void cll_print(CircularLinkedList cll);


#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H */
