/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../include/core/MLCL_TypeDescriptor.h"
#include <assert.h>
#include <stdio.h>

TypeDescriptor * new_type_descriptor(void (* type_manifest) (TypeDescriptor * type_descriptor)){
    TypeDescriptor * type_descriptor;
    assert(type_manifest);
    type_descriptor = (TypeDescriptor *) malloc(sizeof(TypeDescriptor));
    if(!type_descriptor) return NULL;
    type_manifest(type_descriptor);
    return type_descriptor;
}

void type_descriptor_free(TypeDescriptor **td){
    if(!*td) return;
    free(*td);
    *td = NULL;
}
