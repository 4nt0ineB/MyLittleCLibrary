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

#include "../../include/_Tests/MLCL_all_tests.h"
#include <stdio.h>

int run_all_tests(){
    Timer *timer;
    printf("┌[▓▒ MLCL ▒▓]\n");

    timer = new_timer();
    timer_start(timer);
    if(!run_all_type_descriptor_tests())
        return 0;
    if(!run_all_linked_list_tests())
        return 0;
    if(!run_all_circular_linked_list_tests())
        return 0;
    if(!run_all_double_linked_list_tests())
        return 0;
    if(!run_all_circular_double_linked_list_tests())
        return 0;
    if(!run_all_binary_search_tree_tests())
        return 0;
    if(!run_all_avl_tree_tests())
        return 0;
    if(!run_all_array_list_tests())
        return 0;
    if(!run_all_list_tests())
        return 0;
    if(!run_all_binary_heap_tests())
        return 0;
    timer_update(timer);
    printf("└[▓▒ All tests successfully passed in ");
    timer_print(*timer);
    printf("]▒▓]\n");
    free(timer);
    return 1;
}
