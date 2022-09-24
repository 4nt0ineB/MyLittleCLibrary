/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Queue/MLCL_Queue_test.h"
#include "../../../../include/data-structures/Queue/MLCL_Queue.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_primitive_types.h"


int run_all_queue_tests(){
    printf("▒▒▒ Running all Queue tests ▒▒▒\n");
    MLCL_TEST(test_queue_add, "test_queue_add")
    MLCL_TEST(test_queue_pop, "test_queue_pop")
    return 1;
}

int test_queue_add(){
    Queue *queue;

    queue = new_queue(int_m);

    if(!queue)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    queue_add(queue, new_int(1));
    queue_add(queue, new_int(2));
    queue_add(queue, new_int(3));

    if((* (int *) queue->s.circular_double_linked_list->head->data) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    queue_free(&queue);
    return 1;
}

int test_queue_pop(){
    Queue *queue;
    void * tmp;

    queue = new_queue(int_m);

    if(!queue)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    queue_add(queue, new_int(1));
    queue_add(queue, new_int(2));
    queue_add(queue, new_int(3));

    tmp = queue_pop(queue);

    if((* (int *) tmp) != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    free(tmp);
    queue_free(&queue);
    return 1;
}
