/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../../include/_Tests/Queue/MLCL_Queue_test.h"
#include "../../../include/Queue/MLCL_Queue.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_queue_tests(){
    printf("▒▒▒ Running all Queue tests ▒▒▒\n");
    MLCL_TEST(test_queue_add, "test_queue_add")
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