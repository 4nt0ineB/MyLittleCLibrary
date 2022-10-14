/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_CircularLinkedList_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_primitive_types.h"
#include "../../../../include/data-structures/Lists/MLCL_CircularLinkedList.h"

#include <stdio.h>


int run_all_circular_linked_list_tests(){
    printf("▒▒▒ Running alist CircularLinkedList tests \n");
    MLCL_TEST(test_circular_linked_list_prepend)
    MLCL_TEST(test_circular_linked_list_append)
    MLCL_TEST(test_circular_linked_list_search)
    MLCL_TEST(test_circular_linked_list_pop)
    MLCL_TEST(test_circular_linked_list_shift)
    return 1;
}

int test_circular_linked_list_append(){
    CircularLinkedList *list;
    list = new_circular_linked_list(float_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    circular_linked_list_append(list, new_float(5.4f));
    circular_linked_list_append(list, new_float(5.3f));
    circular_linked_list_append(list, new_float(5.3f));
    circular_linked_list_append(list, new_float(5.96f));
    if(list->head->next->next->next->next != list->head)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    circular_linked_list_free(&list);
    return 1;
}

int test_circular_linked_list_prepend(){
    CircularLinkedList *list;
    list = new_circular_linked_list(float_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    circular_linked_list_prepend(list, new_float(5.4f));
    circular_linked_list_prepend(list, new_float(5.3f));
    /*printf("\n");
    circular_linked_list_print(list);*/
    if(list->head != list->head->next->next)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    circular_linked_list_free(&list);
    return 1;
}

int test_circular_linked_list_search(){
    CircularLinkedList *list;
    int x;
    list = new_circular_linked_list(int_m);
    if(!list) MLCL_ERR(1, MLCL_ERR_ALLOC)
    circular_linked_list_prepend(list, new_int(5));
    circular_linked_list_prepend(list, new_int(6));
    circular_linked_list_prepend(list, new_int(7));
    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)
    x = 6;
    if(!circular_linked_list_search(list, &x, int_eq))
        MLCL_ERR(3, MLCL_ERR_TRUE)
    circular_linked_list_free(&list);
    return 1;
}

int test_circular_linked_list_pop(){
    CircularLinkedList *list;
    void *data;
    list = new_circular_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    circular_linked_list_prepend(list, new_int(5));
    circular_linked_list_prepend(list, new_int(6));
    data = circular_linked_list_pop(list);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    circular_linked_list_free(&list);
    free(data);
    return 1;
}

int test_circular_linked_list_shift(){
    CircularLinkedList *list;
    void *data;
    list = new_circular_linked_list(float_m);
    circular_linked_list_append(list, new_float(5.4f));
    circular_linked_list_append(list, new_float(5.5f));
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    data = circular_linked_list_shift(list);
    if(list->head->next->next != list->head)
    MLCL_ERR(2, MLCL_ERR_TRUE)
    circular_linked_list_free(&list);
    free(data);
    return 1;
}

