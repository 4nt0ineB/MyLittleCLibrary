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
DoubleLinkedCell * new_circular_double_linked_list(const void * data, TypeDescriptor * type_descriptor);

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
 * Iterative free of all cells (everything) in the list.
 * free the descriptor at last cell freed.
 * @param l
 */
void circular_double_linked_list_free(CircularDoubleLinkedList * ll);

#endif /* MYLITTLECLIBRARY_MLCL_CIRCULARDOUBLELINKEDLIST_H */
