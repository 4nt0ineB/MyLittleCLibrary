/*
   Created by antoine on 6/18/22.
*/

#include "../include/MLCL_Types.h"
#include <assert.h>
#include <stdio.h>

TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor)){
    TypeDescriptor * type_descriptor;
    assert(type_manifest);
    type_descriptor = (TypeDescriptor *) malloc(sizeof(TypeDescriptor));
    if(!type_descriptor) return NULL;
    printf("HEYYY\n\n");
    type_manifest(type_descriptor);
    return type_descriptor;
}

void type_descriptor_free(TypeDescriptor ** td){
    if(!*td) return;
    free(*td);
    *td = NULL;
}

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
    printf("%d", *(int *) x);
}

void int_free(void ** x){
    if(!*x) return;
    free((int *) x);
    *x = NULL;
}