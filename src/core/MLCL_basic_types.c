/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../include/core/MLCL_basic_types.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ############## str (char *) ############## */

char * new_str(const char *str){
    char *p;
    p = (char *) malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(p, str);
    return p;
}

void str_m(TypeDescriptor *type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(float);
    type_descriptor->manifest = str_m;
    type_descriptor->cmp = str_cmp;
    type_descriptor->print = str_print;
    type_descriptor->fprint = str_fprint;
    type_descriptor->copy = str_copy;
    type_descriptor->data_free = str_free;
    type_descriptor->eq = str_eq;
    type_descriptor->lt = str_lt;
    type_descriptor->le = str_le;
    type_descriptor->gt = str_gt;
    type_descriptor->ge = str_ge;
}

int str_cmp(const void *x, const void *y){
    return strcmp((const char *) x, (const char *) y);
}

int str_eq(const void *x, const void *y){
    return str_cmp(x, y) == 0;
}

int str_lt(const void *x, const void *y){
    return str_cmp(x, y) < 0;
}

int str_le(const void *x, const void *y){
    return str_cmp(x, y) <= 0;
}

int str_gt(const void *x, const void *y){
    return str_cmp(x, y) > 0;
}

int str_ge(const void *x, const void *y){
    return str_cmp(x, y) >= 0;
}

void str_print(const void *x){
    str_fprint(x, stdout);
}

void str_fprint(const void *x, FILE *stream){
    fprintf(stream, "%s",  (char *) x);
}

void * str_copy(const void *data){
    void * alloc_data;
    size_t data_size;
    data_size = sizeof(char) * (strlen((char *) data) + 1);
    alloc_data = (char *) calloc(1, data_size);
    if(!alloc_data) return NULL;
    memcpy(alloc_data, data, data_size);
    return alloc_data;
}

void str_free(void *x){
    if(!x) return;
    /*free((char *)(*x));*/
    free(x);
}


/* ############## char ############## */

char * new_char(char c){
    char *p;
    p = (char *) malloc(sizeof(char));
    *p = c;
    return p;
}

void char_m(TypeDescriptor *type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(float);
    type_descriptor->manifest = char_m;
    type_descriptor->cmp = char_cmp;
    type_descriptor->print = char_print;
    type_descriptor->fprint = char_fprint;
    type_descriptor->copy = char_copy;
    type_descriptor->data_free = char_free;
    type_descriptor->eq = char_eq;
    type_descriptor->lt = char_lt;
    type_descriptor->le = char_le;
    type_descriptor->gt = char_gt;
    type_descriptor->ge = char_ge;
}

int char_cmp(const void *x, const void *y){
    return (*(char *) x == *(char *) y) ? 0 : (*(char *) x < *(char *) y) ? -1 :  1;
}

int char_eq(const void *x, const void *y){
    return (*(char *) x) == (*(char *) y);
}

int char_lt(const void *x, const void *y){
    return (*(char *) x) < (*(char *) y);
}

int char_le(const void *x, const void *y){
    return (*(char *) x) <= (*(char *) y);
}

int char_gt(const void *x, const void *y){
    return (*(char *) x) > (*(char *) y);
}

int char_ge(const void *x, const void *y){
    return (*(char *) x) >= (*(char *) y);
}

void char_print(const void * x){
    char_fprint(x, stdout);
}

void char_fprint(const void *x, FILE *stream){
    fprintf(stream, "%c",  *(char *) x);
}

void * char_copy(const void *data){
    void * alloc_data;
    size_t data_size;
    data_size = sizeof(char);
    alloc_data = calloc(1, data_size);
    if(!alloc_data) return NULL;
    memcpy(alloc_data, data, data_size);
    return alloc_data;
}

void char_free(void *x){
    if(!x) return;
    free(x);
}

/* ############## int ############## */

int * new_int(int x){
    int *p;
    p = (int *) malloc(sizeof(int));
    *p = x;
    return p;
}

void int_m(TypeDescriptor *type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(int);
    type_descriptor->manifest = int_m;
    type_descriptor->cmp = int_cmp;
    type_descriptor->print = int_print;
    type_descriptor->fprint = int_fprint;
    type_descriptor->copy = int_copy;
    type_descriptor->data_free = int_free;
    type_descriptor->eq = int_eq;
    type_descriptor->lt = int_lt;
    type_descriptor->le = int_le;
    type_descriptor->gt = int_gt;
    type_descriptor->ge = int_ge;
}

int int_cmp(const void * x, const void * y){
    return ((*(int *) x) == (*(int *) y)) ? 0 : ((*(int *) x) < (*(int *) y)) ? -1 : 1;
}

int int_eq(const void * x, const void * y){
    return (*(int *) x) == (*(int *) y);
}

int int_lt(const void * x, const void * y){
    return (*(int *) x) < (*(int *) y);
}

int int_le(const void * x, const void * y){
    return (*(int *) x) <= (*(int *) y);
}

int int_gt(const void * x, const void * y){
    return (*(int *) x) > (*(int *) y);
}

int int_ge(const void * x, const void * y){
    return (*(int *) x) >= (*(int *) y);
}

void int_print(const void * x){
    int_fprint(x, stdout);
}

void int_fprint(const void *x, FILE *stream){
    fprintf(stream, "%d",  *(int *) x);
}

void * int_copy(const void *data){
    void * alloc_data;
    size_t data_size;
    data_size = sizeof(int);
    alloc_data = calloc(1, data_size);
    if(!alloc_data) return NULL;
    memcpy(alloc_data, data, data_size);
    return alloc_data;
}

void int_free(void *x){
    if(!x) return;
    free(x);
}

/* ############## float ############## */

float * new_float(float x){
    float *p;
    p = (float *) malloc(sizeof(float));
    *p = x;
    return p;
}

void float_m(TypeDescriptor *type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(float);
    type_descriptor->manifest = float_m;
    type_descriptor->cmp = float_cmp;
    type_descriptor->print = float_print;
    type_descriptor->fprint = float_fprint;
    type_descriptor->copy = float_copy;
    type_descriptor->data_free = float_free;
    type_descriptor->eq = float_eq;
    type_descriptor->lt = float_lt;
    type_descriptor->le = float_le;
    type_descriptor->gt = float_gt;
    type_descriptor->ge = float_ge;
}

int float_cmp(const void *x, const void *y){
    return (*(float *) x == *(float *) y) ? 0 : (*(float *) x < *(float *) y) ? -1 :  1;
}

int float_eq(const void *x, const void *y){
    return (*(float *) x) == (*(float *) y);
}

int float_lt(const void *x, const void *y){
    return (*(float *) x) < (*(float *) y);
}

int float_le(const void *x, const void *y){
    return (*(float *) x) <= (*(float *) y);
}

int float_gt(const void *x, const void *y){
    return (*(float *) x) > (*(float *) y);
}

int float_ge(const void *x, const void *y){
    return (*(float *) x) >= (*(float *) y);
}

void float_print(const void * x){
    float_fprint(x, stdout);
}

void float_fprint(const void *x, FILE *stream){
    fprintf(stream, "%.2f",  *(float *) x);
}

void * float_copy(const void *data){
    void * alloc_data;
    size_t data_size;
    data_size = sizeof(float);
    alloc_data = calloc(1, data_size);
    if(!alloc_data) return NULL;
    memcpy(alloc_data, data, data_size);
    return alloc_data;
}

void float_free(void *x){
    if(!x) return;
    free(x);
}


