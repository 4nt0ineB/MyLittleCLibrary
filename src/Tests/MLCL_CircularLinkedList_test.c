/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tests/MLCL_CircularLinkedList_test.h"

#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_basic_types.h"
#include "../../include/MLCL_CircularLinkedList.h"

#include <stdio.h>

int run_all_circular_linked_list_tests(){
    printf("|> Running all CircularLinkedList tests\n");
    if(!test_cll_append())
        return 0;
    if(!test_cll_pop())
        return 0;
    if(!test_cll_shift())
        return 0;
    return 1;
}

int test_cll_append(){
    CircularLinkedList ll;
    float x;
    printf("- test_cll_append\n");
    x = 5.4f;
    ll = new_cll(&x, new_type_descriptor(float_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    x = 5.3f;
    ll->d->append(&ll, &x);
    ll->d->append(&ll, &x);
    x = 5.96f;
    ll->d->append(&ll, &x);
    if(ll->next->next->next->next != ll)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    ll->d->free(&ll);
    MLCL_OK();
    return 1;
}

int test_cll_pop(){
    /* @Todo test_cll_pop rewrite cll_pop as it is like a shift*/
   /* LinkedList ll;
    int x;
    void * data;
    printf("- test_ll_pop\n");
    x = 5;
    ll = new_cll(&x, new_type_descriptor(int_manifest));
    if(!ll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    x = 6;
    ll->d->prepend(&ll, &x);
    data = ll->d->pop(&ll);
    if((* (int *) data) != 5)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    if(!ll)
        MLCL_ERR(3, MLCL_ERR_FALSE);
    ll->d->free(&ll);
    free(data);*/
   /*Le pop est un shift modifié*/
    MLCL_OK();
    return 1;
}

int test_cll_shift(){
    CircularLinkedList cll;
    float x;
    printf("- test_cll_shift\n");
    x = 5.4f;
    cll = new_cll(&x, new_type_descriptor(float_manifest));
    x = 5.5f;
    cll->d->append(&cll, &x);
    if(!cll)
        MLCL_ERR(1, MLCL_ERR_ALLOC);
    free((float *) cll->d->shift(&cll));
    if(cll->next->next != cll)
        MLCL_ERR(2, MLCL_ERR_TRUE);
    cll->d->free(&cll);
    MLCL_OK();
    return 1;
}