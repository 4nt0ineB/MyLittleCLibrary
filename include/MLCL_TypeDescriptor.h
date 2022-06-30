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

/**
 * @brief Interface for basic types and more complex structures of the lib.
 */
typedef struct s_type_descriptor {
    size_t data_size;
    int (*cmp) (const void * x, const void * y);
    void (*print) (const void * data);
    void (*free_data) (void ** data);
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

/* ############## int ############## */
/**
 * @brief The int manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void int_manifest(TypeDescriptor * type_descriptor);

/**
 *
 * @param x
 * @param y
 * @return
 */
int int_cmp(const void * x, const void * y);

/**
 *
 * @param x
 */
void int_print(const void * x);

/**
 *
 * @param x
 */
void int_free(void ** x);
/* ############################ */

/* ############## int ############## */
/**
 * @brief The int manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void int_manifest(TypeDescriptor * type_descriptor);

/**
 *
 * @param x
 * @param y
 * @return
 */
int int_cmp(const void * x, const void * y);

/**
 *
 * @param x
 */
void int_print(const void * x);

/**
 *
 * @param x
 */
void int_free(void ** x);
/* ############################ */

#endif /* MYLITTLECLIBRARY_MLCL_TYPES_H */
