/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../../include/_Tests/Tree/MLCL_AVLTree_test.h"
#include "../../../include/Tree/MLCL_AVLTree.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_TypeDescriptor.h"
#include "../../../include/MLCL_basic_types.h"

#include <stdio.h>

int run_all_avl_tree_tests(){
    printf("▒▓ Running all AVLTree tests\n");
    MLCL_TEST(test_new_avl_tree)
    MLCL_TEST(test_avl_tree_add)
    MLCL_TEST(test_avl_remove)
    return 1;
}

int test_new_avl_tree(){
    AVLTree avl;
    int x;
    printf("├ test_new_avl_tree:");
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    if(!avl)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    avl->d->free(&avl);
    return 1;
}

int test_avl_tree_add(){
    AVLTree avl;
    int x;
    printf("├ test_avl_tree_add:");
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    x = 7;
    avl->d->add(&avl, &x);
    x = 6;
    avl->d->add(&avl, &x);
    x = 4;
    avl->d->add(&avl, &x);
    x = 5;
    avl->d->add(&avl, &x);
    x = 6;
    if(!avl->d->type_descriptor->eq(avl->left->right->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl->d->free(&avl);
    return 1;
}

int test_avl_remove(){
    AVLTree avl;
    int x;
    printf("├ test_avl_remove:");
    x = 8;
    avl = new_avl_tree(&x,  int_m);
    x = 7;
    avl->d->add(&avl, &x);
    x = 6;
    avl->d->add(&avl, &x);
    x = 4;
    avl->d->add(&avl, &x);
    x = 5;
    avl->d->add(&avl, &x);
    x = 8;
    avl->d->remove(&avl, &x);
    avl->d->to_dot(avl, "test.dot");
    x = 6;
    if(!avl->d->type_descriptor->eq(avl->right->left->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl->d->free(&avl);
    return 1;
}