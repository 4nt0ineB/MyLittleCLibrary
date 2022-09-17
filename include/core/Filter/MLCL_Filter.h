/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_FILTER_H
#define MYLITTLECLIBRARY_MLCL_FILTER_H

#include "../MLCL_TypeDescriptor.h"
#include "../MLCL_primitive_types.h"
#include "../MLCL_logic.h"
#include "stdlib.h"

/***************************************************
 * FilterConditon
 ***************************************************/

typedef int (*cfilter_f) (void *strct, void *field_value, comparison_predicate_t cmp_predicate);

/**
 * @brief a test that apply on a struct, field of a struct
 */
typedef struct ConditionalFilter{
    cfilter_f function; /**< test function to check condition on field of a structure with a Filter */
    void *field_value; /**< tmp value given to test a field with */
    comparison_predicate_t cmp_predicate; /**< EQ, NEQ, LT, ... */
    void (*value_free) (void *data); /**< Function to free the given field_value. Set NULL to avoid to free */
} ConditionalFilter;

/**
 * @brief
 * @param filter_function a function to check condition on structure/type with a Filter
 * @param value a value to compare the field with
 * @param cmp_predicate how to compare the field with the value
 * @param value_free Function to free the given field_value. Set NULL to avoid to free
 * @return
 */
ConditionalFilter * new_condition(
        cfilter_f filter_function,
        void *field_value,
        comparison_predicate_t cmp_predicate,
        void (*value_free) (void *data)
);

/**
 * @brief
 * @param self
 */
void conditional_filter_free(ConditionalFilter **self);

/***************************************************
 * Filter
 ***************************************************/

/**
 * @brief a generic filter (interface for typed filters)
 * to be used in generic structures for remove, search, etc.
 */
typedef struct Filter {
    TypeDescriptor *td;
    ConditionalFilter **conditions;
    int n_conditions;
    int (*evaluate) (struct Filter *filter, void *strct);
} Filter;

/**
 * @brief Create a new filter
 * @param n_filters number of filters (each b and w types) the filter will have
 * @return
 */
Filter * new_filter(int n_conditions);

/**
 * @brief Passes trough all conditions to check if the given struct/type validate all condition
 * @param self a pointer to a filter
 * @param strct the data of a struct
 * @return
 */
int filter_evaluate(Filter *self, void *data);

/**
 * @brief Free a filter
 * @param self
 */
void filter_free(Filter **self);


#endif /* MYLITTLECLIBRARY_MLCL_FILTER_H */
