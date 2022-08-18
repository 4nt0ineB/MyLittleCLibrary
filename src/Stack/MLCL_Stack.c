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

#include "../../include/Stack/MLCL_Stack.h"

Stack * new_stack(void (*type_manifest) (TypeDescriptor *)){
    Stack * s;
    if(!type_manifest) return NULL;
    s = (Stack *) malloc(sizeof(Stack));
    if(!s) return NULL;
    s->l = (List *) new_list(DOUBLE_LINKED_LIST, type_manifest);
    if(!s->l) return NULL;
    /* Methods */
    s->add = stack_add;
    s->pop = stack_pop;
    s->peek = stack_peek;
    s->is_empty = stack_is_empty;
    s->free = stack_free;
    return s;
}

int stack_add(Stack * s, const void * data){
    if(!s) return 0;
    if(!s->l) return 0;
    s->l->prepend(s->l, data);
    return 1;
}

void * stack_peek(const Stack *s){
    if(!s) return NULL;
    if(!s->l) return NULL;
    return s->l->head_peek(s->l);
}

void * stack_pop(Stack * s){
    if(!s) return NULL;
    if(!s->l) return NULL;
    return s->l->shift(s->l);
}

int stack_is_empty(const Stack *s){
    if(!s) return 1;
    if(!s->l) return 1;
    return s->l->is_empty(s->l);
}

void stack_free(Stack **s){
    if(!*s) return;
    if((*s)->l)
        (*s)->l->free(&(*s)->l);
    free(*s);
    *s = NULL;
}