/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Lists/MLCL_ArrayList_test.h"
#include "../../../../include/data-structures/Lists/MLCL_ArrayList.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"


int run_all_array_list_tests(){
    printf("▒▒▒ Running all ArrayList tests ▒▒▒\n");
    MLCL_TEST(test_array_list_append, "test_array_list_append")
    MLCL_TEST(test_array_list_pop, "test_array_list_pop")
    MLCL_TEST(test_array_list_pop_i, "test_array_list_pop_i")
    MLCL_TEST(test_array_list_is_sorted, "test_array_list_is_sorted")
    MLCL_TEST(test_array_list_bubble_sort, "test_array_list_bubble_sort")
    MLCL_TEST(test_array_list_selection_sort, "test_array_list_selection_sort")
    MLCL_TEST(test_array_list_insertion_sort, "test_array_list_insertion_sort")
    MLCL_TEST(test_array_list_quick_sort, "test_array_list_quick_sort")
    MLCL_TEST(test_array_list_merge_sort, "test_array_list_merge_sort")
    MLCL_TEST(test_array_list_search, "test_array_list_search")
    MLCL_TEST(test_array_list_binary_search, "test_array_list_binary_search")
    return 1;
}

int test_array_list_append(){
    ArrayList * l;
    int i;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 10; i++)
        l->d->append(l, &i);

    if(*(int *) l->array[5] != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(l->count != 10)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_pop(){
    ArrayList * l;
    int i;
    void * x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    x = l->d->pop(l);

    if(*(int *) x != 4)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);
    free(l->d->pop(l));
    free(l->d->pop(l));
    free(l->d->pop(l));
    free(l->d->pop(l));

    if(l->count != 0)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_pop_i(){
    ArrayList * l;
    int i;
    void * x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    x = l->d->pop_i(l, 0);
    if(*(int *) x != 0)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);

    x = l->d->pop_i(l, 1);
    if(*(int *) x != 2)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    free(x);

    if(l->count != 3)
        MLCL_ERR(3, MLCL_ERR_TRUE)
    if(l->size != 10)
        MLCL_ERR(4, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_is_sorted(){
    ArrayList * l;
    int i;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    for(i = 0; i < 5; i++)
        l->d->append(l, &i);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_bubble_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->bublle_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_selection_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->selection_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_insertion_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->insertion_sort(l, l->d->type_descriptor->ge);

    if(!l->d->is_sorted(l, l->d->type_descriptor->ge))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_quick_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
    MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
    MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_merge_sort(){
    ArrayList * l;
    int x;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->merge_sort(l, l->d->type_descriptor->le);

    if(!l->d->is_sorted(l, l->d->type_descriptor->le))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_search(){
    ArrayList * l;
    int x, index;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    x = 28;
    if(!l->d->search(l, &x, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}

int test_array_list_binary_search(){
    ArrayList * l;
    int x, index;

    l = new_array_list(int_m);
    if(!l)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 6;
    l->d->append(l, &x);
    x = 3;
    l->d->append(l, &x);
    x = 28;
    l->d->append(l, &x);
    x = 2;
    l->d->append(l, &x);
    x = 1;
    l->d->append(l, &x);

    l->d->quick_sort(l, l->d->type_descriptor->le);

    x = 28;
    if(!l->d->binary_search(l, &x, &index))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(index != 4)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    l->d->free(&l);
    return 1;
}