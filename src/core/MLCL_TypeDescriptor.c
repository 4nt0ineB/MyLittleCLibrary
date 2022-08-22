/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *    This Library is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This Library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this Library.  If not, see <http://www.gnu.org/licenses/>.
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
