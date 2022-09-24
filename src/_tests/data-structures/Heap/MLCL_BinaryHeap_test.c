/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Heap/MLCL_BinaryHeap_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_TypeDescriptor.h"
#include "../../../../include/core/MLCL_primitive_types.h"


int run_all_binary_heap_tests(){
    printf("▒▒▒ Running all BinaryHeap tests ▒▒▒\n");
    MLCL_TEST(test_binary_heap_add,
              "test_binary_heap_add")
    MLCL_TEST(test_binary_heap_pop,
              "test_binary_heap_pop")
    return 1;
}

int test_binary_heap_add(){
    BinaryHeap *heap;
    int x;

    heap = new_binary_heap(MAX_HEAP, int_m);

    if(!heap)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    binary_heap_add(heap, new_int(5));
    binary_heap_add(heap, new_int(2));
    binary_heap_add(heap, new_int(6));
    binary_heap_add(heap, new_int(1));
    binary_heap_add(heap, new_int(0));

    x = 6;
    if(heap->td->eq(heap->list->array[0], &x) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_heap_free(&heap);
    return 1;
}

int test_binary_heap_pop(){
    BinaryHeap *heap;
    int x;

    heap = new_binary_heap(MAX_HEAP, int_m);

    if(!heap)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    binary_heap_add(heap, new_int(5));
    binary_heap_add(heap, new_int(2));
    binary_heap_add(heap, new_int(6));
    binary_heap_add(heap, new_int(1));
    binary_heap_add(heap, new_int(0));

    free(binary_heap_pop(heap));
    free(binary_heap_pop(heap));


    x = 2;
    if(heap->td->eq(heap->list->array[0], &x) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_heap_free(&heap);
    return 1;
}


