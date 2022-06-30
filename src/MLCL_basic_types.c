/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_basic_types.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/* ############## char ############## */

void char_manifest(TypeDescriptor * type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(float);
    type_descriptor->cmp = char_cmp;
    type_descriptor->print = char_print;
    type_descriptor->free_data = char_free;
}

int char_cmp(const void * x, const void * y){
    return (*(char *) x == *(char *) y) ? 0 : (*(char *) x < *(char *) y) ? -1 :  1;
}

void char_print(const void * x){
    printf("%c",  *(char *) x);
}

void char_free(void ** x){
    if(!*x) return;
    free(*x);
    *x = NULL;
}

/* ############################ */

/* ############## int ############## */

void int_manifest(TypeDescriptor * type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(int);
    type_descriptor->cmp = int_cmp;
    type_descriptor->print = int_print;
    type_descriptor->free_data = int_free;
}

int int_cmp(const void * x, const void * y){
    return (*(int *) x == *(int *) y) ? 0 : (*(int *) x < *(int *) y) ? -1 :  1;
}

void int_print(const void * x){
    printf("%d",  *(int *) x);
}

void int_free(void ** x){
    if(!*x) return;
    free(*x);
    *x = NULL;
}

/* ############################ */

/* ############## float ############## */

void float_manifest(TypeDescriptor * type_descriptor){
    assert(type_descriptor);
    type_descriptor->data_size = sizeof(float);
    type_descriptor->cmp = float_cmp;
    type_descriptor->print = float_print;
    type_descriptor->free_data = float_free;
}

int float_cmp(const void * x, const void * y){
    return (*(float *) x == *(float *) y) ? 0 : (*(float *) x < *(float *) y) ? -1 :  1;
}

void float_print(const void * x){
    printf("%.2f",  *(float *) x);
}

void float_free(void ** x){
    if(!*x) return;
    free(*x);
    *x = NULL;
}

/* ############################ */

