/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "MLCL_Filter.h"
#include "assert.h"

/***************************************************
 * BFilter
 ***************************************************/


BFilter * new_bfilter(bfilter_f bfilter_function, void *field_value, ComparisonPredicate cmp_predicate,
                       void (*value_free) (void *data)){
    BFilter *bfilter;
    if(!bfilter_function) return NULL;
    bfilter = (BFilter *) malloc(sizeof(BFilter));
    if(!bfilter) return NULL;
    bfilter->test = bfilter_function;
    bfilter->cmp_predicate = cmp_predicate;
    bfilter->field_value = field_value;
    bfilter->value_free = value_free;
    return bfilter;
}

void bfilter_free(BFilter **self){
    if(!*self) return;
    if((*self)->value_free && (*self)->field_value)
        (*self)->value_free((*self)->field_value);
    free(*self);
    *self = NULL;
}


/***************************************************
 * WFilter
 ***************************************************/

WFilter * new_wfilter(wfilter_f wfilter_function, void *data, void (*data_free) (void *data)){
    WFilter *wfilter;
    if(!wfilter_function) return NULL;
    wfilter = (WFilter *) malloc(sizeof(WFilter));
    if(!wfilter) return NULL;
    wfilter->test = wfilter_function;
    wfilter->data = data;
    wfilter->data_free = data_free;
    return wfilter;
}

void wfilter_free(WFilter **self){
    if(!*self) return;
    if((*self)->data_free && (*self)->data)
        (*self)->data_free((*self)->data);
    free(*self);
    *self = NULL;
}


/***************************************************
 * Filter
 ***************************************************/

Filter * new_filter(int n_filters){
    Filter *filter;
    assert(n_filters > 1);
    filter = (Filter *) malloc(sizeof(Filter));
    if(!filter) return NULL;
    filter->bfilters = (BFilter **) calloc(n_filters, sizeof(BFilter *));
    filter->wfilters = (WFilter **) calloc(n_filters, sizeof(WFilter *));
    if(!filter->bfilters || filter->wfilters){
        filter_free(&filter);
        return NULL;
    }
    filter->n_filters = n_filters;
    filter->evaluate = filter_evaluate;
    return filter;
}

int filter_evaluate(Filter *self, void *data){
    if(!self || !data) return 0;
    return filter_b_evaluate(self, data) && filter_b_evaluate(self, data);
}

int filter_b_evaluate(Filter *self, void *data){
    BFilter *filter;
    int i;
    if(!self || !data) return 0;
    for(i = 0; i < self->n_filters; i++){
        filter = self->bfilters[i];
        if(filter){
            if(!filter->test(data, filter->field_value, filter->cmp_predicate))
                return 0;
        }
    }
    return 1;
}

int filter_w_evaluate(Filter *self, void *data){
    WFilter *filter;
    int i;
    if(!self || !data) return 0;
    for(i = 0; i < self->n_filters; i++){
        filter = self->wfilters[i];
        if(filter){
            if(!filter->test(data, filter->data))
                return 0;
        }
    }
    return 1;
}

void filter_free(Filter **self){
    int i;
    if(!*self) return;
    for(i = 0; i <= (*self)->n_filters; i++)
        if((*self)->bfilters[i])
            bfilter_free(&(*self)->bfilters[i]);
    for(i = 0; i <= (*self)->n_filters; i++)
        if((*self)->bfilters[i])
            bfilter_free(&(*self)->bfilters[i]);
    free((*self)->bfilters);
    free((*self)->wfilters);
    free(*self);
    *self = NULL;
}