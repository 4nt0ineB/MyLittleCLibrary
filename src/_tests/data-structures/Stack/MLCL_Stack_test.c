/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Stack/MLCL_Stack_test.h"
#include "../../../../include/data-structures/Stack/MLCL_Stack.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"

int run_all_stack_tests(){
    printf("▒▒▒ Running all Stack tests ▒▒▒\n");
    MLCL_TEST(test_stack_add, "test_queue_add")
    MLCL_TEST(test_stack_pop, "test_queue_pop")
    return 1;
}

int test_stack_add(){
    Stack *q;
    int x;

    q = new_stack(int_m);

    if(!q)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 1;

    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    if((* (int *) q->l->s.circular_double_linked_list->data) != 3)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    q->free(&q);
    return 1;
}

int test_stack_pop(){
    Stack *q;
    int x;
    void * tmp;

    q = new_stack(int_m);

    if(!q)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 1;
    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    tmp = q->pop(q);

    if((* (int *) tmp) != 3)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    free(tmp);

    q->free(&q);
    return 1;
}