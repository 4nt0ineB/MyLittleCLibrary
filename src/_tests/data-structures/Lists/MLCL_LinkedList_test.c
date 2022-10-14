/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_LinkedList_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/data-structures/Lists/MLCL_LinkedList.h"

int run_all_linked_list_tests(){
    printf("▒▒▒ Running all LinkedList tests \n");
    MLCL_TEST(test_new_linked_list)
    MLCL_TEST(test_linked_list_prepend)
    MLCL_TEST(test_linked_list_append)
    MLCL_TEST(test_linked_list_search)
    MLCL_TEST(test_linked_list_search_all)
    MLCL_TEST(test_linked_list_remove)
    MLCL_TEST(test_linked_list_remove_all)
    MLCL_TEST(test_linked_list_shift)
    MLCL_TEST(test_linked_list_pop)
    MLCL_TEST(test_linked_list_merge_sort)
    return 1;
}

int test_new_linked_list(){
    LinkedList *list;
    list = new_linked_list(int_m);
    linked_list_append(list, new_int(5));
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    if((*(int *) list->head->data) != 5)
        MLCL_ERR(2, MLCL_ERR_EQ)
    linked_list_free(&list);
    return 1;
}


int test_linked_list_prepend(){
    LinkedList *list;
    list = new_linked_list(float_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_float(5.2f));
    linked_list_prepend(list, new_float(7.9f));
    if(!list->head->next)
        MLCL_ERR(3, MLCL_ERR_ALLOC)
    if((* (float *) list->head->next->data) !=  5.2f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    if((* (float *) list->head->data) != 7.9f)
        MLCL_ERR(5, MLCL_ERR_EQ)
    linked_list_free(&list);
    return 1;
}

int test_linked_list_append(){
    LinkedList *list;
    list = new_linked_list(float_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_append(list, new_float(5.2f));
    linked_list_append(list, new_float(7.9f));
    if(!list->head->next)
        MLCL_ERR(2, MLCL_ERR_ALLOC)
    if((* (float *) list->head->next->data) != 7.9f)
        MLCL_ERR(3, MLCL_ERR_EQ)
    if((* (float *) list->head->data) != 5.2f)
        MLCL_ERR(4, MLCL_ERR_EQ)
    linked_list_free(&list);
    return 1;
}

int test_linked_list_search(){
    LinkedList *list;
    Filter *filter;
    list = new_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(5));
    linked_list_append(list, new_int(6));
    linked_list_prepend(list, new_int(7));
    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(6), EQ, int_free);
    if(!linked_list_search(list,filter))
        MLCL_ERR(3, MLCL_ERR_TRUE)
    linked_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_linked_list_search_all(){
    LinkedList *list, *searched_data;
    Filter *filter;
    list = new_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(5));
    linked_list_append(list, new_int(6));
    linked_list_prepend(list, new_int(7));
    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(7), LE, int_free);
    searched_data = linked_list_search_all(list,filter);
    if(!searched_data)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(searched_data->length != 3)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    linked_list_free(&list);
    filter_free(&filter);
    linked_list_free_w(&searched_data, NULL);

    return 1;
}

int test_linked_list_remove(){
    LinkedList *list;
    Filter *filter;
    list = new_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(5));
    linked_list_prepend(list, new_int(6));
    /* filter to target data = 5 */
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(5), EQ, int_free);
    linked_list_remove(list, filter);
    /*linked_list_print(list);*/
    if((* (int *) list->head->data) != 6)
        MLCL_ERR(2, MLCL_ERR_EQ)
    filter_clear(filter);
    filter->conditions[0] = new_condition(int_filter, new_int(6), EQ, int_free);
    linked_list_remove(list, filter);
    if(list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    linked_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_linked_list_remove_all(){
    LinkedList *list;
    Filter *filter;
    list = new_linked_list(int_m);
    if(!list)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(5));
    linked_list_prepend(list, new_int(6));
    /* filter to target data < 7 */
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(7), LT, int_free);
    /*linked_list_print(list);*/
    linked_list_remove_all(list, filter);
    /*linked_list_print(list);*/
  /*  if(list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)*/
    linked_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_linked_list_shift(){
    LinkedList *list;
    void *data;
    list = new_linked_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(5));
    linked_list_prepend(list, new_int(6));
    data = linked_list_shift(list);
    if((* (int *) data) != 6)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    linked_list_free(&list);
    free(data);
    return 1;
}

int test_linked_list_pop(){
    LinkedList *list;
    void *data;
    list = new_linked_list(int_m);
    linked_list_prepend(list, new_int(5));
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    linked_list_prepend(list, new_int(6));
    data = linked_list_pop(list);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(!list->head)
        MLCL_ERR(3, MLCL_ERR_FALSE)
    linked_list_free(&list);
    free(data);
    return 1;
}

int test_linked_list_merge_sort(){
    LinkedList *list;
    list = new_linked_list(int_m);
    linked_list_append(list, new_int(501));
    linked_list_append(list, new_int(12));
    linked_list_append(list, new_int(500));
    linked_list_append(list, new_int(6));
    linked_list_merge_sort(list, int_lt);
    if(*(int *) list->head->data != 6)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    if(*(int *) list->head->next->next->next->data != 501)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    /*printf("\n");
    linked_list_print(list);*/
    linked_list_free(&list);
    return 1;
}

/*int test_linked_list_ordered_add(){
    LinkedList ll;
    int x;
    x = 5;
    ll = new_linked_list(&x, int_m);
    x = 6;
    ll->d->ordered_add(&ll, &x);
    x = 2;
    ll->d->ordered_add(&ll, &x);
    x = 3;
    ll->d->ordered_add(&ll, &x);
    x = 2;
    if(ll->d->type_descriptor->cmp(&x, ll->data) != 0)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    x = 3;
    if(ll->d->type_descriptor->cmp(&x, ll->next->data) != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    x = 5;
    if(ll->d->type_descriptor->cmp(&x, ll->next->next->data) != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    x = 6;
    if(ll->d->type_descriptor->cmp(&x, ll->next->next->next->data) != 0)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}


int test_linked_list_insert(){
    */
/* @Todo Insert test*//*

    return 1;
}

int test_linked_list_filter(){
    */
/* @Todo filter test *//*

    return 1;
}
*/
