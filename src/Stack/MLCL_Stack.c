/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Stack/MLCL_Stack.h"

Stack * new_queue(void (*type_manifest) (TypeDescriptor *)){
    Stack * s;
    if(!type_manifest) return NULL;
    s = (Stack *) malloc(sizeof(Stack));
    if(!s) return NULL;
    s->l = (List *) new_list(CIRCULAR_DOUBLE_LINKED_LIST, type_manifest);
    if(!s->l) return NULL;
    /* Methods */
    s->add = queue_add;
    s->pop = queue_pop;
    s->peek = queue_peek;
    s->is_empty = queue_is_empty;
    s->free = queue_free;
    return s;
}

int queue_add(Stack * s, const void * data){
    if(!s) return 0;
    if(!s->l) return 0;
    s->l->prepend(s->l, data);
    return 1;
}

void * queue_peek(const Stack *s){
    if(!s) return NULL;
    if(!s->l) return NULL;
    return s->l->head_peek(s->l);
}

void * queue_pop(Stack * s){
    if(!s) return NULL;
    if(!s->l) return NULL;
    return s->l->shift(s->l);
}

int queue_is_empty(const Stack *s){
    if(!s) return 1;
    if(!s->l) return 1;
    return s->l->is_empty(s->l);
}

void queue_free(Stack **s){
    if(!*s) return;
    if((*s)->l)
        (*s)->l->free(&(*s)->l);
    free(*s);
    *s = NULL;
}