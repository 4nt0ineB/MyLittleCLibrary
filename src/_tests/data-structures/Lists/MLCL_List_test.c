/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_List_test.h"

#include "../../../../include/data-structures/Lists/MLCL_List.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"

int run_all_list_tests(){
    printf("▒▒▒ Running all List tests ▒▒▒\n");
    MLCL_TEST(test_list_append, "test_list_append")
    return 1;
}

int test_list_append(){

    List * l;

    l = new_list(LINKED_LIST, str_m);

    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    l->append(l, "hell");
    l->append(l, "shell");
    l->append(l, "Foo");
    l->append(l, "bar");
    l->append(l, "Bubble");
    l->s.linked_list->d->merge_sort(&l->s.linked_list, l->s.linked_list->d->type_descriptor->lt);

    if(l->s.linked_list->d->type_descriptor->eq(l->s.linked_list->data, "Bubble") != 1)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->free(&l);
    return 1;
}
