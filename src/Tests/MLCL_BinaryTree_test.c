/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../include/Tests/MLCL_BinaryTree_test.h"
#include "../../include/Tests/MLCL_exceptions.h"
#include "../../include/MLCL_basic_types.h"


int run_all_binary_tree_tests(){
    printf("▒▓ Running all BinaryTree tests\n");
    MLCL_TEST(test_new_binary_tree)
    MLCL_TEST(test_binary_tree_height)
    MLCL_TEST(test_binary_tree_nb_nodes)
    MLCL_TEST(test_binary_tree_nb_leaves)
    MLCL_TEST(test_binary_tree_nb_internal_nodes)
    MLCL_TEST(test_binary_tree_nb_two_children)
    MLCL_TEST(test_binary_tree_is_bt)
    MLCL_TEST(test_binary_tree_insert)
    MLCL_TEST(test_binary_tee_remove)
    MLCL_TEST(test_binary_tee_search)
    return 1;
}

int test_new_binary_tree(){
    printf("├ test_new_binary_tree");

    return 1;
}
int test_binary_tree_height(){
    printf("├ test_binary_tree_height");
    return 1;
}
int test_binary_tree_nb_nodes(){
    printf("├ test_binary_tree_nb_nodes");
    return 1;
}
int test_binary_tree_nb_leaves(){
    printf("├ test_binary_tree_nb_leaves");
    return 1;
}
int test_binary_tree_nb_internal_nodes(){
    printf("├ test_binary_tree_nb_internal_nodes");
    return 1;
}
int test_binary_tree_nb_two_children(){
    printf("├ test_binary_tree_nb_two_children");
    return 1;
}
int test_binary_tree_is_bt(){
    printf("├ test_binary_tree_is_bt");
    return 1;
}
int test_binary_tree_insert(){
    BinaryTree t;
    int x;
    printf("├ test_binary_tree_insert");
    x = 1;
    t = new_binary_tree(&x, int_manifest);
    x = 2;
    t->d->insert(&t, &x);
    x = 3;
    t->d->insert(&t, &x);
    x = 4;
    t->d->insert(&t, &x);
    /* made with poor linear random generator =,
     * tests might become false with new generator */
    x = 3;
    if(!(t->d->type_descriptor->eq(t->left->left->data, &x)))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->fprint_preorder(stdout, t);printf("\n");
    return 1;
}
int test_binary_tee_remove(){
    printf("├ test_binary_tee_remove");
    return 1;
}
int test_binary_tee_search(){
    printf("├ test_binary_tee_search");
    return 1;
}