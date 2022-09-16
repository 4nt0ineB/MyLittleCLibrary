/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_FILTER_H
#define MYLITTLECLIBRARY_MLCL_FILTER_H

#include "../../../include/core/MLCL_TypeDescriptor.h"
#include "../../../include/core/MLCL_basic_types.h"
#include "../../../include/core/MLCL_logic.h"
#include "stdlib.h"


/***************************************************
 * BFilter
 ***************************************************/

typedef int (*bfilter_f) (const void *strct, const void *field_value, ComparisonPredicate cmp_predicate);

/**
 * @brief a filter that apply on a field of a struct
 */
typedef struct BFilter{
    bfilter_f test; /**< test function to check condition on field of a structure with a Filter */
    void *field_value; /**< tmp value given to test a field with */
    ComparisonPredicate cmp_predicate; /**< EQ, NEQ, LT, ... */
    void (*value_free) (void *data); /**< Function to free the given field_value. Set NULL to avoid to free */
} BFilter;

/**
 * @brief
 * @param bfilter_function test function to check condition on field of a structure with a Filter
 * @param value a value to compare the field with
 * @param cmp_predicate how to compare the field with the value
 * @param value_free Function to free the given field_value. Set NULL to avoid to free
 * @return
 */
BFilter * new_bfilter(
        bfilter_f bfilter_function,
        void *field_value,
        ComparisonPredicate cmp_predicate,
        void (*value_free) (void *data)
);

/**
 * @brief
 * @param self
 */
void bfilter_free(BFilter **self);


/***************************************************
 * WFilter
 ***************************************************/

typedef int (*wfilter_f) (const void *strct, const void *data);

/**
 * @brief a more complex custom filter that apply on the struct
 */
typedef struct WFilter{
    wfilter_f test; /**< test function to check a custom condition on structure/type with a Filter */
    void *data; /**< tmp data to use if wanted */
    void (*data_free) (void *data); /**< Function to free the given data. Give function, or NULL to avoid to free */
} WFilter;

/**
 * @brief
 * @param wfilter_function
 * @param data  tmp data to use if wanted
 * @param data_free Function to free the given data. Give function, or NULL to avoid to free
 * @return
 */
WFilter * new_wfilter(
        wfilter_f wfilter_function,
        void *data,
        void (*data_free) (void *data)
);

/**
 * @brief
 * @param self
 */
void wfilter_free(WFilter **self);


/***************************************************
 * Filter
 ***************************************************/

/**
 * @brief a generic filter (interface for typed filters)
 * to be used in generic structures for remove, search, etc.
 */
typedef struct Filter {
    TypeDescriptor *td;
    BFilter **bfilters; /**< like "filter by " so b , for mnemonic purpose only */
    WFilter **wfilters; /**< like "filter with " so w, for mnemonic purpose only */
    int n_filters;
    int (*evaluate) (struct Filter *filter, void *strct);
} Filter;

/**
 * @brief Create a new filter
 * @param n_filters number of filters (each b and w types) the filter will have
 * @return
 */
Filter * new_filter(int n_filters);

/**
 * @brief Passes trough all bfilters and wfilters to check if the given struct/type validate all condition
 * @param self a pointer to a filter
 * @param strct the data of a struct
 * @return
 */
int filter_evaluate(Filter *self, void *data);
int filter_b_evaluate(Filter *self, void *data);
int filter_w_evaluate(Filter *self, void *data);

/**
 * @brief Free a filter
 * @param self
 */
void filter_free(Filter **self);


#endif /* MYLITTLECLIBRARY_MLCL_FILTER_H */
