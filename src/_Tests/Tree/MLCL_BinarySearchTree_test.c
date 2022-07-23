/*
 *   This file is part of the MLCL Library.
 *   Antoine Bastos 2022
 *
 *   This Library is free software under the terms of
 *   the MIT license.
 */

#include "../../../include/_Tests/Tree/MLCL_BinarySearchTree_test.h"
#include "../../../include/_Tests/MLCL_exceptions.h"
#include "../../../include/MLCL_basic_types.h"


int run_all_binary_search_tree_tests(){
    printf("▒▓ Running all BinarySearchTree tests\n");
    MLCL_TEST(test_new_binary_search_tree)
    MLCL_TEST(test_binary_search_tree_add)
    MLCL_TEST(test_binary_tree_search)
    MLCL_TEST(test_binary_tree_remove)
    MLCL_TEST(test_binary_search_tree_height)
    MLCL_TEST(test_binary_search_tree_nb_nodes)
    MLCL_TEST(test_binary_search_tree_nb_leaves)
    MLCL_TEST(test_binary_search_tree_nb_internal_nodes)
    MLCL_TEST(test_binary_search_tree_nb_two_children)
    MLCL_TEST(test_binary_search_tree_is_perfect_bt)
    MLCL_TEST(test_binary_search_tree_is_bst)
    return 1;
}

int test_new_binary_search_tree(){
    BinarySearchTree t;
    float x;
    printf("├ test_new_binary_search_tree");
    x = 1.2f;
    t = new_binary_search_tree(&x, float_m);
    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    if(!t->d->type_descriptor->eq(t->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_height(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_height");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->height(t) != 2)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_nb_nodes(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_nb_nodes");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->nb_nodes(t) != 6)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_nb_leaves(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_nb_leaves");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->nb_leaves(t) != 3)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_nb_internal_nodes(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_nb_internal_nodes");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->nb_internal_nodes(t) != 3)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_nb_two_children(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_nb_two_children");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->nb_two_children(t) != 2)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_is_perfect_bt(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_is_perfect_bt");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(t->d->is_perfect_bt(t))
        MLCL_ERR(1, MLCL_ERR_FALSE)
    x = 15;
    t->d->add(&t, &x);
    if(!t->d->is_perfect_bt(t))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_search_tree_add(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_add");
    x = 1;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 3;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 3;
    if(!(t->d->type_descriptor->eq(t->right->right->data, &x)))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}

int test_binary_tree_remove(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_tee_remove");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    x = 14;
    t->d->remove(&t, &x);
    x = 9;
    if(!(t->d->type_descriptor->eq(t->right->data, &x)))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}
int test_binary_tree_search(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_tee_search");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    x = 4;
    if(!(t->d->search(&t, &x)))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}

int test_binary_search_tree_is_bst(){
    BinarySearchTree t;
    int x;
    printf("├ test_binary_search_tree_is_bst");
    x = 7;
    t = new_binary_search_tree(&x, int_m);
    x = 2;
    t->d->add(&t, &x);
    x = 14;
    t->d->add(&t, &x);
    x = 1;
    t->d->add(&t, &x);
    x = 4;
    t->d->add(&t, &x);
    x = 9;
    t->d->add(&t, &x);
    if(!(t->d->is_bst(t)))
        MLCL_ERR(2, MLCL_ERR_TRUE)
    t->d->free(&t);
    return 1;
}