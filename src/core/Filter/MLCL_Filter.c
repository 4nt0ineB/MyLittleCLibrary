/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/core/Filter/MLCL_Filter.h"
#include "assert.h"


/***************************************************
 * ConditionalFilter
 ***************************************************/

ConditionalFilter * new_condition(cfilter_f filter_function, void *field_value, comparison_predicate_t cmp_predicate,
                       void (*value_free) (void *data)){
    ConditionalFilter *cfilter;
    if(!filter_function) return NULL;
    cfilter = (ConditionalFilter *) malloc(sizeof(ConditionalFilter));
    if(!cfilter) return NULL;
    cfilter->function = filter_function;
    cfilter->cmp_predicate = cmp_predicate;
    cfilter->field_value = field_value;
    cfilter->value_free = value_free;
    return cfilter;
}

void conditional_filter_free(ConditionalFilter **self){
    if(!*self) return;
    if((*self)->value_free && (*self)->field_value)
        (*self)->value_free((*self)->field_value);
    free(*self);
    *self = NULL;
}

/***************************************************
 * Filter
 ***************************************************/

Filter * new_filter(int n_conditions){
    Filter *filter;
    if(n_conditions < 1) return NULL;
    filter = (Filter *) malloc(sizeof(Filter));
    if(!filter) return NULL;
    filter->conditions = (ConditionalFilter **) calloc(n_conditions, sizeof(ConditionalFilter *));
    if(!filter->conditions){
        filter_free(&filter);
        return NULL;
    }
    filter->n_conditions = n_conditions;
    filter->evaluate = filter_evaluate;
    return filter;
}

int filter_evaluate(Filter *self, void *data){
    ConditionalFilter *filter;
    int i;
    if(!self || !data) return 0;
    for(i = 0; i < self->n_conditions; i++){
        filter = self->conditions[i];
        if(filter){
            if(!filter->function(data, filter->field_value, filter->cmp_predicate))
                return 0;
        }
    }
    return 1;
}

void filter_clear(Filter *self){
    int i;
    if(!self) return;
    for(i = 0; i < self->n_conditions; i++)
        if(self->conditions[i])
            conditional_filter_free(&self->conditions[i]);
}

void filter_free(Filter **self){
    if(!*self) return;
    filter_clear(*self);
    free((*self)->conditions);
    free(*self);
    *self = NULL;
}