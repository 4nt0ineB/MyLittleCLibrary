/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_DOUBLELINKEDLIST_H
#define MYLITTLECLIBRARY_DOUBLELINKEDLIST_H

#include <stdlib.h>
#include "../../core/MLCL_TypeDescriptor.h"
#include "../../core/Filter/MLCL_Filter.h"

/**
 * @brief A generic Double linked list \n
 */
typedef struct DoubleLinkedListNode {
    void *data; /*!< Generic data */
    struct DoubleLinkedListNode *next, *prev; /*!< Next node */
} DoubleLinkedListNode;

typedef struct DoubleLinkedList{
    DoubleLinkedListNode *head; /*!< Head of the list */
    TypeDescriptor *td; /*!< Type descriptor of carried data */
    int length; /*!< length of the list */
    char separator[MLCL_SEPARATOR_LEN]; /*!< Separator for print */
} DoubleLinkedList;

/***************************************************
 * DoubleLinkedListNode
 ***************************************************/

/**
 * @brief Alloc a new double linked node
 * @param data the data to carry
 * @return
 */
DoubleLinkedListNode * new_double_linked_list_node(void *data);

/**
 * @brief insert a node after the given one with the given data
 * @param self
 * @param data
 * @return
 */
int double_linked_list_node_insert(DoubleLinkedListNode **self, void *data);

/**
 * @brief Extract the node
 * @details next and prev set to NULL
 * @param self
 * @return
 */
void * double_linked_list_node_extract(DoubleLinkedListNode **self);

/**
 * @brief
 * @param self
 * @param stream
 * @param data_fprint
 */
void double_linked_list_node_fprint(const DoubleLinkedListNode *self, FILE *stream, void (data_fprint) (const void *, FILE *));

/**
 *
 * @param self
 * @param data_fprint
 */
void double_linked_list_node_print(const DoubleLinkedListNode *self, void (data_fprint) (const void *, FILE *));

/**
 * @brief
 * @param self
 * @param data_free_f
 */
void double_linked_list_node_free(DoubleLinkedListNode **self, void (*data_free_f) (void *data));

/***************************************************
 * DoubleLinkedList
 ***************************************************/

/**
 * @brief Alloc and return a new empty linked list
 * @param type_manifest
 * @return
 */
DoubleLinkedList * new_double_linked_list(void (*type_manifest) (TypeDescriptor *td));

/**
 * @brief
 * @param self
 * @param data
 * @return
 */
int double_linked_list_append(DoubleLinkedList *self, void *data);

/**
 * @brief
 * @param self
 * @param data
 * @return
 */
int double_linked_list_prepend(DoubleLinkedList *self, void *data);

/**
 * @brief Extract and return the data from the head
 * @param self
 * @return
 */
void * double_linked_list_shift(DoubleLinkedList *self);

/**
 * @brief Extract and return the data from the tail
 * @param self
 * @return
 */
void * double_linked_list_pop(DoubleLinkedList *self);

/**
 * @brief
 * @param self
 * @param filter
 * @return
 */
void * double_linked_list_search(const DoubleLinkedList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param filter
 * @return
 */
DoubleLinkedList * double_linked_list_search_all(const DoubleLinkedList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param filter
 * @return
 */
void * double_linked_list_extract(DoubleLinkedList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param filter
 * @return
 */
DoubleLinkedList * double_linked_list_extract_all(DoubleLinkedList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param filter
 * @param data_free
 * @return
 */
int double_linked_list_remove_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data));
/**
 * @brief
 * @param self
 * @param filter
 * @return
 */
int double_linked_list_remove(DoubleLinkedList *self, Filter *filter);

/**
 *
 * @param self
 * @param filter
 * @param data_free
 * @return
 */
int double_linked_list_remove_all_w(DoubleLinkedList *self, Filter *filter, void (*data_free) (void *data));

/**
 *
 * @param self
 * @param filter
 * @return
 */
int double_linked_list_remove_all(DoubleLinkedList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param stream
 */
void double_linked_list_fprint(const DoubleLinkedList *self, FILE *stream);

/**
 * @brief
 * @param self
 */
void double_linked_list_print(const DoubleLinkedList *self);

/**
 * @brief
 * @param self
 * @param stream
 */
void double_linked_list_to_dot_(DoubleLinkedList *self, FILE *stream);

/**
 * @brief
 * @param self
 * @param path
 */
void double_linked_list_to_dot(DoubleLinkedList *self, const char *path);

/**
 *
 * @param self
 * @param data_free
 */
void double_linked_list_clear_w(DoubleLinkedList *self, void (*data_free) (void *data));

/**
 *
 * @param self
 */
void double_linked_list_clear(DoubleLinkedList *self);

/**
 *
 * @param self
 * @param data_free
 */
void double_linked_list_free_w(DoubleLinkedList **self, void (data_free) (void *));

/**
 * @brief
 * @param self
 */
void double_linked_list_free(DoubleLinkedList **self);

#endif /* MYLITTLECLIBRARY_DOUBLELINKEDLIST_H */
