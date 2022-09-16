/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_CircularDoubleLinkedList_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/data-structures/Lists/MLCL_CircularDoubleLinkedList.h"
#include "../../../../include/core/MLCL_primitive_types.h"



int run_all_circular_double_linked_list_tests(){
    printf("▒▒▒ Running all CircularDoubleLinkedList tests ▒▒▒\n");
/*
    MLCL_TEST(test_circular_double_linked_list_ordered_add, "test_circular_double_linked_list_ordered_add")
*/
    MLCL_TEST(test_circular_double_linked_list_prepend, "test_circular_double_linked_list_prepend")
    MLCL_TEST(test_circular_double_linked_list_append, "test_circular_double_linked_list_append")
    MLCL_TEST(test_circular_double_linked_list_search, "test_circular_double_linked_list_search")
    MLCL_TEST(test_circular_double_linked_list_pop, "test_circular_double_linked_list_pop")
    MLCL_TEST(test_circular_double_linked_list_shift, "test_circular_double_linked_list_shift")
    return 1;
}
/*
int test_circular_double_linked_list_ordered_add(){
    CircularDoubleLinkedList *list;
    int x;

    x = 5;
    list = new_circular_double_linked_list(int_m);
    x = 6;
    circular_double_linked_listordered_add(&list, &x);
    x = 2;
    circular_double_linked_listordered_add(&list, &x);
    x = 3;
    circular_double_linked_listordered_add(&list, &x);
    x = 2;
    if(list->td->cmp(&x, list->head->data) != 0)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    x = 3;
    if(list->td->cmp(&x, list->head->next->data) != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    x = 5;
    if(list->td->cmp(&x, list->head->next->next->data) != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    x = 6;
    if(list->td->cmp(&x, list->head->next->next->next->data) != 0)
        MLCL_ERR(4, MLCL_ERR_TRUE)
    circular_double_linked_list_free(&list);
    return 1;
}*/

int test_circular_double_linked_list_prepend(){
    CircularDoubleLinkedList *list;

    list = new_circular_double_linked_list(float_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    circular_double_linked_list_prepend(list, new_float(5.4f));
    circular_double_linked_list_prepend(list, new_float(5.3f));

    if(list->head != list->head->next->next)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    circular_double_linked_list_free(&list);
    return 1;
}

int test_circular_double_linked_list_append(){
    CircularDoubleLinkedList *list;

    list = new_circular_double_linked_list(float_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    circular_double_linked_list_append(list, new_float(5.4f));
    circular_double_linked_list_append(list, new_float(5.3f));
    circular_double_linked_list_append(list, new_float(5.3f));
    circular_double_linked_list_append(list, new_float(5.96f));

    if(list->head->next->next->next->next != list->head)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    circular_double_linked_list_free(&list);
    return 1;
}

int test_circular_double_linked_list_search(){
    CircularDoubleLinkedList *list;
    int x;

    list = new_circular_double_linked_list(int_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    circular_double_linked_list_prepend(list, new_int(5));
    circular_double_linked_list_prepend(list, new_int(6));
    circular_double_linked_list_prepend(list, new_int(7));

    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)

    x = 7;
    if(!circular_double_linked_list_search(list, &x, int_eq))
        MLCL_ERR(3, MLCL_ERR_TRUE)
        
    circular_double_linked_list_free(&list);
    return 1;
}

int test_circular_double_linked_list_pop(){
    CircularDoubleLinkedList *list;
    void *data;

    list = new_circular_double_linked_list(int_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)


    circular_double_linked_list_prepend(list, new_int(5));
    circular_double_linked_list_prepend(list, new_int(6));

    data = circular_double_linked_list_pop(list);

    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    circular_double_linked_list_free(&list);
    free(data);
    return 1;
}

int test_circular_double_linked_list_shift(){
    CircularDoubleLinkedList *list;
    void *data;
    list = new_circular_double_linked_list(float_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    circular_double_linked_list_append(list, new_float(5.4f));
    circular_double_linked_list_append(list, new_float(5.5f));

    data = circular_double_linked_list_shift(list);
    circular_double_linked_list_print(list);

    if(list->head->next->next != list->head)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    circular_double_linked_list_free(&list);
    free(data);
    return 1;
}

