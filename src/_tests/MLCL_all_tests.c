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

#include "../../include/_tests/MLCL_all_tests.h"
#include <stdio.h>
#include <stdlib.h>

int run_all_tests(){
    Timer *timer;
    int i;
    int (*tests[])() =
            {
            /*run_all_type_descriptor_tests*/
            run_all_linked_list_tests
            , run_all_circular_linked_list_tests
            , run_all_double_linked_list_tests
            /*, run_all_circular_double_linked_list_tests
            , run_all_binary_search_tree_tests
            , run_all_avl_tree_tests
            , run_all_array_list_tests
            , run_all_list_tests
            , run_all_binary_heap_tests
            , run_all_queue_tests
            , run_all_stack_tests
            , run_all_ternary_search_tree_tests
            , run_all_bk_tree_tests*/
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
