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

/**
 * @brief CircularLinkedList extends LinkedList
 */
typedef LinkedList CircularLinkedList;

/**
 * @brief CircularLinkedListDescriptor extends LinkedListDescriptor
 */
typedef LinkedListDescriptor CircularLinkedListDescriptor;

/**
 * @brief A detailed constructor for the cells of a linked list.
 * @param data First cell's data.
 * @param descriptor The circular linked list descriptor.
 * @return
 */
LinkedCell * circular_linked_list_builder(const void * data, CircularLinkedListDescriptor * descriptor);

/**
 * @brief Allocate and return a default
 * linked list descriptor. Type descriptor set to null.
 * @return
 */
CircularLinkedListDescriptor * circular_linked_list_descriptor();

/**
 * @brief The circular linked list constructor.
 * @param data
 * @param type_descriptor
 * @return
 */
CircularLinkedList new_circular_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *));

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
void * circular_linked_list_pop(CircularLinkedList * cll);

/**
 * Iterative free of all cells (everything) in the list.
 * free the descriptor at last cell removeetion.
 * @param cll
 */
void circular_linked_list_free(CircularLinkedList * cll);

/**
 * @brief Print the list on stdout
 * @param cll
 */
void circular_linked_list_print(CircularLinkedList cll);

/**
 * @brief Print the list on give stream
 * @param file
 * @param ll
 */
void circular_linked_list_fprint(FILE * file, CircularLinkedList ll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param ll
 * @param dest_path
 */
void circular_linked_list_to_dot(CircularLinkedList ll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARLINKEDLIST_H */
