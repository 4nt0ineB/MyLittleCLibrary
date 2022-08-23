/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Queue/MLCL_Queue_test.h"
#include "../../../../include/data-structures/Queue/MLCL_Queue.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"

/*
int run_all_queue_tests(){
    printf("▒▒▒ Running all Queue tests ▒▒▒\n");
    MLCL_TEST(test_queue_add, "test_queue_add")
    MLCL_TEST(test_queue_pop, "test_queue_pop")
    return 1;
}

int test_queue_add(){
    Queue *q;
    int x;

    q = new_queue(int_m);

    if(!q)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 1;

    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    if((* (int *) q->l->s.circular_double_linked_list->data) != 1)
    MLCL_ERR(2, MLCL_ERR_TRUE)

    q->free(&q);
    return 1;
}

int test_queue_pop(){
    Queue *q;
    int x;
    void * tmp;

    q = new_queue(int_m);

    if(!q)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 1;
    q->add(q, &x);
    x = 2;
    q->add(q, &x);
    x = 3;
    q->add(q, &x);

    tmp = q->pop(q);

    if((* (int *) tmp) != 1)
    MLCL_ERR(2, MLCL_ERR_TRUE)

    free(tmp);

    q->free(&q);
    return 1;
}*/
