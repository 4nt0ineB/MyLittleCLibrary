/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H
#define MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H

#include "MLCL_TypeDescriptor.h"
#include "MLCL_logic.h"
#include <stdio.h>

/* ############## str (char *) ############## */
char * new_str(const char *str);
void str_m(TypeDescriptor *type_descriptor);
int str_cmp(const void *x, const void *y);
int str_eq(const void *x, const void *y);
int str_lt(const void *x, const void *y);
int str_le(const void *x, const void *y);
int str_gt(const void *x, const void *y);
int str_ge(const void *x, const void *y);
void str_print(const void *x);
void str_fprint(const void *x, FILE *stream);
void * str_copy(const void *data);
void str_free(void *x);

/**
 *
 * @param x the string to be compared
 * @param y the string to compare to
 * @param cmp_predicate NEQ, EQ, LT, ...
 * @return
 */
int str_filter(void *x, void *y, comparison_predicate_t cmp_predicate);

/* ############## char ############## */
char * new_char(char x);
/**
 * @brief The char manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void char_m(TypeDescriptor * type_descriptor);

/**
 * @brief
 * @param x
 * @param y
 * @return
 */
int char_cmp(const void *x, const void *y);

int char_eq(const void *x, const void *y);
int char_lt(const void *x, const void *y);
int char_le(const void *x, const void *y);
int char_gt(const void *x, const void *y);
int char_ge(const void *x, const void *y);

/**
 * @brief
 * @param x
 */
void char_print(const void *x);

/**
 * @brief
 * @param x
 * @param file
 */
void char_fprint(const void *x, FILE *stream);

/**
 * Copy the given data to a new address
 * @param data data considered as a char
 * @return pointer to a new allocated copy of the given data
 */
void * char_copy(const void *data);

/**
 * @brief
 * @param x
 */
void char_free(void *x);

/**
 *
 * @param x the char to be compared
 * @param y the char to compare to
 * @param cmp_predicate NEQ, EQ, LT, ...
 * @return
 */
int char_filter(void *x, void *y, comparison_predicate_t cmp_predicate);

/* ############## int ############## */

int * new_int(int x);

/**
 * @brief The int manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void int_m(TypeDescriptor * type_descriptor);

/**
 * @brief
 * @param x
 * @param y
 * @return
 */
int int_cmp(const void *x, const void *y);

int int_eq(const void *x, const void *y);
int int_lt(const void *x, const void *y);
int int_le(const void *x, const void *y);
int int_gt(const void *x, const void *y);
int int_ge(const void *x, const void *y);

/**
 * @brief
 * @param x
 */
void int_print(const void *x);

/**
 *
 * @param x
 */
void int_fprint(const void *x, FILE *stream);

/**
 * Copy the given data to a new address
 * @param data data considered as a int
 * @return pointer to a new allocated copy of the given data
 */
void * int_copy(const void *data);

/**
 * @brief
 * @param x
 * @param file
 */
void int_free(void *x);

/**
 *
 * @param x the int to be compared
 * @param y the int to compare to
 * @param cmp_predicate NEQ, EQ, LT, ...
 * @return
 */
int int_filter(void *x, void *y, comparison_predicate_t cmp_predicate);

/* ############## float ############## */
float * new_float(float x);

/**
 * @brief The float manifest assign its respective functions according
 * to the required ones by the type interface TypeDescriptor
 * @param type_descriptor
 */
void float_m(TypeDescriptor *type_descriptor);

/**
 * @brief
 * @param x
 * @param y
 * @return
 */
int float_cmp(const void *x, const void *y);

int float_eq(const void *x, const void *y);
int float_lt(const void *x, const void *y);
int float_le(const void *x, const void *y);
int float_gt(const void *x, const void *y);
int float_ge(const void *x, const void *y);

/**
 * @brief
 * @param x
 */
void float_print(const void *x);

/**
 * @brief
 * @param x
  * @param file
 */
void float_fprint(const void *x, FILE *stream);

/**
 * Copy the given data to a new address
 * @param data data considered as a float
 * @return pointer to a new allocated copy of the given data
 */
void * float_copy(const void *data);

/**
 * @brief
 * @param x
 */
void float_free(void *x);

/**
 *
 * @param x the float to be compared
 * @param y the float to compare to
 * @param cmp_predicate NEQ, EQ, LT, ...
 * @return
 */
int float_filter(void *x, void *y, comparison_predicate_t cmp_predicate);

#endif /* MYLITTLECLIBRARY_MLCL_BASIC_TYPES_H */
