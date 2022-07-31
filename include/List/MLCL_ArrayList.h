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
 * this one is not freed when empty.
 */
typedef struct s_array_list {
    void ** array; /**< the array */
    int count; /**< Number of elements, the length */
    int size; /**< Total available space allocated */
    struct s_array_list_descriptor * d;
} ArrayList;

/**
 * @brief
 */
typedef struct s_array_list_descriptor {
    TypeDescriptor * type_descriptor;
    int (*append) (ArrayList *, const void *);
    void (*print_at) (const ArrayList *, int);
    void (*fprint_at) (FILE *, const ArrayList *, int);
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
 * @brief
 * @param l
 * @param data
 * @return
 */
int array_list_append(ArrayList *l, const void * data);

/**
 * @brief
 * @param l
 * @param i
 */
void array_list_print_at(const ArrayList *l, int i);

/**
 * @brief
 * @param l
 * @param i
 */
void array_list_fprint_at(FILE * file, const ArrayList *l, int i);

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
void array_list_fprint(FILE * file, const ArrayList *l);

/**
 * @brief
 * @param ald
 */
void array_list_free_descriptor(ArrayListDescriptor ** ald);

/**
 * @brief
 * @param l
 */
void array_list_free(ArrayList ** l);


#endif /* MYLITTLECLIBRARY_MLCL_DYNAMICARRAY_H */
