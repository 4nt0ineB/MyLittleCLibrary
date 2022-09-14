/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../include/_tests/MLCL_all_tests.h"
#include <stdio.h>
#include <stdlib.h>

int run_all_tests(){
    Timer *timer;
    int i;
    int (*tests[])() =
            {
            run_all_type_descriptor_tests
            , run_all_linked_list_tests
            , run_all_circular_linked_list_tests
            , run_all_double_linked_list_tests
            , run_all_circular_double_linked_list_tests
            , run_all_array_list_tests
            , run_all_list_tests
            , run_all_binary_search_tree_tests
            , run_all_avl_tree_tests
            , run_all_binary_heap_tests
            , run_all_queue_tests
            , run_all_stack_tests
            , run_all_ternary_search_tree_tests
            , run_all_bk_tree_tests
            , NULL
    };

    timer = new_timer();
    timer_start(timer);

    printf("┌[▓▒ MLCL ▒▓]\n");

    for(i = 0; tests[i]; i++)
        if(!(*tests[i])())
            return 0;

    printf("└[▓▒ All tests successfully passed in ");

    timer_update(timer);
    timer_print(timer);
    printf("]▒▓]\n");

    free(timer);

    return 1;
}
