/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../include/data-structures/Queue/MLCL_Queue.h"

Queue * new_queue(void (*type_manifest) (TypeDescriptor *)){
    return new_list(CIRCULAR_DOUBLE_LINKED_LIST, type_manifest);
}

int queue_add(Queue *self, void *data){
    return list_append(self, data);
}

void * queue_peek(const Queue *self){
    return list_head_peek(self);
}

void * queue_pop(Queue *self){
    return list_shift(self);
}

int queue_is_empty(const Queue *self){
    return !list_length(self);
}

void queue_free(Queue **self){
    list_free(self);
}
