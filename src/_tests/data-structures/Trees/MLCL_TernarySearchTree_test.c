/*
 *   This file is part of the MLCL Library
 *   Antoine Bastos 2022
 *   SPDX-License-Identifier: Apache-2.0
 */

#include "../../../../include/_tests/data-structures/Trees/MLCL_TernarySearchTree_test.h"
#include "../../../../include/data-structures/Trees/MLCL_TernarySearchTree.h"
#include "../../../../include/_tests/MLCL_exceptions.h"


int run_all_ternary_search_tree_tests(){
    printf("▒▒▒ Running all TernarySearchTree tests ▒▒▒\n");
    MLCL_TEST(test_ternary_search_tree_add, "test_ternary_search_tree_add")
    MLCL_TEST(test_ternary_search_tree_remove, "test_ternary_search_tree_remove")
    MLCL_TEST(test_ternary_search_tree_search, "test_ternary_search_tree_search")
    return 1;
}


int test_ternary_search_tree_add(){
    TernarySearchTree *tree;

    tree = new_ternary_search_tree();

    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    ternary_search_tree_add(tree, "Beetlejuice");
    ternary_search_tree_add(tree, "Foo");
    ternary_search_tree_add(tree, "Bar");

    if(* (char *) tree->root->data != 'B')
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(* (char *) tree->root->child->left->child->data != 'r')
        MLCL_ERR(3, MLCL_ERR_TRUE)

    ternary_search_tree_free(&tree);
    return 1;
}

int test_ternary_search_tree_remove(){
    TernarySearchTree *tree;

    tree = new_ternary_search_tree();

    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    ternary_search_tree_add(tree, "Neo");
    ternary_search_tree_add(tree, "Trinity");
    ternary_search_tree_add(tree, "Morpheus");
    ternary_search_tree_add(tree, "Cypher");
    ternary_search_tree_add(tree, "Switch");


    /*t->d->to_dot(t, "test.dot");
    t->d->print(t);*/


    ternary_search_tree_remove(tree, "Switch");
    ternary_search_tree_remove(tree, "Cypher");

    if(tree->root->left->left)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(tree->root->right->left)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    ternary_search_tree_free(&tree);
    return 1;
}

int test_ternary_search_tree_search(){
    TernarySearchTree *tree;

    tree = new_ternary_search_tree();

    if(!tree)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    ternary_search_tree_add(tree, "Scott");
    ternary_search_tree_add(tree, "Ramona");
    ternary_search_tree_add(tree, "Wallace");
    ternary_search_tree_add(tree, "Kim");
    ternary_search_tree_add(tree, "knives");

    if(!ternary_search_tree_search(tree, "Kim"))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(ternary_search_tree_search(tree, "Todd"))
        MLCL_ERR(3, MLCL_ERR_FALSE)

    ternary_search_tree_free(&tree);
    return 1;
}
