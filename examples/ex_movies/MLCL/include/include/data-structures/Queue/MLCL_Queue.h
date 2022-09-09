/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_QUEUE_H
#define MYLITTLECLIBRARY_MLCL_QUEUE_H

#include "../Lists/MLCL_List.h"

typedef List Queue;

Queue * new_queue(void (*type_manifest) (TypeDescriptor *));
int queue_add(Queue *self, void *data);
void * queue_peek(const Queue *self);
void * queue_pop(Queue *self);
int queue_is_empty(const Queue *self);
void queue_free(Queue **self);

#endif /* MYLITTLECLIBRARY_MLCL_QUEUE_H */
