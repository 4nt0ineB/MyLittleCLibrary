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
