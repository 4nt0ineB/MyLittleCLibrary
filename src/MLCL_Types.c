/*
   Created by antoine on 6/18/22.
*/

#include "../include/MLCL_Types.h"
#include <assert.h>
#include <stdio.h>

TypeDescriptor * new_t_desrciptor(void (* type_manifest) (TypeDescriptor * type_descriptor)){
    TypeDescriptor * type_descriptor;
    assert(type_manifest);
    type_descriptor = (TypeDescriptor *) malloc(sizeof(type_descriptor));
    if(!type_descriptor) return NULL;
    type_manifest(type_descriptor);
    return type_descriptor;
}

void int_manifest(TypeDescriptor * type_descriptor){
    type_descriptor->data_size = sizeof(int);
    type_descriptor->cmp = int_cmp;
    type_descriptor->print = int_print;
}

int int_cmp(const void * x, const void * y){
    return (x == y) ? 0 : (x < y) ? -1 :  1;
}

void int_print(const void * x){
    printf("%d", *(int *) x);
}