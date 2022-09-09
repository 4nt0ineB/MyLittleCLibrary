/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_TYPES_H
#define MYLITTLECLIBRARY_MLCL_TYPES_H

#include <stdlib.h>
#include <stdio.h>

#define MLCL_TYPE_DESCRIPTOR_SEPARATOR_LEN 16
#define MLCL_SEPARATOR_LEN 16

/**
 * @brief Interface for all types manipulated by the structs of the library.
 */
typedef struct TypeDescriptor {
    size_t data_size;
    void (*manifest) (struct TypeDescriptor*); /**<  type_manifest used to make the type descriptor */
    int (*cmp) (const void *, const void *); /**< Comparison function */
    void (*print) (const void *); /**< Printing function, shorthand to fprint */
    void (*fprint) (const void *, FILE *); /**< Printing function on given stream */
    void * (*copy) (const void *); /**< Function to allocate a copy of a data of the associated type */
    void (*data_free) (void *); /**< Function to free the data */
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
TypeDescriptor * new_type_descriptor(void (*type_manifest) (TypeDescriptor *type_descriptor));

/**
 * Free a type descriptor
 * @param td type descriptor
 */
void type_descriptor_free(TypeDescriptor **td);

#endif /* MYLITTLECLIBRARY_MLCL_TYPES_H */
