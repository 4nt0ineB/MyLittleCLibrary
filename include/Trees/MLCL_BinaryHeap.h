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

#ifndef MYLITTLECLIBRARY_MLCL_BINARYHEAP_H
#define MYLITTLECLIBRARY_MLCL_BINARYHEAP_H

#include "../Lists/MLCL_ArrayList.h"

typedef enum { MIN_HEAP, MAX_HEAP } BINARY_HEAP_ORDER;

typedef struct s_binary_heap {
    BINARY_HEAP_ORDER type;
    ArrayList *l;
    struct s_binary_heap_descriptor * d;
} BinaryHeap;

typedef struct s_binary_heap_descriptor{
    TypeDescriptor * type_descriptor;
    int (*cmp_data) (const BinaryHeap *, const void *, const void *);
    void (*free) (BinaryHeap **);
} BinaryHeapDescriptor;

BinaryHeap * binary_heap_builder(BINARY_HEAP_ORDER order, BinaryHeapDescriptor * descriptor);
BinaryHeapDescriptor * binary_heap_descriptor();
BinaryHeap * new_binary_heap(BINARY_HEAP_ORDER order, void (*type_manifest) (TypeDescriptor *));
int array_list_is_heap(const BinaryHeap *h);
int binary_heap_cmp_data(const BinaryHeap *h, const void * x, const void * y);
int binary_heap_get_child_index(const BinaryHeap *h, int i);

/**
 * @brief change current index data by the given one
 * @param h
 * @param i
 * @param data
 */
void binary_heap_swap(BinaryHeap *h, int i, const void * data);

void binary_heap_add(BinaryHeap *h, const void * data);

void binary_heap_free(BinaryHeap **h);
#endif /* MYLITTLECLIBRARY_MLCL_BINARYHEAP_H */
