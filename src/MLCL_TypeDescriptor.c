/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../include/MLCL_TypeDescriptor.h"
#include <assert.h>
#include <stdio.h>

TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor)){
    TypeDescriptor * type_descriptor;
    assert(type_manifest);
    type_descriptor = (TypeDescriptor *) malloc(sizeof(TypeDescriptor));
    if(!type_descriptor) return NULL;
    type_manifest(type_descriptor);
    /* @Todo: check if manifest gave all needed functions */
    return type_descriptor;
}

void type_descriptor_free(TypeDescriptor ** td){
    if(*td){
        free(*td);
        *td = NULL;
    }
}
