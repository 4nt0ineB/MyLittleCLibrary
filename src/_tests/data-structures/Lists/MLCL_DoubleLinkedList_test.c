/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_DoubleLinkedList_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/data-structures/Lists/MLCL_DoubleLinkedList.h"

int run_all_double_linked_list_tests(){
    printf("▒▒▒ Running all DoubleLinkedList tests \n");
    MLCL_TEST(test_new_double_linked_list)
    MLCL_TEST(test_double_linked_list_prepend)
    MLCL_TEST(test_double_linked_list_append)
    MLCL_TEST(test_double_linked_list_search)
    MLCL_TEST(test_double_linked_list_remove)
    MLCL_TEST(test_double_linked_list_shift)
    MLCL_TEST(test_double_linked_list_pop)
    return 1;
}

int test_new_double_linked_list(){
    DoubleLinkedList *list;
    list = new_double_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_free(&list);
    return 1;
}

int test_double_linked_list_prepend(){
    DoubleLinkedList *list;
    list = new_double_linked_list(float_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_prepend(list, new_float(5.2f));
    double_linked_list_prepend(list, new_float(7.9f));
    /*double_linked_list_print(list);*/
    if(!list->head)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if(!list->head->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) list->head->next->data) !=  5.2f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    if((* (float *) list->head->data) != 7.9f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    double_linked_list_free(&list);
    return 1;
}

int test_double_linked_list_append(){
    DoubleLinkedList *list;
    list = new_double_linked_list(float_m);
    double_linked_list_append(list, new_float(5.2f));
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_append(list, new_float(7.9f));
    if(!list->head)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if(!list->head->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) list->head->next->data) != 7.9f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    if((* (float *) list->head->data) != 5.2f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    double_linked_list_free(&list);
    return 1;
}

int test_double_linked_list_search(){
    DoubleLinkedList *list;
    Filter *filter;
    list = new_double_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));
    double_linked_list_prepend(list, new_int(7));
    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(6), EQ, int_free);
    if(!double_linked_list_search(list, filter))
        MLCL_ERR(3, MLCL_ERR_TRUE)
    double_linked_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_double_linked_list_remove(){
    DoubleLinkedList *list;
    Filter *filter;
    list = new_double_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(6), EQ, int_free);
    double_linked_list_remove(list, filter);
    /*double_linked_list_print(list);*/
    if((* (int *) list->head->data) != 5)
        MLCL_ERR(2, MLCL_ERR_EQ)
    filter_clear(filter);
    filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
    double_linked_list_remove(list, filter);
    if(list->head)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    double_linked_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_double_linked_list_shift(){
    DoubleLinkedList *list;
    void *data;
    list = new_double_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));
    data = double_linked_list_shift(list);
    if((* (int *) data) != 6)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    double_linked_list_free(&list);
    free(data);
    return 1;
}

int test_double_linked_list_pop(){
    DoubleLinkedList *list;
    void *data;
    list = new_double_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));
    data = double_linked_list_pop(list);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    double_linked_list_free(&list);
    free(data);
    return 1;
}

