/*
 *   This file is part of the MLCL Library
 *   Copyrleft 2022 Antoine Bastos
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Trees/MLCL_BinarySearchTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_BinarySearchTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"
#include "../../../../include/core/MLCL_basic_types.h"


int run_all_binary_search_tree_tests(){
    printf("▒▒▒ Running all BinarySearchTree tests ▒▒▒\n");
    MLCL_TEST(test_new_binary_search_tree,
              "test_new_binary_search_tree")
    MLCL_TEST(test_binary_search_tree_add,
              "test_binary_search_tree_add")
    MLCL_TEST(test_binary_tree_search,
              "test_binary_tree_search")
    MLCL_TEST(test_binary_tree_remove,
              "test_binary_tree_remove")
    MLCL_TEST(test_binary_search_tree_height,
              "test_binary_search_tree_height")
    MLCL_TEST(test_binary_search_tree_nb_nodes,
              "test_binary_search_tree_nb_nodes")
    MLCL_TEST(test_binary_search_tree_nb_leaves,
              "test_binary_search_tree_nb_leaves")
    MLCL_TEST(test_binary_search_tree_nb_internal_nodes,
              "test_binary_search_tree_nb_internal_nodes")
    MLCL_TEST(test_binary_search_tree_nb_two_children,
              "test_binary_search_tree_nb_two_children")
    MLCL_TEST(test_binary_search_tree_is_perfect_bt,
              "test_binary_search_tree_is_perfect_bt")
    MLCL_TEST(test_binary_search_tree_is_bst,
              "test_binary_search_tree_is_bst")
    return 1;
}

int test_new_binary_search_tree(){
    BinarySearchTree *tree;
    float x;

    tree = new_binary_search_tree(float_m);
    binary_search_tree_add(tree, new_float(1.2f));

    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    x = 1.2f;
    if(!tree->td->eq(tree->root->data, &x))
        MLCL_ERR(1, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_height(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_height(tree) != 2)
        MLCL_ERR(1, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_nb_nodes(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_nb_nodes(tree) != 6)
        MLCL_ERR(1, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_nb_leaves(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_nb_leaves(tree) != 3)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_nb_internal_nodes(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_nb_internal_nodes(tree) != 3)
        MLCL_ERR(1, MLCL_ERR_TRUE)
    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_nb_two_children(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_nb_two_children(tree) != 2)
        MLCL_ERR(1, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_is_perfect_bt(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(binary_search_tree_is_perfect_bt(tree))
        MLCL_ERR(1, MLCL_ERR_FALSE)

    binary_search_tree_add(tree, new_int(15));

    if(!binary_search_tree_is_perfect_bt(tree))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_search_tree_add(){
    BinarySearchTree *tree;
    int x;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(3));
    binary_search_tree_add(tree, new_int(4));

    x = 4;
    if(!(tree->td->eq(tree->root->right->right->data, &x)))
        MLCL_ERR(1, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}

int test_binary_tree_remove(){
    BinarySearchTree *tree;
    int x;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    x = 14;
    binary_search_tree_remove(tree, &x);

    x = 9;
    if(!(tree->td->eq(tree->root->right->data, &x)))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
int test_binary_tree_search(){
    BinarySearchTree *tree;
    int x;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    x = 4;
    if(!(binary_search_tree_search(tree, &x)))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}

int test_binary_search_tree_is_bst(){
    BinarySearchTree *tree;

    tree = new_binary_search_tree(int_m);
    binary_search_tree_add(tree, new_int(7));
    binary_search_tree_add(tree, new_int(2));
    binary_search_tree_add(tree, new_int(14));
    binary_search_tree_add(tree, new_int(1));
    binary_search_tree_add(tree, new_int(4));
    binary_search_tree_add(tree, new_int(9));

    if(!(binary_search_tree_is_bst(tree)))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    binary_search_tree_free(&tree);
    return 1;
}
