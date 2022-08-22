/*
 *   This file is part of the MLCL Library
 *   Copyright 2022 Antoine Bastos
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
    TernarySearchTree t;

    t = new_ternary_search_tree("Beetlejuice");

    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "Foo");
    t->d->add(&t, "Bar");


    if(* (char *) t->data != 'B')
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(* (char *) t->child->left->child->data != 'r')
        MLCL_ERR(3, MLCL_ERR_TRUE)

    t->d->free(&t);
    return 1;
}

int test_ternary_search_tree_remove(){
    TernarySearchTree t;

    t = new_ternary_search_tree("Neo");
    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "Trinity");
    t->d->add(&t, "Morpheus");
    t->d->add(&t, "Cypher");
    t->d->add(&t, "Switch");

    /*t->d->to_dot(t, "test.dot");
    t->d->print(t);*/

    t->d->remove(&t, "Switch");
    t->d->remove(&t, "Cypher");

    if(t->left->left)
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(t->right->left)
        MLCL_ERR(3, MLCL_ERR_TRUE)

    t->d->free(&t);
    return 1;
}

int test_ternary_search_tree_search(){
    TernarySearchTree t;

    t = new_ternary_search_tree("Scott");

    if(!t)
        MLCL_ERR(1, MLCL_ERR_ALLOC)

    t->d->add(&t, "Ramona");
    t->d->add(&t, "Wallace");
    t->d->add(&t, "Kim");
    t->d->add(&t, "knives");

    if(!t->d->search(t, "Kim"))
        MLCL_ERR(2, MLCL_ERR_TRUE)

    if(t->d->search(t, "Todd"))
        MLCL_ERR(3, MLCL_ERR_FALSE)

    t->d->free(&t);
    return 1;
}