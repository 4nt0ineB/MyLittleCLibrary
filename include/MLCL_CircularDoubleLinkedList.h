/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H

#include "MLCL_DoubleLinkedList.h"

/**
 * @brief CircularDoubleLinkedList extends DoubleLinkedList
 */
typedef DoubleLinkedList CircularDoubleLinkedList;

/**
 * @brief CircularLinkedListDescriptor extends DoubleLinkedListDescriptor
 */
typedef DoubleLinkedListDescriptor CircularDoubleLinkedListDescriptor;

/**
 * @brief A detailed constructor for the cells of a circular double linked list.
 * @param data First cell's data.
 * @param descriptor The circular linked list descriptor.
 * @return
 */
DoubleLinkedCell * circular_double_linked_list_builder(const void * data, CircularDoubleLinkedListDescriptor * descriptor);

/**
 * @brief Allocate and return a default
 * circular double linked list descriptor. Type descriptor set to null
 * @return
 */
CircularDoubleLinkedListDescriptor * circular_double_linked_list_descriptor();

/**
 * @brief The circular double linked list constructor.
 * @param data
 * @param type_descriptor
 * @return
 */
DoubleLinkedCell * new_circular_double_linked_list(const void * data, void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Insert data to linked list head.
 * @param l
 * @param data
 * @return
 */
int circular_double_linked_list_prepend(CircularDoubleLinkedList * ll, const void * data);

/**
 * @brief Insert data to circular double linked list's tail.
 * So the cell previous the given one actually..
 * @param cdll
 * @param data
 * @return
 */
int circular_double_linked_list_append(CircularDoubleLinkedList * cdll, const void * data);

/**
 * @brief Short-hand search. Look for equality with TypeDescriptor comparison function.
 * @param cdll
 * @param data
 * @return cell's address if found or NULL.
 */
CircularDoubleLinkedList circular_double_linked_list_search(CircularDoubleLinkedList cdll, const void * data);

/**
 * @brief Remove and return head's data. The Targeted cell will be freed not the data.
 * @param cdll
 * @return
 */
void * circular_double_linked_list_shift(CircularDoubleLinkedList * cdll);

/**
 * @brief Remove and return tail's data. The Targeted cell will be freed not the data.
 * @param cdll
 * @return
 */
void * circular_double_linked_list_pop(CircularDoubleLinkedList * cdll);

/**
 * Iterative free of all cells (everything) in the list.
 * free the descriptor at last cell freed.
 * @param cdll
 */
void circular_double_linked_list_free(CircularDoubleLinkedList * cdll);

/**
 * @brief Print the list on stdout
 * @param cdll
 */
void circular_double_linked_list_print(CircularDoubleLinkedList cdll);

/**
 * @brief Print the list on give stream
 * @param file
 * @param cdll
 */
void circular_double_linked_list_fprint(FILE * file, CircularDoubleLinkedList cdll);

/**
 * @brief Produce a dot formatted file of a representation of the structure
 * @param cdll
 * @param dest_path
 */
void circular_double_linked_list_to_dot(CircularDoubleLinkedList cdll, const char * dest_path);

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H */
