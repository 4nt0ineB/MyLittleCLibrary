/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_ArrayList_test.h"
#include "../../../../include/data-structures/Lists/MLCL_ArrayList.h"
#include "../../../../include/_tests/MLCL_exceptions.h"

int run_all_array_list_tests(){
    printf("▒▒▒ Running all ArrayList tests \n");
    MLCL_TEST(test_array_list_append)
    MLCL_TEST(test_array_list_pop)
    MLCL_TEST(test_array_list_pop_i)
    MLCL_TEST(test_array_list_is_sorted)
    MLCL_TEST(test_array_list_bubble_sort)
    MLCL_TEST(test_array_list_selection_sort)
    MLCL_TEST(test_array_list_insertion_sort)
    MLCL_TEST(test_array_list_quick_sort)
    MLCL_TEST(test_array_list_merge_sort)
    MLCL_TEST(test_array_list_search)
    MLCL_TEST(test_array_list_remove)
    MLCL_TEST(test_array_list_remove_all)
    MLCL_TEST(test_array_list_binary_search)
    return 1;
}

int test_array_list_append(){
    ArrayList *list;
    int i;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    for(i = 0; i < 10; i++)
        array_list_append(list, new_int(i));
    if(*(int *) list->array[5] != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(list->length != 10)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(list->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_pop(){
    ArrayList *list;
    int i;
    void *x;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    for(i = 0; i < 5; i++)
        array_list_append(list, new_int(i));
    x = array_list_pop(list);
    if(*(int *) x != 4)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);
    free(array_list_pop(list));
    free(array_list_pop(list));
    free(array_list_pop(list));
    free(array_list_pop(list));
    if(list->length != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(list->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_pop_i(){
    ArrayList *list;
    int i;
    void * x;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    for(i = 0; i < 5; i++)
        array_list_append(list, new_int(i));
    x = array_list_pop_i(list, 0);
    if(*(int *) x != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);
    x = array_list_pop_i(list, 1);
    if(*(int *) x != 2)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);
    if(list->length != 3)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(list->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_is_sorted(){
    ArrayList *list;
    int i;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    for(i = 0; i < 5; i++)
        array_list_append(list, new_int(i));
    if(!array_list_is_sorted(list, list->td->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_bubble_sort(){
    ArrayList *list;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_bubble_sort(list, list->td->le);
    if(!array_list_is_sorted(list, list->td->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_selection_sort(){
    ArrayList *list;
    list = new_array_list(int_m);
    if(!list)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_selection_sort(list, list->td->le);
    if(!array_list_is_sorted(list, list->td->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_insertion_sort(){
    ArrayList *list;
    list = new_array_list(int_m);
    if(!list)
    MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_insertion_sort(list, list->td->ge);
    if(!array_list_is_sorted(list, list->td->ge))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_quick_sort(){
    ArrayList *list;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_quick_sort(list, list->td->le);
    if(!array_list_is_sorted(list, list->td->le))
    MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_merge_sort(){
    ArrayList *list;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_merge_sort(list, list->td->lt);
    /*array_list_print(list);*/
    if(!array_list_is_sorted(list, list->td->lt))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}

int test_array_list_search(){
    ArrayList *list;
    Filter *filter;
    int index;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_quick_sort(list, list->td->le);
    filter = new_filter(1);
    filter->conditions[0] = new_condition(int_filter, new_int(28), EQ, int_free);
    if(!array_list_search(list, filter, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    array_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_array_list_remove(){
    ArrayList *list;
    Filter *filter;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_quick_sort(list, list->td->le);
    filter = new_filter(1);
    /* Let's remove 28 */
    filter->conditions[0] = new_condition(int_filter, new_int(28), EQ, int_free);
    if(!array_list_remove(list, filter))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(list->length != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    array_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_array_list_remove_all(){
    ArrayList *list;
    Filter *filter;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_quick_sort(list, list->td->le);
    filter = new_filter(1);
    /* We want to remove all int less or equal to 3 */
    filter->conditions[0] = new_condition(int_filter, new_int(3), LE, int_free);
    if(!array_list_remove_all(list, filter))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(list->length != 2)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    array_list_free(&list);
    filter_free(&filter);
    return 1;
}

int test_array_list_binary_search(){
    ArrayList *list;
    int x, index;
    list = new_array_list(int_m);
    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    array_list_append(list, new_int(6));
    array_list_append(list, new_int(3));
    array_list_append(list, new_int(28));
    array_list_append(list, new_int(2));
    array_list_append(list, new_int(1));
    array_list_quick_sort(list, list->td->le);
    x = 28;
    if(!array_list_binary_search(list, &x, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    array_list_free(&list);
    return 1;
}
