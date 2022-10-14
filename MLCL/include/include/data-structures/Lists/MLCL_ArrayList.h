/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H
#define MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H

#include "../../core/MLCL_TypeDescriptor.h"
#include "../../core/Filter/MLCL_Filter.h"

#define ARRAY_LIST_BLOCK_SIZE 10
#define ARRAY_LIST_MAX_EMPTY_BLOCKS 2

/**
 * @brief A generic Array List
 * Compared to others structures of the lib
 * this one is not freed when empty. \n
 */
typedef struct s_array_list {
    void ** array; /**< the array */
    int length; /**< Number of elements, the length */
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

/**
 * @brief Check if there is enough space list according to defined block size
 */
int array_list_make_space(ArrayList *self);

/**
 * @brief Realloc array if there is enough unused space according to defined block size
 */
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
 * @param self
 * @param i
 * @param data
 * @return
 */
int array_list_insert(ArrayList *self, int i, void *data);

/**
 * @brief At a given index, free and assign new data
 * @param self
 * @param i
 * @param data
 * @return
 */
int array_list_assign_i(ArrayList *self, int i, void *data);

/**
 * @brief Remove and return last value of the list
 * @param self
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
 * @param self
 * @param filter
 * @param r_index (pass NULL if unwanted)
 * @return 1 if exists, 0 else
 */
int array_list_search(ArrayList *self, Filter *filter, int *r_index);

/**
 * @brief Return index of data validating the filter
 * @param self
 * @param filter
 * @return @todo a ArrayList of found data, NULL if nothing found
 */
ArrayList * array_list_search_all(ArrayList *self, Filter *filter);

/**
 * @brief
 * @param self
 * @param data
 * @param r_index the index of the value will be return (pass NULL if unwanted)
 * @return 1 if exists, 0 else
 */
int array_list_binary_search(ArrayList *self, const void *data, int *r_index);

/**
 * @brief extract the first data corresponding
 * @param self
 * @param filter
 * @return first data validating the filter
 */
void * array_list_extract(ArrayList *self, Filter *filter);

/**
 * @brief extract all data corresponding
 * @param self
 * @param filter
 * @return
 */
ArrayList * array_list_extract_all(ArrayList *self, Filter *filter);

int array_list_remove_w(ArrayList *self, Filter *filter, void (*data_free) (void *));
int array_list_remove(ArrayList *self, Filter *filter);
int array_list_remove_all_w(ArrayList *self, Filter *filter, void (*data_free) (void *));
int array_list_remove_all(ArrayList *self, Filter *filter);

/**
 * Return Check if list is sorted according to given cmp function
 * @param self
 * @param cmp comparison function (must return 1 or 0)
 * @return 1 or 0
 */
int array_list_is_sorted(const ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief Sort array list with bubble sort algorithm
 * @param self
 * @param cmp
 */
void array_list_bubble_sort(ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief Sort array list with selection sort algorithm
 * @param self
 * @param cmp
 */
void array_list_selection_sort(ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief Sort array list with insertion sort algorithm
 * @param self
 * @param cmp
 */
void array_list_insertion_sort(ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief Sort array list with quick sort algorithm
 * @param self
 * @param cmp
 */
void array_list_quick_sort(ArrayList *self, int (*cmp) (const void *, const void *));

/**
 * @brief Sort array list with merge sort algorithm
 * @param self
 * @param cmp
 */
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
 * @param self
 * @param stream
 * @return
 */
void array_list_fprint(const ArrayList *self, FILE *stream);

/**
 * Empty the array of all data of the array
 * @param self
 * @param data_free function to free the data
 */
void array_list_empty(ArrayList *self, void (*data_free) (void *));

/**
 * @brief Free the array list
 * @param self
 * @param data_free function to free the data
 */
void array_list_free_w(ArrayList **self, void (*data_free) (void *));

/**
 * @brief Free the array list
 * @param self
 */
void array_list_free(ArrayList **self);

/**
 * @brief Write on stream the representation of array list formatted to dot
 * @param self
 * @param stream
 */
void array_list_to_dot_(const ArrayList *self, FILE *stream);

/**
 * @brief Write on file the representation of array list formatted to dot
 * @param self
 * @param path name of the file
 */
void array_list_to_dot(const ArrayList *self, const char *path);


#endif /* MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H */
