/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tests/MLCL_CircularDoubleLinkedList_test.h"
#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_CircularDoubleLinkedList.h"
#include "../../include/MLCL_basic_types.h"

int run_all_circular_double_linked_list_tests(){
    printf("▒▓ Running all CircularDoubleLinkedList tests\n");
    MLCL_TEST(test_circular_double_linked_list_prepend)
    MLCL_TEST(test_circular_double_linked_list_append)
    MLCL_TEST(test_circular_double_linked_list_search)
    MLCL_TEST(test_circular_double_linked_list_pop)
    MLCL_TEST(test_circular_double_linked_list_shift)
    return 1;
}

int test_circular_double_linked_list_prepend(){
    CircularDoubleLinkedList ll;
    float x;
    printf("├ test_circular_double_linked_list_prepend:");
    x = 5.4f;
    ll = new_circular_double_linked_list(&x, new_type_descriptor(float_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 5.3f;
    ll->d->prepend(&ll, &x);
    if(ll != ll->next->next)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}

int test_circular_double_linked_list_append(){
    CircularDoubleLinkedList ll;
    float x;
    printf("├ test_circular_double_linked_list_append:");
    x = 5.4f;
    ll = new_circular_double_linked_list(&x, new_type_descriptor(float_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    x = 5.3f;
    ll->d->append(&ll, &x);
    ll->d->append(&ll, &x);
    x = 5.96f;
    ll->d->append(&ll, &x);
    if(ll->next->next->next->next != ll)
        MLCL_ERR(2, MLCL_ERR_TRUE)
    ll->d->free(&ll);
    return 1;
}

int test_circular_double_linked_list_search(){
    printf("├ test_circular_double_linked_list_search:");
    return 1;
}

int test_circular_double_linked_list_pop(){
    printf("├ test_circular_double_linked_list_pop:");
    return 1;
}

int test_circular_double_linked_list_shift(){
    printf("├ test_circular_double_linked_list_shift:");
    return 1;
}
