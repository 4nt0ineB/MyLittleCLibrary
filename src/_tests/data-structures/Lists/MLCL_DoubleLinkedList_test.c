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

#include "../../../../include/_tests/data-structures/Lists/MLCL_DoubleLinkedList_test.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/data-structures/Lists/MLCL_DoubleLinkedList.h"
#include "../../../../include/core/MLCL_basic_types.h"



int run_all_double_linked_list_tests(){
    printf("▒▒▒ Running all DoubleLinkedList tests ▒▒▒\n");
    MLCL_TEST(test_new_double_linked_list, "test_new_double_linked_list")
    /*MLCL_TEST(test_double_linked_list_ordered_add, "test_double_linked_list_ordered_add")*/
    MLCL_TEST(test_double_linked_list_prepend, "test_double_linked_list_prepend")
    MLCL_TEST(test_double_linked_list_append, "test_double_linked_list_append")
    MLCL_TEST(test_double_linked_list_search, "test_double_linked_list_search")
    MLCL_TEST(test_double_linked_list_remove, "test_double_linked_list_remove")
    MLCL_TEST(test_double_linked_list_shift, "test_double_linked_list_shift")
    MLCL_TEST(test_double_linked_list_pop, "test_double_linked_list_pop")
    /*MLCL_TEST(test_double_linked_list_filter, "test_double_linked_list_filter")*/
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

/*int test_double_linked_list_ordered_add(){
    DoubleLinkedList *list;
    int x;

    list = new_double_linked_list(int_m);
    double_linked_list_append(list, new_int(5));
    double_linked_list_ordered_add(&list, new_int(6));
    double_linked_list_ordered_add(&list, new_int(2));
    double_linked_list_ordered_add(&list, new_int(3));

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

    double_linked_list_free(&list);
    return 1;
}*/

int test_double_linked_list_prepend(){
    DoubleLinkedList *list;

    list = new_double_linked_list(float_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    double_linked_list_prepend(list, new_float(5.2f));

    double_linked_list_prepend(list, new_float(7.9f));

    double_linked_list_print(list);

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

int test_double_linked_list_insert(){

/* @Todo Insert test*/

    return 1;
}

int test_double_linked_list_search(){
    DoubleLinkedList *list;
    int x;

    list = new_double_linked_list(int_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));
    double_linked_list_prepend(list, new_int(7));

    if((* (int *) list->head->data) != 7)
        MLCL_ERR(2, MLCL_ERR_EQ)

    x = 6;
    if(!double_linked_list_search(list, &x, int_eq))
        MLCL_ERR(3, MLCL_ERR_TRUE)

    double_linked_list_free(&list);
    return 1;
}

int test_double_linked_list_remove(){
    DoubleLinkedList *list;
    int x;

    list = new_double_linked_list(int_m);

    if(!list)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    double_linked_list_append(list, new_int(5));
    double_linked_list_prepend(list, new_int(6));

    x = 6;
    double_linked_list_remove(list, &x, int_eq, int_free);

    if((* (int *) list->head->data) != 5)
        MLCL_ERR(2, MLCL_ERR_EQ)

    x = 5;
    double_linked_list_remove(list, &x, int_eq, int_free);

    if(list->head)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    double_linked_list_free(&list);

    return 1;
}

int test_double_linked_list_shift(){
    DoubleLinkedList *list;
    void * data;

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
    void * data;

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

int test_double_linked_list_filter(){
/* @Todo filter test */

    return 1;
}

