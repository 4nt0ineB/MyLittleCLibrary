/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#ifndef MYLITTLECLIBRARY_MLCL_STACK_H
#define MYLITTLECLIBRARY_MLCL_STACK_H

#include "../Lists/MLCL_List.h"

typedef struct s_stack {
    List *l;
    int (*add) (struct s_stack *, const void *);
    void * (*peek) (const struct s_stack *);
    void * (*pop) (struct s_stack *);
    int (*is_empty) (const struct s_stack *);
    void (*free) (struct s_stack **);
} Stack;

Stack * new_queue(void (*type_manifest) (TypeDescriptor *));
int queue_add(Stack *s, const void * data);
void * queue_peek(const Stack *s);
void * queue_pop(Stack * s);
int queue_is_empty(const Stack *s);
void queue_free(Stack **s);

#endif /* MYLITTLECLIBRARY_MLCL_STACK_H */
