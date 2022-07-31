/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H
#define MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H

#include "../MLCL_TypeDescriptor.h"

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
    struct s_array_list_descriptor * d;
} ArrayList;

/**
 * @brief Descriptor of the array list
 * Even if not required for this type of struct
 * we keep the general syntax for mnemonic purpose mystruct->d(escriptor)->myfunction
 */
typedef struct s_array_list_descriptor {
    TypeDescriptor * type_descriptor;
    int (*append) (ArrayList *, const void *);
    void * (*pop) (ArrayList *);
    void * (*pop_i) (ArrayList *, int i);
    int (*is_sorted) (const ArrayList *, int (*cmp) (const void *, const void *));
    /* Sorting */
    void (*bublle_sort) (ArrayList *, int (*cmp) (const void *, const void *));
    void (*selection_sort) (ArrayList *, int (*cmp) (const void *, const void *));
    void (*quick_sort) (ArrayList *, int (*cmp) (const void *, const void *));
    void (*merge_sort) (ArrayList *, int (*cmp) (const void *, const void *));
    /* Print */
    void (*print_i) (const ArrayList *, int);
    void (*fprint_i) (FILE *, const ArrayList *, int);
    void (*print) (const ArrayList *);
    void (*fprint) (FILE *, const ArrayList *);
    void (*free) (ArrayList **);

} ArrayListDescriptor;

/**
 * @brief Return a new allocated array list pointer for a given array list descriptor
 */
ArrayList * array_list_builder(ArrayListDescriptor * descriptor);

/**
 * @brief The array list constructor
 * @param type_manifest
 * @return
 */
ArrayList * new_array_list(void (*type_manifest) (TypeDescriptor *));

/**
 * @brief Append allocated copy of the data to the end of the list
 * @param l
 * @param data
 * @return
 */
int array_list_append(ArrayList *l, const void * data);

/**
 * @brief Remove and return last value of the list
 * @param l
 * @return
 */
void * array_list_pop(ArrayList *l);

/**
 * @brief Remove and return data at given index of the list.
 * bad complexity, it has to shift all data to the left
 * @param l
 * @return
 */
void * array_list_pop_i(ArrayList *l, int i);

/**
 * Return Check if list is sorted
 * @param l
 * @param cmp comparison function
 * @return 1 or 0
 */
int array_list_is_sorted(const ArrayList *l, int (*cmp) (const void *, const void *));

void array_list_bublle_sort(ArrayList *l, int (*cmp) (const void *, const void *));
void array_list_selection_sort(ArrayList *l, int (*cmp) (const void *, const void *));
void array_list_quick_sort(ArrayList *l, int (*cmp) (const void *, const void *));
void array_list_merge_sort(ArrayList *l, int (*cmp) (const void *, const void *));

/**
 * @brief print data at a given index
 * @param l
 * @param i
 */
void array_list_print_i(const ArrayList *l, int i);

/**
 * @brief Print on given stream the data at a given index
 * @param l
 * @param i
 */
void array_list_fprint_i(FILE * stream, const ArrayList *l, int i);

/**
 * @brief Print the list on stdout
 * @param l
 * @return
 */
void array_list_print(const ArrayList *l);

/**
 * @brief Print the list on the given stream
 * @param file
 * @param l
 * @return
 */
void array_list_fprint(FILE * stream, const ArrayList *l);

/**
 * @brief free the descriptor of the array list
 * @param ald
 */
void array_list_free_descriptor(ArrayListDescriptor ** ald);

/**
 * @brief Free the array list
 * @param l
 */
void array_list_free(ArrayList ** l);


#endif /* MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H */
