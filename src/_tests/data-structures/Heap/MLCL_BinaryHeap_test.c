/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Heap/MLCL_BinaryHeap_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_TypeDescriptor.h"
#include "../../../../include/core/MLCL_basic_types.h"

int run_all_binary_heap_tests(){
    printf("▒▒▒ Running all BinaryHeap tests ▒▒▒\n");
    MLCL_TEST(test_binary_heap_add,
              "test_binary_heap_add")
    MLCL_TEST(test_binary_heap_pop,
              "test_binary_heap_pop")
    return 1;
}

int test_binary_heap_add(){
    BinaryHeap *h;
    int x;

    h = new_binary_heap(MAX_HEAP, int_m);

    if(!h)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 5;
    binary_heap_add(h, &x);
    x = 2;
    binary_heap_add(h, &x);
    x = 6;
    binary_heap_add(h, &x);
    x = 1;
    binary_heap_add(h, &x);
    x = 0;
    binary_heap_add(h, &x);

    x = 6;
    if(h->l->d->type_descriptor->eq(h->l->array[0], &x) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    h->d->free(&h);
    return 1;
}

int test_binary_heap_pop(){
    BinaryHeap *h;
    int x;
    void * tmp;

    h = new_binary_heap(MAX_HEAP, int_m);

    if(!h)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 5;
    binary_heap_add(h, &x);
    x = 2;
    binary_heap_add(h, &x);
    x = 6;
    binary_heap_add(h, &x);
    x = 1;
    binary_heap_add(h, &x);
    x = 0;
    binary_heap_add(h, &x);

    tmp = binary_heap_pop(h);
    h->d->type_descriptor->data_free(&tmp);
    tmp = binary_heap_pop(h);
    h->d->type_descriptor->data_free(&tmp);

    x = 2;
    if(h->l->d->type_descriptor->eq(h->l->array[0], &x) != 1)
    MLCL_ERR(2, MLCL_ERR_TRUE)

    h->d->free(&h);
    return 1;
}

