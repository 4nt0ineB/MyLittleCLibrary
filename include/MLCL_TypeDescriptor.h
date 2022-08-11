/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
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

#ifndef MYLITTLECLIBRARY_MLCL_TYPES_H
#define MYLITTLECLIBRARY_MLCL_TYPES_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Interface for all types manipulated by the structs of the library.
 */
typedef struct s_type_descriptor {
    size_t data_size;
    char separator[6];
    void (*manifest) (struct s_type_descriptor*); /**<  type_manifest used to make the type descriptor */
    int (*cmp) (const void *, const void *); /**< Comparison function */
    void (*print) (const void *); /**< Printing function, shorthand to fprint */
    void (*fprint) (FILE *, const void *); /**< Printing function on given stream */
    void * (*copy) (const void *); /**< Function to allocate a copy of a data of the associated type */
    void (*free_data) (void **); /**< Function to free the data */
    int (*eq) (const void *, const void *); /**< equal test */
    int (*lt) (const void *, const void *); /**< less than test */
    int (*le) (const void *, const void *); /**< less equal test */
    int (*gt) (const void *, const void *); /**< greater than test */
    int (*ge) (const void *, const void *); /**< greater equal test */
} TypeDescriptor;

/**
 * @brief Allocate a type descriptor for a given type manifest
 * @param type_manifest is a function that assign the function allowing the manipulation of the type to the type descriptor
 * interface
 * @return a type descriptor
 */
TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor));

/**
 * Free a type descriptor
 * @param td type descriptor
 */
void type_descriptor_free(TypeDescriptor ** td);

#endif /* MYLITTLECLIBRARY_MLCL_TYPES_H */
