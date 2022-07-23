/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_TYPES_H
#define MYLITTLECLIBRARY_MLCL_TYPES_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Interface for basic types and more complex structures of the lib.
 */
typedef struct s_type_descriptor {
    size_t data_size;
    void (*manifest) (struct s_type_descriptor*);
    int (*cmp) (const void *, const void *);
    void (*print) (const void *);
    void (*fprint) (FILE *, const void *);
    void * (*copy) (const void *);
    void (*free_data) (void **);
    int (*eq) (const void *, const void *);
    int (*lt) (const void *, const void *);
    int (*le) (const void *, const void *);
    int (*gt) (const void *, const void *);
    int (*ge) (const void *, const void *);
} TypeDescriptor;

/**
 * @brief Allocate a type descriptor for a given type manifest
 * @param type_manifest
 * @return a type descriptor
 */
TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor));

/**
 * Free a type descriptor
 * @param td
 */
void type_descriptor_free(TypeDescriptor ** td);

#endif /* MYLITTLECLIBRARY_MLCL_TYPES_H */
