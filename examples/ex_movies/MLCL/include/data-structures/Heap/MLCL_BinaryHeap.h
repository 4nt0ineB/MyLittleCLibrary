/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#ifndef MYLITTLECLIBRARY_MLCL_BINARYHEAP_H
#define MYLITTLECLIBRARY_MLCL_BINARYHEAP_H

#include "../Lists/MLCL_ArrayList.h"

typedef enum { MIN_HEAP, MAX_HEAP } BINARY_HEAP_ORDER;

typedef struct BinaryHeap {
    BINARY_HEAP_ORDER type;
    ArrayList *list;
    TypeDescriptor *td;
} BinaryHeap;

BinaryHeap * new_binary_heap(BINARY_HEAP_ORDER order, void (*type_manifest) (TypeDescriptor *));
int array_list_is_heap(const BinaryHeap *self);
int binary_heap_cmp_data(const BinaryHeap *self, const void *x, const void *y);
int binary_heap_get_child_index(const BinaryHeap *self, int i);

/**
 * @brief change the given index data by the given one, while respecting the structures ordering
 * @param h
 * @param i
 * @param data
 * @param shallow_copy 1 just copy the address, 0 deep copy of the data
 */
int binary_heap_swap(BinaryHeap *self, int i, const void *data, char shallow_copy);

void binary_heap_add(BinaryHeap *self, const void *data);

/**
 * @brief Return the pointer to the data with highest priority. Depends on heap type (MIN_HEAP / MAX_HEAP).
 * @param h
 * @return
 */
void * binary_heap_pop(BinaryHeap *h);

void binary_heap_clear(BinaryHeap *self, void (*data_free) (void *));
void binary_heap_free(BinaryHeap **h);
#endif /* MYLITTLECLIBRARY_MLCL_BINARYHEAP_H */
