/*
 *   This file is part of the MLCL Library.
 *
 *   Copyright (C) 2022 Antoine Bastos
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H
#define MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H

#include "MLCL_TypeDescriptor.h"

/* ############## char ############## */
/**
 * @brief The char manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void char_manifest(TypeDescriptor * type_descriptor);

/**
 *
 * @param x
 * @param y
 * @return
 */
int char_cmp(const void * x, const void * y);

/**
 *
 * @param x
 */
void char_print(const void * x);

/**
 *
 * @param x
 */
void char_free(void ** x);
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

/* ############## float ############## */
/**
 * @brief The float manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void float_manifest(TypeDescriptor * type_descriptor);

/**
 *
 * @param x
 * @param y
 * @return
 */
int float_cmp(const void * x, const void * y);

/**
 *
 * @param x
 */
void float_print(const void * x);

/**
 *
 * @param x
 */
void float_free(void ** x);
/* ############################ */

#endif /* MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H */
