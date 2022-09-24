/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_List_test.h"

#include "../../../../include/data-structures/Lists/MLCL_List.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_primitive_types.h"

int run_all_list_tests(){
    printf("▒▒▒ Running all List tests ▒▒▒\n");
    MLCL_TEST(test_list_append, "test_list_append")
    return 1;
}

int test_list_append(){

    List *list;

    list = new_list(LINKED_LIST, str_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    list_append(list, new_str("hell"));
    list_append(list, new_str("shell"));
    list_append(list, new_str("Foo"));
    list_append(list, new_str("bar"));
    list_append(list, new_str("Bubble"));
    linked_list_merge_sort(list->s.linked_list, list->s.linked_list->td->lt);

    if(list->s.linked_list->td->eq(list->s.linked_list->head->data, "Bubble") != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    list_free(&list);
    return 1;
}

