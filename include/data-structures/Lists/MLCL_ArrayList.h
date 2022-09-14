/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H
#define MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H

#include "../../core/MLCL_TypeDescriptor.h"

#define ARRAY_LIST_BLOCK_SIZE 10
#define ARRAY_LIST_MAX_EMPTY_BLOCKS 2

/**
 * @brief A generic Array List
 * Compared to others structures of the lib
 * this one is not freed when empty. \n
 */
typedef struct s_array_list {
    void ** array; /**< the array */
    int count; /**< Number of elements, the length */
    int size; /**< Total available space allocated */
    TypeDescriptor *td;
    char separator[MLCL_SEPARATOR_LEN];
} ArrayList;

/**
 * @brief The array list constructor
 * @param type_manifest
 * @return
 */
ArrayList * new_array_list(void (*type_manifest) (TypeDescriptor *));

int array_list_make_space(ArrayList *self);

int array_list_update_space(ArrayList *self);

/**
 * @brief Append allocated copy of the data to the end of the list
 * @param l
 * @param data
 * @return
 */
int array_list_append(ArrayList *self, void *data);

/**
 * @brief Insert data at index
 * @param l
 * @param i
 * @param data
 * @return
 */
int array_list_insert(ArrayList *self, int i, void *data);

/**
 * @brief At a given index, free and assign new data
 * @param l
 * @param i
 * @param data
 * @return
 */
int array_list_assign_i(ArrayList *self, int i, void *data);

/**
 * @brief Remove and return last value of the list
 * @param l
 * @return
 */
void * array_list_pop(ArrayList *self);

/**
 * @brief Remove and return data at given index of the list.
 * bad complexity, it has to shift all data to the left
 * @param l
 * @return
 */
void * array_list_pop_i(ArrayList *self, int i);

/**
 * @brief Naive search
 * @param l
 * @param data
 * @param res (pass NULL if unwanted)
 * @return 1 if exists, 0 else
 */
int array_list_search(ArrayList *self, const void *data, int (*filter) (const void *, const void*), int *r_index);

/**
 * @brief
 * @param data
 * @param res the index of the value will be return (pass NULL if unwanted)
 * @return 1 if exists, 0 else
 */
int array_list_binary_search(ArrayList *self, const void *data, int *r_index);

/**
 * Return Check if list is sorted
 * @param l
 * @param cmp comparison function
 * @return 1 or 0
 */
int array_list_is_sorted(const ArrayList *self, int (*cmp) (const void *, const void *));

void array_list_bubble_sort(ArrayList *self, int (*cmp) (const void *, const void *));
void array_list_selection_sort(ArrayList *self, int (*cmp) (const void *, const void *));
void array_list_insertion_sort(ArrayList *self, int (*cmp) (const void *, const void *));
void array_list_quick_sort(ArrayList *self, int (*cmp) (const void *, const void *));
void array_list_merge_sort(ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief print data at a given index
 * @param l
 * @param i
 */
void array_list_print_i(const ArrayList *self, int i);

/**
 * @brief Print on given stream the data at a given index
 * @param l
 * @param i
 */
void array_list_fprint_i(const ArrayList *self, FILE * stream, int i);

/**
 * @brief Print the list on stdout
 * @param l
 * @return
 */
void array_list_print(const ArrayList *self);

/**
 * @brief Print the list on the given stream
 * @param file
 * @param l
 * @return
 */
void array_list_fprint(const ArrayList *self, FILE * stream);

void array_list_empty(ArrayList *self, void (*data_free) (void *));

/**
 * @brief Free the array list
 * @param l
 */
void array_list_free(ArrayList **self);

void array_list_to_dot_(const ArrayList *self, FILE * stream);
void array_list_to_dot(const ArrayList *self, const char * path);


#endif /* MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H */
