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
