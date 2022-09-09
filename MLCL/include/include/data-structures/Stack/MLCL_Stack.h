/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_STACK_H
#define MYLITTLECLIBRARY_MLCL_STACK_H

#include "../Lists/MLCL_List.h"

typedef struct List Stack;

Stack * new_stack(void (*type_manifest) (TypeDescriptor *));
int stack_add(Stack *self, void *data);
void * stack_peek(const Stack *self);
void * stack_pop(Stack *self);
int stack_is_empty(const Stack *self);
void stack_free(Stack **self);

#endif /* MYLITTLECLIBRARY_MLCL_STACK_H */
