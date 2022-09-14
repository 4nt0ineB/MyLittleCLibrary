/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Stack/MLCL_Stack.h"

Stack * new_stack(void (*type_manifest) (TypeDescriptor *)){
    return new_list(CIRCULAR_DOUBLE_LINKED_LIST, type_manifest);
}

int stack_add(Stack *self, void *data){
    return list_prepend(self, data);
}

void * stack_peek(const Stack *self){
    return list_head_peek(self);
}

void * stack_pop(Stack *self){
    return list_shift(self);
}

int stack_is_empty(const Stack *self){
    return !list_length(self);
}

void stack_free(Stack **self){
    list_free(self);
}
