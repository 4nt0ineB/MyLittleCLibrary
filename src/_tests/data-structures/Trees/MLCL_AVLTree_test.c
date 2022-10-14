/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Trees/MLCL_AVLTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_AVLTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_TypeDescriptor.h"
#include "../../../../include/core/MLCL_primitive_types.h"

#include <stdio.h>

int run_all_avl_tree_tests(){
    printf("▒▒▒ Running all AVLTree tests \n");
    MLCL_TEST(test_new_avl_tree)
    MLCL_TEST(test_avl_tree_add)
    MLCL_TEST(test_avl_remove)
    return 1;
}

int test_new_avl_tree(){
    AVLTree *tree;
    tree = new_avl_tree(int_m);
    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)
    avl_tree_free(&tree);
    return 1;
}

int test_avl_tree_add(){
    AVLTree *tree;
    int x;
    tree = new_avl_tree(int_m);
    avl_tree_add(tree, new_int(8));
    avl_tree_add(tree, new_int(7));
    avl_tree_add(tree, new_int(6));
    avl_tree_add(tree, new_int(4));
    avl_tree_add(tree, new_int(5));
    /*avl_tree_to_dot(tree, "test.dot");
    avl_tree_fprint_preorder(tree, stdout);*/
    x = 6;
    if(!tree->td->eq(tree->root->left->right->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl_tree_free(&tree);
    return 1;
}

int test_avl_remove(){
    AVLTree *tree;
    int x;
    tree = new_avl_tree(int_m);
    avl_tree_add(tree, new_int(8));
    avl_tree_add(tree, new_int(7));
    avl_tree_add(tree, new_int(6));
    avl_tree_add(tree, new_int(4));
    avl_tree_add(tree, new_int(5));
    x = 8;
    avl_tree_remove(tree, &x);
    x = 6;
    if(!tree->td->eq(tree->root->right->left->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)
    avl_tree_free(&tree);
    return 1;
}

